#pragma once

#include <string>

#include <myroomies/model/Expense.h>
#include <myroomies/bom/Input.h>

namespace myroomies {
namespace bom {

struct ExpenseNew final : public myroomies::model::Expense,
                          public myroomies::bom::Input
{
    void unmarshall() override;
    void validate() const override;
};

} /* namespace bom */
} /* namespace myroomies */
