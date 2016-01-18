#include <sstream>
#include <vector>
#include <chrono>

#include <httpserver.hpp>

#include <myroomies/bom/Marshaller.h>
#include <myroomies/bom/Unmarshaller.h>

#include <myroomies/model/Expense.h>

#include <myroomies/resources/MoneyResource.h>

using httpserver::http_response_builder;
using httpserver::http_response;

using myroomies::bom::Marshaller;
using myroomies::bom::Unmarshaller;

using myroomies::model::Expense;

namespace {

std::vector<Expense>& GetExpenses()
{
    static std::vector<Expense> ExpensesVector;
    if (ExpensesVector.empty())
    {
        Expense e;
        e.id = 1;
        e.userId = 1;
        e.date = std::chrono::system_clock::now();
        e.amount = 12.5;
        e.title = "test1";
        e.comment = "comment 1";
        ExpensesVector.push_back(e);
        ExpensesVector.push_back(e);
    }
    return ExpensesVector;
}

} // namespace

namespace myroomies {
namespace resources {

void MoneyResource::onGET(const httpserver::http_request& iRequest,
                          httpserver::http_response** oResponse)
{
    std::string response;

    Marshaller<Expense> m;
    m.marshall(GetExpenses()[0], response);
    *oResponse = new http_response(
        http_response_builder(response, 200, "application/json; charset=utf-8").string_response()
    );
}

void MoneyResource::onPOST(const httpserver::http_request& iRequest,
                           httpserver::http_response** oResponse)
{
    std::string content;
    iRequest.get_content(content);
    Unmarshaller<Expense> unmarshaller;
    Expense e;
    unmarshaller.unmarshall(content, e);
    GetExpenses().push_back(e);
    *oResponse = new http_response(
        http_response_builder("Hello POST", 200, "application/json; charset=utf-8").string_response()
    );
}

} /* namespace resources */
} /* namespace myroomies */
