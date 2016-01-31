#pragma once

#include <myroomies/model/Expense.h>

#include <myroomies/bom/Unmarshaller.h>
#include <myroomies/bom/Marshaller.h>

namespace myroomies {
namespace bom {

// using myroomies::model::Expense;
class Expense : public myroomies::model::Expense
{};

template class Marshaller<Expense>;
template class Unmarshaller<Expense>;

} /* namespace bom */
} /* namespace myroomies */
