#include <string>
#include <memory>
#include <vector>

#include <myroomies/utils/Configuration.h>

#include <myroomies/bom/Expense.h>

#include <myroomies/services/ServiceRegistry.h>
#include <myroomies/services/ServiceInterface.h>
#include <myroomies/services/MoneyService.h>

using myroomies::utils::Configuration;
using myroomies::bom::Expense;
using myroomies::services::ServiceRegistry;
using myroomies::services::ServiceInterface;

namespace {

std::vector<Expense>& GetExpenses()
{
    static std::vector<Expense> ExpensesVector;
    if (ExpensesVector.empty())
    {
        Expense e;
        e.id = 1;
        e.userId = 1;
        e.date = boost::gregorian::date(boost::gregorian::day_clock::universal_day());
        e.amount = 12.5;
        e.title = "test1";
        e.comment = "comment 1";
        ExpensesVector.push_back(e);
        ExpensesVector.push_back(e);
    }
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
  : ServiceInterface()
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

} /* namespace services */
} /* namespace myroomies */
