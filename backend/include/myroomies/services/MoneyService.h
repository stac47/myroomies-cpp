#pragma once

#include <string>
#include <memory>
#include <vector>

#include <myroomies/utils/Configuration.h>

#include <myroomies/bom/Expense.h>

#include <myroomies/services/ServiceRegistry.h>
#include <myroomies/services/ServiceInterface.h>

namespace myroomies {
namespace services {

class MoneyService : public ServiceInterface
{
public:
    static std::shared_ptr<MoneyService> BuildFromConfig(
        const std::shared_ptr<ServiceRegistry>& iServiceRegistry,
        const myroomies::utils::Configuration&);

    std::vector<myroomies::bom::Expense> getExpenses();

    const myroomies::bom::Expense addExpense(const myroomies::bom::Expense& iExpense);

private:
    MoneyService(const std::shared_ptr<ServiceRegistry>& iServiceRegistry);
};

} /* namespace services */
} /* namespace myroomies */
