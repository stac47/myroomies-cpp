#include <myroomies/bom/Unmarshaller.h>
#include <myroomies/bom/Marshaller.h>
#include <myroomies/bom/Expense.h>

namespace myroomies {
namespace bom {

template<>
void Marshaller<Expense>::marshallObject(const Expense& iObject, std::string& oStr)
{
    putValue("id", iObject.id);
    putValue("userId", iObject.userId);
    putValue("date", iObject.date);
    putValue("amount", iObject.amount);
    putValue("title", iObject.title);
    putValue("comment", iObject.comment);
    marshall(oStr);
}

template<>
void Unmarshaller<Expense>::unmarshall(const std::string& iStr, Expense& oObject)
{
    parse(iStr);
    extractValue("id", true, oObject.id);
    extractValue("userId", false, oObject.userId);
    extractValue("amount", false, oObject.amount);
    extractValue("date", false, oObject.date);
    extractValue("title", false, oObject.title);
    extractValue("comment", false, oObject.comment);
}
} /* namespace bom */
} /* namespace myroomies */
