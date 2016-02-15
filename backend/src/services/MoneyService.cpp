#include <string>
#include <memory>
#include <vector>
#include <algorithm>

#include <myroomies/utils/Configuration.h>
#include <myroomies/utils/LoggingMacros.h>
#include <myroomies/utils/db/Def.h>

#include <myroomies/bom/Expense.h>
#include <myroomies/bom/User.h>

#include <myroomies/services/ServiceRegistry.h>
#include <myroomies/services/ServiceInterface.h>
#include <myroomies/services/MoneyService.h>
#include <myroomies/services/Exception.h>

using myroomies::utils::Configuration;
using myroomies::utils::db::Key_t;

using myroomies::bom::Expense;
using myroomies::bom::ExpenseNew;
using myroomies::bom::User;

using myroomies::services::ServiceRegistry;
using myroomies::services::ServiceInterface;

namespace {

std::vector<Expense>& GetExpenses()
{
    static std::vector<Expense> ExpensesVector;
    return ExpensesVector;
}

} /* namespace  */

namespace myroomies {
namespace services {


std::shared_ptr<MoneyService> MoneyService::BuildFromConfig(
    const std::shared_ptr<ServiceRegistry>& iServiceRegistry,
    const Configuration&)
{
    return std::shared_ptr<MoneyService>(new MoneyService(iServiceRegistry));
}

MoneyService::MoneyService(const std::shared_ptr<ServiceRegistry>&)
  : ServiceInterface("Money")
{}

std::vector<Expense> MoneyService::getExpenses(
    const std::unique_ptr<const User>& iLoggedUser) const
{
    // TODO check if admin or user
    return GetExpenses();
}

Expense MoneyService::addExpense(
    const std::unique_ptr<const User>& iLoggedUser,
    const ExpenseNew& iExpense)
{
    Expense createdExpense;
    createdExpense.id = GetExpenses().size() + 1;
    createdExpense.userId = iLoggedUser->id;
    createdExpense.houseshareId = iLoggedUser->houseshareId;
    createdExpense.date = iExpense.date;
    createdExpense.amount = iExpense.amount;
    createdExpense.title = iExpense.title;
    createdExpense.comment = iExpense.comment;
    GetExpenses().push_back(createdExpense);
    MYROOMIES_LOG_INFO("User [id=" << iLoggedUser->id << "] "
                       << "created expense [id=" << createdExpense.id << "] "
                       << "for houseshare [id=" << iLoggedUser->houseshareId << "]");
    return createdExpense;
}

void MoneyService::removeExpense(Key_t iLoggedUserId, Key_t iExpenseId)
{
    auto it = std::find_if(GetExpenses().begin(), GetExpenses().end(),
                           [iExpenseId](const Expense& e) {return e.id == iExpenseId;});
    if (it == std::end(GetExpenses()))
    {
        throw ResourceNotFoundException();
    }
    if (iLoggedUserId == 0)
    {
        MYROOMIES_LOG_INFO("'admin' deletes expense [id=" << iExpenseId << "]");
    }
    else if (it->userId != iLoggedUserId)
    {
        MYROOMIES_LOG_WARN("User [id=" << iLoggedUserId << "] "
                           << "tries to delete expense [id=" << iExpenseId << "]");
        throw ForbiddenResourceException();
    }
    GetExpenses().erase(it);
}

} /* namespace services */
} /* namespace myroomies */
