#ifndef __MONEYRESOURCE_H__
#define __MONEYRESOURCE_H__

#include <myroomies/resources/ResourceBase.h>

namespace myroomies {
namespace resources {

class MoneyResource : public ResourceBase
{
public:
    MoneyResource() : ResourceBase(true) {}

    void onGET(const httpserver::http_request& iRequest,
               httpserver::http_response**) override;
};

} // namespace resources
} // namespace myroomies
#endif /* __MONEYRESOURCE_H__ */
