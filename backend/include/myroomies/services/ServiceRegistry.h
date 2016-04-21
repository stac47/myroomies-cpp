#pragma once

#include <memory>
#include <map>
#include <typeindex>
#include <typeinfo>

#include <myroomies/utils/Configuration.h>
#include <myroomies/services/ServiceInterface.h>

namespace myroomies {
namespace services {

class ServiceRegistry : public std::enable_shared_from_this<ServiceRegistry>
{
public:
    explicit ServiceRegistry(const myroomies::utils::Configuration& iConfig);

    ServiceRegistry(const ServiceRegistry&) = delete;
    ServiceRegistry& operator=(const ServiceRegistry&) = delete;

    template<typename T>
    std::shared_ptr<T> get();

private:
    template<typename T>
    void registerService(const std::shared_ptr<T>& iService);

    std::map<std::type_index, std::shared_ptr<ServiceInterface>> services_;
    const myroomies::utils::Configuration config_;
};

template<typename T>
void ServiceRegistry::registerService(const std::shared_ptr<T>& iService)
{
    services_[std::type_index(typeid(T))] = std::shared_ptr<T>(iService);
}

template<typename T>
std::shared_ptr<T> ServiceRegistry::get()
{
    // TODO mutex here
    if (services_.find(std::type_index(typeid(T))) == services_.end())
    {
        registerService(T::BuildFromConfig(shared_from_this(), config_));
    }
    return std::dynamic_pointer_cast<T>(services_[std::type_index(typeid(T))]);
}

} /* namespace services */
} /* namespace myroomies */
