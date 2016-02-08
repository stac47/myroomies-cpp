#pragma once

#include <string>
#include <memory>
#include <vector>

#include <myroomies/utils/Configuration.h>
#include <myroomies/utils/db/Def.h>

#include <myroomies/bom/Expense.h>
#include <myroomies/bom/ExpenseNew.h>

#include <myroomies/services/ServiceInterface.h>

namespace myroomies {
namespace services {

class ServiceRegistry;

class MoneyService : public ServiceInterface
{
public:
    static std::shared_ptr<MoneyService> BuildFromConfig(
        const std::shared_ptr<ServiceRegistry>& iServiceRegistry,
        const myroomies::utils::Configuration&);

    std::vector<myroomies::bom::Expense> getExpenses(
        const std::unique_ptr<const myroomies::bom::User>& iLoggedUser) const;

    myroomies::bom::Expense addExpense(
        const std::unique_ptr<const myroomies::bom::User>& iLoggedUser,
        const myroomies::bom::ExpenseNew& iExpense);

    void removeExpense(myroomies::utils::db::Key_t iLoggedUserId,
                       myroomies::utils::db::Key_t iExpenseId);

private:
    MoneyService(const std::shared_ptr<ServiceRegistry>& iServiceRegistry);

};

} /* namespace services */
} /* namespace myroomies */
