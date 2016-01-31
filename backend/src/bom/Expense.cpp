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
    putValue("houseshareId", iObject.houseshareId);
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
    extractValue("id", false, oObject.id);
    extractValue("userId", false, oObject.userId);
    extractValue("houseshareId", false, oObject.houseshareId);
    extractValue("amount", true, oObject.amount);
    extractValue("date", true, oObject.date);
    extractValue("title", true, oObject.title);
    extractValue("comment", true, oObject.comment);
}
} /* namespace bom */
} /* namespace myroomies */
