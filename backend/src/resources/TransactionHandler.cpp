#include <string>
#include <memory>

#include <myroomies/bom/User.h>

#include <myroomies/services/ServiceRegistry.h>

#include <myroomies/resources/TransactionHandler.h>

using myroomies::services::ServiceRegistry;

namespace myroomies {
namespace resources {

TransactionHandler::TransactionHandler()
{}

TransactionHandler::~TransactionHandler()
{}

const std::shared_ptr<ServiceRegistry>& TransactionHandler::getServiceRegistry() const
{
    return serviceRegistry_;
}

void TransactionHandler::setServiceRegistry(const std::shared_ptr<ServiceRegistry>& iServiceRegistry)
{
    serviceRegistry_ = iServiceRegistry;
}

const std::unique_ptr<const myroomies::bom::User>& TransactionHandler::getLoggedUser() const
{
    return loggedUser_;
}

void TransactionHandler::setLoggedUser(const myroomies::bom::User& iLoggedUser)
{
    loggedUser_ = std::make_unique<const myroomies::bom::User>(iLoggedUser);
}

void TransactionHandler::handleGET(const HttpRequest& iRequest, HttpResponse& oResponse) {}

void TransactionHandler::handlePOST(const HttpRequest& iRequest, HttpResponse& oResponse) {}

void TransactionHandler::handlePUT(const HttpRequest& iRequest, HttpResponse& oResponse) {}

void TransactionHandler::handleDELETE(const HttpRequest& iRequest, HttpResponse& oResponse) {}

} /* namespace resources */
} /* namespace myroomies */
