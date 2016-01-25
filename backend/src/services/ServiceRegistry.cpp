#include <myroomies/utils/Configuration.h>

#include <myroomies/services/ServiceRegistry.h>

namespace myroomies {
namespace services {

ServiceRegistry::ServiceRegistry(const myroomies::utils::Configuration& iConfig)
  : config_(iConfig)
{}

} /* namespace services */
} /* namespace myroomies */
