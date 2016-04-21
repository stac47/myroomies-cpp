#include <vector>
#include <sstream>

#include <boost/serialization/vector.hpp>

#include <myroomies/utils/db/Def.h>
#include <myroomies/utils/LoggingMacros.h>
#include <myroomies/utils/UriMatcher.h>
#include <myroomies/utils/json/JsonOutputArchive.h>
#include <myroomies/utils/json/JsonInputArchive.h>

#include <myroomies/bom/Expense.h>
#include <myroomies/bom/User.h>

#include <myroomies/services/MoneyService.h>
#include <myroomies/services/Exception.h>

#include <myroomies/resources/MoneyHandler.h>

using myroomies::resources::HttpRequest;
using myroomies::resources::HttpResponse;

using myroomies::utils::db::Key_t;
using myroomies::utils::UriMatcher;

using myroomies::bom::Expense;
using myroomies::bom::ExpenseNew;
using myroomies::bom::User;

using myroomies::utils::json::JsonInputArchive;
using myroomies::utils::json::JsonOutputArchive;

using myroomies::services::MoneyService;

namespace myroomies {
namespace resources {

void MoneyHandler::handleGET(const HttpRequest& iRequest, HttpResponse& oResponse)
{
    std::vector<Expense> expenses =
        getServiceRegistry()->get<MoneyService>()->getExpenses(getLoggedUser());
    std::ostringstream os;
    JsonOutputArchive oa(os);
    oa << expenses;
    oResponse.setPayload(os.str());
}

void MoneyHandler::handlePOST(const HttpRequest& iRequest, HttpResponse& oResponse)
{
    std::string content = iRequest.getPayload();
    JsonInputArchive ia(content);
    ExpenseNew newExpense;
    ia >> newExpense;
    Expense createdExpense = getServiceRegistry()->get<MoneyService>()->addExpense(getLoggedUser(), newExpense);
    std::ostringstream os;
    JsonOutputArchive oa(os);
    oa << createdExpense;
    oResponse.setPayload(os.str());
}

void MoneyHandler::handleDELETE(const HttpRequest& iRequest, HttpResponse& oResponse)
{
    UriMatcher matcher("^\\S*/(\\d+)$");
    if (!matcher.match(iRequest.getPath()))
    {
        oResponse.setStatus(400);
        return;
    }
    try
    {
        Key_t expenseId = matcher.get<Key_t>(1);
        MYROOMIES_LOG_DEBUG("Deleting expense [id=" << expenseId << "] "
                            << "extracted from [URI=" << iRequest.getPath() << "]");
        getServiceRegistry()->get<MoneyService>()->removeExpense(getLoggedUser()->id, expenseId);
        oResponse.setStatus(200);
    }
    catch (const myroomies::utils::UriMatcherException&)
    {
        oResponse.setStatus(400);
    }
    catch (const myroomies::services::ForbiddenResourceException&)
    {
        oResponse.setStatus(403);
    }
    catch (const myroomies::services::ResourceNotFoundException&)
    {
        oResponse.setStatus(404);
    }
}


} /* namespace resources */
} /* namespace myroomies */
