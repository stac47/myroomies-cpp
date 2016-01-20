#pragma once

#include <myroomies/resource/TransactionHandler.h>

namespace myroomies {
namespace resources {

class UserHandler : public TransactionHandler
{
public:
    void handleGET(const HttpRequest& iRequest, HttpResponse& oResponse) override;
    void handlePOST(const HttpRequest& iRequest, HttpResponse& oResponse) override;
};

} /* namespace resources */
} /* namespace myroomies */
