#pragma once

#include <memory>
#include <string>

namespace myroomies {
namespace services {

class ServiceRegistry;

class ServiceInterface
{
public:
    ServiceInterface(const std::string& iServiceName);
    ServiceInterface(const ServiceInterface&) = delete;
    ServiceInterface& operator=(const ServiceInterface&) = delete;
    virtual ~ServiceInterface();

private:
    std::string name_;
};

} /* namespace services */
} /* namespace myroomies */
