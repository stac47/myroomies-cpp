#include <sstream>
#include <vector>
#include <regex>

#include <boost/lexical_cast.hpp>

#include <myroomies/utils/db/Def.h>
#include <myroomies/utils/LoggingMacros.h>

#include <myroomies/bom/Expense.h>
#include <myroomies/bom/ExpenseNew.h>
#include <myroomies/bom/User.h>

#include <myroomies/services/MoneyService.h>
#include <myroomies/services/Exception.h>

#include <myroomies/resources/MoneyHandler.h>

using myroomies::resources::HttpRequest;
using myroomies::resources::HttpResponse;

using myroomies::utils::db::Key_t;

using myroomies::bom::Expense;
using myroomies::bom::ExpenseNew;
using myroomies::bom::User;

using myroomies::services::MoneyService;

namespace myroomies {
namespace resources {

void MoneyHandler::handleGET(const HttpRequest& iRequest, HttpResponse& oResponse)
{
    std::vector<Expense> expenses =
        getServiceRegistry()->get<MoneyService>()->getExpenses(getLoggedUser());
    std::string response;
    myroomies::bom::MarshallCollection(expenses, response);
    oResponse.setPayload(response);
}

void MoneyHandler::handlePOST(const HttpRequest& iRequest, HttpResponse& oResponse)
{
    std::string content = iRequest.getPayload();
    ExpenseNew newExpense;
    newExpense.parse(content);
    Expense createdExpense = getServiceRegistry()->get<MoneyService>()->addExpense(getLoggedUser(), newExpense);
    std::string responsePayload;
    createdExpense.marshall(responsePayload);
    oResponse.setPayload(responsePayload);
}

void MoneyHandler::handleDELETE(const HttpRequest& iRequest, HttpResponse& oResponse)
{
    std::string uri = iRequest.getPath();
    std::regex urlRegex("/(\\d+)$");
    std::smatch match;
    std::regex_search(uri, match, urlRegex);
    std::string expenseIdStr = match[1];
    MYROOMIES_LOG_DEBUG("Deleting expense [id=" << expenseIdStr << "] "
                        << "extracted from [URI=" << uri << "]");
    try
    {
        Key_t expenseId = boost::lexical_cast<Key_t>(expenseIdStr);
        getServiceRegistry()->get<MoneyService>()->removeExpense(getLoggedUser()->id, expenseId);
        oResponse.setStatus(200);
    }
    catch (const boost::bad_lexical_cast&)
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
