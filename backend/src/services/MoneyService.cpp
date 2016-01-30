#include <string>
#include <memory>
#include <vector>
#include <algorithm>

#include <myroomies/utils/Configuration.h>
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

std::vector<Expense> MoneyService::getExpenses()
{
    return GetExpenses();
}

const Expense MoneyService::addExpense(const Expense& iExpense)
{
    GetExpenses().push_back(iExpense);
    return iExpense;
}

void MoneyService::removeExpense(const User& iLoggedUser, Key_t iExpenseId)
{
    auto it = std::find_if(GetExpenses().begin(), GetExpenses().end(),
                           [iExpenseId](const Expense& e) {return e.id == iExpenseId;});
    if (it == std::end(GetExpenses()))
    {
        throw ResourceNotFoundException();
    }
    if (it->userId != iLoggedUser.user.id)
    {
        throw ForbiddenResourceException();
    }
    GetExpenses().erase(it);
}

} /* namespace services */
} /* namespace myroomies */
