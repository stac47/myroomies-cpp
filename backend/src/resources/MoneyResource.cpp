#include <httpserver.hpp>

#include <myroomies/resources/MoneyResource.h>

using httpserver::http_response_builder;
using httpserver::http_response;

namespace myroomies {
namespace resources {

void MoneyResource::onGET(const httpserver::http_request& iRequest,
                          httpserver::http_response** oResponse)
{
    *oResponse = new http_response(
        http_response_builder("Hello world", 200, "text/plain").string_response()
    );
}

} // namespace resources
} // namespace myroomies
