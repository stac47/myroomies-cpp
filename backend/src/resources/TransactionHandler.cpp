#include <string>
#include <memory>

#include <myroomies/services/ServiceRegistry.h>
#include <myroomies/resources/TransactionHandler.h>

namespace myroomies {
namespace resources {

TransactionHandler::TransactionHandler()
{}

TransactionHandler::~TransactionHandler()
{}

std::shared_ptr<myroomies::services::ServiceRegistry> TransactionHandler::getServiceRegistry() const
{
    return serviceRegistry_.lock();
}

void TransactionHandler::setServiceRegistry(
    const std::weak_ptr<myroomies::services::ServiceRegistry>& iServiceRegistry)
{
    serviceRegistry_ = iServiceRegistry;
}

const std::unique_ptr<const myroomies::model::User>& TransactionHandler::getLoggedUser() const
{
    return loggedUser_;
}

void TransactionHandler::setLoggedUser(const myroomies::model::User& iLoggedUser)
{
    loggedUser_ = std::make_unique<const myroomies::model::User>(iLoggedUser);
}

void TransactionHandler::handleGET(const HttpRequest& iRequest, HttpResponse& oResponse) {}

void TransactionHandler::handlePOST(const HttpRequest& iRequest, HttpResponse& oResponse) {}

void TransactionHandler::handlePUT(const HttpRequest& iRequest, HttpResponse& oResponse) {}

void TransactionHandler::handleDELETE(const HttpRequest& iRequest, HttpResponse& oResponse) {}

} /* namespace resources */
} /* namespace myroomies */
