#include <sstream>
#include <vector>

#include <myroomies/bom/Marshaller.h>
#include <myroomies/bom/Unmarshaller.h>
#include <myroomies/bom/Expense.h>


#include <myroomies/services/MoneyService.h>

#include <myroomies/resources/MoneyHandler.h>


using myroomies::bom::Marshaller;
using myroomies::bom::Unmarshaller;

using myroomies::resources::HttpRequest;
using myroomies::resources::HttpResponse;

using myroomies::model::Expense;

using myroomies::services::MoneyService;

namespace myroomies {
namespace resources {

void MoneyHandler::handleGET(const HttpRequest& iRequest, HttpResponse& oResponse)
{
    std::string response;

    Marshaller<Expense> m;
    m.marshallCollection(getServiceRegistry()->get<MoneyService>()->getExpenses(), response);
    oResponse.setPayload(response);
}

void MoneyHandler::handlePOST(const HttpRequest& iRequest, HttpResponse& oResponse)
{
    std::string content = iRequest.getPayload();
    Unmarshaller<Expense> unmarshaller;
    Expense e;
    unmarshaller.unmarshall(content, e);
    Expense newExpense = getServiceRegistry()->get<MoneyService>()->addExpense(e);
    std::string responsePayload;
    Marshaller<Expense> m;
    m.marshallObject(newExpense, responsePayload);
    oResponse.setPayload(responsePayload);
}

} /* namespace resources */
} /* namespace myroomies */
