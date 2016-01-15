#pragma once

#include <myroomies/resources/ResourceBase.h>

namespace myroomies {
namespace resources {

class BalanceResource : public ResourceBase
{
public:
    BalanceResource() : ResourceBase(true) {}

    void onGET(const httpserver::http_request& iRequest,
               httpserver::http_response**) override;
};

} /* namespace resources */
} /* namespace myroomies */
