#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>

#include <boost/algorithm/string.hpp>

#include <myroomies/bom/User.h>
#include <myroomies/services/ServiceRegistry.h>

namespace myroomies {
namespace resources {

class HttpMessage
{
public:
    HttpMessage() {};
    virtual ~HttpMessage() {}

    void setPayload(const std::string& iPayload)
    {
        payload_ = iPayload;
    }

    const std::string& getPayload() const
    {
        return payload_;
    }

private:
    std::string payload_;
};

class HttpRequest : public HttpMessage
{
public:
    HttpRequest(const std::string& iPath)
      : HttpMessage(),
        path_(iPath) {}

    std::vector<std::string> getPathPieces() const
    {
        std::vector<std::string> ret;
        boost::split(ret, path_, boost::is_any_of("/"));
        return ret;
    }

    std::map<std::string, std::string> getParameters() const
    {
        std::map<std::string, std::string> ret;
        return ret;
    }

private:
    std::string path_;
};

class HttpResponse : public HttpMessage
{
public:
    void setStatus(unsigned int iStatus)
    {
        status_ = iStatus;
    }

    unsigned int getStatus() const
    {
        return status_;
    }
private:
    unsigned int status_;
};

class TransactionHandler
{
public:
    TransactionHandler();
    virtual ~TransactionHandler();

    const std::unique_ptr<const myroomies::bom::User>& getLoggedUser() const;
    void setLoggedUser(const myroomies::bom::User& iLoggedUser);

    const std::shared_ptr<myroomies::services::ServiceRegistry>& getServiceRegistry() const;
    void setServiceRegistry(const std::shared_ptr<myroomies::services::ServiceRegistry>& iServiceRegistry);

    virtual void handleGET(const HttpRequest& iRequest, HttpResponse& oResponse);
    virtual void handlePOST(const HttpRequest& iRequest, HttpResponse& oResponse);
    virtual void handlePUT(const HttpRequest& iRequest, HttpResponse& oResponse);
    virtual void handleDELETE(const HttpRequest& iRequest, HttpResponse& oResponse);

private:
    std::unique_ptr<const myroomies::bom::User> loggedUser_;
    std::shared_ptr<myroomies::services::ServiceRegistry> serviceRegistry_;
};

} /* namespace resources */
} /* namespace myroomies */
