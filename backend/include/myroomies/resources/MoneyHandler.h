#pragma once

#include <myroomies/resources/TransactionHandler.h>

namespace myroomies {
namespace resources {

class MoneyHandler : public TransactionHandler
{
public:
    void handleGET(const HttpRequest& iRequest, HttpResponse& oResponse) override;
    void handlePOST(const HttpRequest& iRequest, HttpResponse& oResponse) override;
    void handleDELETE(const HttpRequest& iRequest, HttpResponse& oResponse) override;
};

} /* namespace resources */
} /* namespace myroomies */
