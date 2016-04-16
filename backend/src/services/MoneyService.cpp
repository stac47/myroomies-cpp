#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <iterator>

#include <myroomies/utils/Configuration.h>
#include <myroomies/utils/LoggingMacros.h>
#include <myroomies/utils/db/Def.h>

#include <myroomies/bom/Expense.h>
#include <myroomies/bom/User.h>

#include <myroomies/model/ExpenseDataAccess.h>

#include <myroomies/services/ServiceRegistry.h>
#include <myroomies/services/ServiceInterface.h>
#include <myroomies/services/MoneyService.h>
#include <myroomies/services/Exception.h>

using myroomies::utils::Configuration;
using myroomies::utils::db::Key_t;

using myroomies::bom::Expense;
using myroomies::bom::ExpenseNew;
using myroomies::bom::User;

using myroomies::model::ExpenseDataAccess;

using myroomies::services::ServiceRegistry;
using myroomies::services::ServiceInterface;

namespace {

myroomies::bom::Expense FromModel(const myroomies::model::Expense& iExpense)
{

    Expense expense;
    expense.id = iExpense.id;
    expense.userId = iExpense.userId;
    expense.date = iExpense.date;
    expense.amount = iExpense.amount;
    expense.title = iExpense.title;
    expense.comment = iExpense.comment;
    expense.tags = iExpense.tags;
    return expense;
}

myroomies::model::Expense ToModel(const myroomies::bom::Expense& iExpense)
{
    myroomies::model::Expense expense;
    expense.id = iExpense.id;
    expense.userId = iExpense.userId;
    expense.date = iExpense.date;
    expense.amount = iExpense.amount;
    expense.title = iExpense.title;
    expense.comment = iExpense.comment;
    expense.tags = iExpense.tags;
    return expense;
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
    ExpenseDataAccess dao;
    auto expenses = dao.getAllExpenses();
    std::vector<Expense> result;
    if (iLoggedUser->id == 1)
    {
        MYROOMIES_LOG_INFO("User [admin] retrieves all expenses");
        std::transform(expenses.begin(), expenses.end(), std::back_inserter(result),
            [] (const auto& e) {return FromModel(e);});
    }
    else
    {
        Key_t id = iLoggedUser->id;
        MYROOMIES_LOG_INFO("User [id=" << id << "] retrieves all expenses"
                           << " from houseshare [id=" << iLoggedUser->houseshareId << "]");
        auto it = std::partition(expenses.begin(), expenses.end(),
            [&id] (const auto& e) {return e.userId != id;});
        std::transform(it, expenses.end(), std::back_inserter(result),
            [] (const myroomies::model::Expense& e) {return FromModel(e);});
    }
    return result;
}

Expense MoneyService::addExpense(
    const std::unique_ptr<const User>& iLoggedUser,
    const ExpenseNew& iExpense)
{
    ExpenseDataAccess dao;
    myroomies::model::Expense expenseToInsert = ToModel(iExpense);
    expenseToInsert.userId = iLoggedUser->id;
    auto createdExpense = dao.createExpense(expenseToInsert);
    MYROOMIES_LOG_INFO("User [id=" << iLoggedUser->id << "] "
                       << "created expense [id=" << createdExpense.id << "] ");
    return FromModel(createdExpense);
}

void MoneyService::removeExpense(Key_t iLoggedUserId, Key_t iExpenseId)
{
    ExpenseDataAccess dao;
    auto expenses = dao.getAllExpenses();
    auto it = std::find_if(expenses.begin(), expenses.end(),
                           [iExpenseId](const auto& e) {return e.id == iExpenseId;});
    if (it == expenses.end())
    {
        MYROOMIES_LOG_WARN("User [id=" << iLoggedUserId << "] tried to remove "
                           << "expense [id=" << iExpenseId << "] which does not exist.");
        throw ResourceNotFoundException();
    }
    if (iLoggedUserId == 1)
    {
        MYROOMIES_LOG_INFO("'admin' deletes expense [id=" << iExpenseId << "]");
    }
    else if (it->userId != iLoggedUserId)
    {
        MYROOMIES_LOG_WARN("User [id=" << iLoggedUserId << "] "
                           << "tries to delete expense [id=" << iExpenseId << "]");
        throw ForbiddenResourceException();
    }
    dao.removeExpense(it->id);
}

} /* namespace services */
} /* namespace myroomies */
