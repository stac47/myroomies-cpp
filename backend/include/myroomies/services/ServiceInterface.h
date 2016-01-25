#pragma once

#include <memory>

namespace myroomies {
namespace services {

class ServiceRegistry;

class ServiceInterface
{
public:
    ServiceInterface();
    ServiceInterface(const ServiceInterface&) = delete;
    ServiceInterface& operator=(const ServiceInterface&) = delete;

    virtual ~ServiceInterface();
};

} /* namespace services */
} /* namespace myroomies */
