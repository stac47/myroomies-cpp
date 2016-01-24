#include <myroomies/utils/Configuration.h>

#include <myroomies/services/ServiceRegistry.h>

namespace myroomies {
namespace services {

ServiceRegistry::ServiceRegistry(const myroomies::utils::Configuration& iConfig)
  : config_(iConfig)
{}

void ServiceRegistry::cleanUp()
{
    // TODO mutex here
    services_.clear();
}

} /* namespace services */
} /* namespace myroomies */
