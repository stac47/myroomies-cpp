#include <httpserver.hpp>

#include <myroomies/resources/BalanceResource.h>

using httpserver::http_response_builder;
using httpserver::http_response;

namespace myroomies {
namespace resources {

void BalanceResource::onGET(const httpserver::http_request& iRequest,
                            httpserver::http_response** oResponse)
{
    *oResponse = new http_response(
        http_response_builder("Balanced", 200, "text/plain").string_response()
    );
}

} /* namespace resources */
} /* namespace myroomies */
