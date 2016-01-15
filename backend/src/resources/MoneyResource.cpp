#include <sstream>
#include <vector>
#include <chrono>

/* #define RAPIDJSON_HAS_STDSTRING 1 */
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <httpserver.hpp>

#include <myroomies/model/Expense.h>
#include <myroomies/resources/MoneyResource.h>

using rapidjson::Document;
using rapidjson::Value;
using rapidjson::Writer;
using rapidjson::StringBuffer;

using httpserver::http_response_builder;
using httpserver::http_response;

using myroomies::model::Expense;

namespace {

std::vector<Expense>& GetExpenses()
{
    static std::vector<Expense> ExpensesVector;
    if (ExpensesVector.empty())
    {
        std::vector<std::string> tags;
        tags.push_back("nourriture");
        ExpensesVector.push_back({1, 1, std::chrono::system_clock::now(), 12.5, "test 1", "comment 1", tags});
        ExpensesVector.push_back({2, 2, std::chrono::system_clock::now(), 100, "test 2", "comment 2", tags});
    }
    return ExpensesVector;
}

} // namespace

namespace myroomies {
namespace resources {

void MoneyResource::onGET(const httpserver::http_request& iRequest,
                          httpserver::http_response** oResponse)
{
    Document d;
    d.SetArray();
    Document::AllocatorType& allocator = d.GetAllocator();
    for (Expense e : GetExpenses())
    {
        Value o(rapidjson::kObjectType);
        o.AddMember("id", e.id, allocator);
        o.AddMember("userId", e.userId, allocator);
        std::time_t cdate = std::chrono::system_clock::to_time_t(e.date);
        o.AddMember("date", Value().SetString(rapidjson::StringRef(std::ctime(&cdate))), allocator);
        o.AddMember("amount", Value().SetDouble(e.amount), allocator);
        o.AddMember("title", e.title, allocator);
        o.AddMember("comment", e.comment, allocator);
        d.PushBack(o, allocator);
    }
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
    *oResponse = new http_response(
        http_response_builder(buffer.GetString(), 200, "application/json; charset=utf-8").string_response()
    );
}

void MoneyResource::onPOST(const httpserver::http_request& iRequest,
                           httpserver::http_response** oResponse)
{
    std::string content;
    iRequest.get_content(content);
    Document d;
    d.Parse(content.c_str());
    Expense expense;
    if (d.HasMember("id"))
    {
        expense.id = d["id"].GetInt();
    }
    expense.userId = d["userId"].GetInt();
    expense.date = std::chrono::system_clock::now();
    expense.title = d["title"].GetString();
    expense.comment = d["comment"].GetString();
    expense.tags = {"food"};
    GetExpenses().push_back(expense);
    *oResponse = new http_response(
        http_response_builder(content, 200, "application/json; charset=utf-8").string_response()
    );
}

} /* namespace resources */
} /* namespace myroomies */
