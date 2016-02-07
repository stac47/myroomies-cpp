#pragma once

#include <string>

#include <myroomies/model/Expense.h>
#include <myroomies/bom/Output.h>

namespace myroomies {
namespace bom {

// using myroomies::model::Expense;
struct Expense final : public myroomies::model::Expense,
                       public myroomies::bom::Output
{
    void marshall(std::string& oOutputStr) override;
};

} /* namespace bom */
} /* namespace myroomies */
