#include <myroomies/bom/Input.h>
#include <myroomies/bom/ExpenseNew.h>

namespace myroomies {
namespace bom {

void ExpenseNew::unmarshall()
{
    extractValue("amount", true, amount);
    extractValue("date", true, date);
    extractValue("title", true, title);
    extractValue("comment", true, comment);
}

void ExpenseNew::validate() const
{
}

} /* namespace bom */
} /* namespace myroomies */
