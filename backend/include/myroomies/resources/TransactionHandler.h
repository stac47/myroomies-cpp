#pragma once

#include <memory>
#include <string>

#include <myroomies/model/User.h>

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

class HttpRequest : public HttpMessage {
};

class HttpResponse : public HttpMessage {};

class TransactionHandler
{
public:
    TransactionHandler();
    virtual ~TransactionHandler();

    const std::unique_ptr<const myroomies::model::User>& getLoggedUser() const;
    void setLoggedUser(const myroomies::model::User& iLoggedUser);

    virtual void handleGET(const HttpRequest& iRequest, HttpResponse& oResponse);
    virtual void handlePOST(const HttpRequest& iRequest, HttpResponse& oResponse);
    virtual void handlePUT(const HttpRequest& iRequest, HttpResponse& oResponse);
    virtual void handleDELETE(const HttpRequest& iRequest, HttpResponse& oResponse);

private:
    std::unique_ptr<const myroomies::model::User> loggedUser_;
};

} /* namespace resources */
} /* namespace myroomies */
