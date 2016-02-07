#include <string>

#include <myroomies/bom/Output.h>
#include <myroomies/bom/Expense.h>

namespace myroomies {
namespace bom {

void Expense::marshall(std::string& oStr)
{
    putValue("id", id);
    putValue("userId", userId);
    putValue("houseshareId", houseshareId);
    putValue("date", date);
    putValue("amount", amount);
    putValue("title", title);
    putValue("comment", comment);
    marshallObject(oStr);
}

} /* namespace bom */
} /* namespace myroomies */
