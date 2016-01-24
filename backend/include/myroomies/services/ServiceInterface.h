#pragma once

#include <memory>

namespace myroomies {
namespace services {

class ServiceRegistry;

class ServiceInterface
{
public:
    ServiceInterface() = delete;
    ServiceInterface(const ServiceInterface&) = delete;
    ServiceInterface& operator=(const ServiceInterface&) = delete;

    virtual ~ServiceInterface();

protected:
    ServiceInterface(const std::shared_ptr<ServiceRegistry>& iServiceRegistry);

    std::shared_ptr<ServiceRegistry> getServiceRegistry();

private:
    std::weak_ptr<ServiceRegistry> serviceRegistry_;
};

} /* namespace services */
} /* namespace myroomies */
