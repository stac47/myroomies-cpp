#include <memory>
#include <typeinfo>
#include <typeindex>

#include <myroomies/utils/LoggingMacros.h>

#include <myroomies/services/ServiceInterface.h>

namespace myroomies {
namespace services {

class ServiceRegistry;

ServiceInterface::ServiceInterface()
{
    MYROOMIES_LOG_INFO("Service construction: " << std::type_index(typeid(this)).name());
}

ServiceInterface::~ServiceInterface()
{
    MYROOMIES_LOG_INFO("Service destruction: " << std::type_index(typeid(this)).name());
}

} /* namespace services */
} /* namespace myroomies */
