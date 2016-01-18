#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <myroomies/bom/Unmarshaller.h>
#include <myroomies/bom/Marshaller.h>
#include <myroomies/bom/Expense.h>

using rapidjson::Document;
using rapidjson::Value;
using rapidjson::Writer;
using rapidjson::StringBuffer;

namespace myroomies {
namespace bom {

template<>
void Marshaller<Expense>::marshall(Expense& iObject, std::string& oStr)
{
    Document o;
    o.SetObject();
    Document::AllocatorType& allocator = o.GetAllocator();
    o.AddMember("id", iObject.id, allocator);
    o.AddMember("userId", iObject.userId, allocator);
    std::time_t cdate = std::chrono::system_clock::to_time_t(iObject.date);
    o.AddMember("date", Value().SetString(rapidjson::StringRef(std::ctime(&cdate))), allocator);
    o.AddMember("amount", Value().SetDouble(iObject.amount), allocator);
    o.AddMember("title", iObject.title, allocator);
    o.AddMember("comment", iObject.comment, allocator);
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    o.Accept(writer);
    oStr = buffer.GetString();
}

template<>
void Unmarshaller<Expense>::unmarshall(const std::string& iStr, Expense& oObject)
{
    Document d;
    d.Parse(iStr.c_str());
    if (d.HasMember("id"))
    {
        oObject.id = d["id"].GetInt();
    }
    oObject.userId = d["userId"].GetInt();
    oObject.date = std::chrono::system_clock::now();
    oObject.title = d["title"].GetString();
    oObject.comment = d["comment"].GetString();
    oObject.tags = {"food"};
}
} /* namespace bom */
} /* namespace myroomies */
