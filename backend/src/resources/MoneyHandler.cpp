#include <sstream>
#include <vector>

#include <boost/date_time/gregorian/gregorian.hpp>

#include <myroomies/bom/Marshaller.h>
#include <myroomies/bom/Unmarshaller.h>

#include <myroomies/model/Expense.h>

#include <myroomies/resources/MoneyHandler.h>


using myroomies::bom::Marshaller;
using myroomies::bom::Unmarshaller;

using myroomies::resources::HttpRequest;
using myroomies::resources::HttpResponse;

using myroomies::model::Expense;

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

} // namespace

namespace myroomies {
namespace resources {

void MoneyHandler::handleGET(const HttpRequest& iRequest, HttpResponse& oResponse)
{
    std::string response;

    Marshaller<Expense> m;
    m.marshallCollection(GetExpenses(), response);
    oResponse.setPayload(response);
}

void MoneyHandler::handlePOST(const HttpRequest& iRequest, HttpResponse& oResponse)
{
    std::string content = iRequest.getPayload();
    Unmarshaller<Expense> unmarshaller;
    Expense e;
    unmarshaller.unmarshall(content, e);
    GetExpenses().push_back(e);
    std::string responsePayload;
    Marshaller<Expense> m;
    m.marshallObject(e, responsePayload);
    oResponse.setPayload(responsePayload);
}

} /* namespace resources */
} /* namespace myroomies */
