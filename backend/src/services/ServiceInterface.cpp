#include <memory>
#include <string>

#include <myroomies/utils/LoggingMacros.h>

#include <myroomies/services/ServiceInterface.h>

namespace myroomies {
namespace services {

class ServiceRegistry;

ServiceInterface::ServiceInterface(const std::string& iName)
  : name_(iName)
{
    MYROOMIES_LOG_INFO("Service construction: " << name_);
}

ServiceInterface::~ServiceInterface()
{
    MYROOMIES_LOG_INFO("Service destruction: " << name_);
}

} /* namespace services */
} /* namespace myroomies */
