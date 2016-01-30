#pragma once

#include <memory>
#include <functional>

#include <httpserver.hpp>

#include <myroomies/model/User.h>
#include <myroomies/bom/User.h>
#include <myroomies/resources/TransactionHandler.h>

namespace myroomies {
namespace services {

class ServiceRegistry;

} /* namespace services */
} /* namespace myroomies */

namespace myroomies {
namespace resources {

class ResourceBase: public httpserver::http_resource
{
public:
    ResourceBase(const std::shared_ptr<myroomies::services::ServiceRegistry>& iServiceRegistry,
                 const std::string& iUri,
                 bool iSecured);

    virtual ~ResourceBase();

    const std::string& getUri() const;

protected:
    bool performSecurity(const httpserver::http_request& iRequest,
                         myroomies::model::User& oLoggedUser);
    bool isSecured() const
    {
        return secured_;
    }

    const std::shared_ptr<myroomies::services::ServiceRegistry>& getServiceRegistry() const
    {
        return serviceRegistry_;
    }

private:
    const std::shared_ptr<myroomies::services::ServiceRegistry>& serviceRegistry_;
    bool secured_;
    std::string uri_;
};

template<typename TH>
class Resource : public ResourceBase
{
public:
    Resource(const std::shared_ptr<myroomies::services::ServiceRegistry>& iServiceRegistry,
             const std::string& iUri,
             bool iSecured)
      : ResourceBase(iServiceRegistry, iUri, iSecured) {}

    void render_GET(const httpserver::http_request& iRequest,
                    httpserver::http_response**) override final;
    void render_POST(const httpserver::http_request& iRequest,
                     httpserver::http_response**) override final;
    void render_PUT(const httpserver::http_request& iRequest,
                    httpserver::http_response**) override final;
    void render_DELETE(const httpserver::http_request& iRequest,
                       httpserver::http_response**) override final;
    void render_HEAD(const httpserver::http_request& iRequest,
                     httpserver::http_response**) override final;
    void render_CONNECT(const httpserver::http_request& iRequest,
                        httpserver::http_response**) override final;
    void render_TRACE(const httpserver::http_request& iRequest,
                      httpserver::http_response**) override final;
    void render_OPTIONS(const httpserver::http_request& iRequest,
                        httpserver::http_response**) override final;
    void render(const httpserver::http_request& iRequest,
                httpserver::http_response**) override final;

private:
    typedef std::function<void(TH&, const HttpRequest&, HttpResponse&)> HandlerFunction;
    void commonRender(const httpserver::http_request& iRequest,
                      httpserver::http_response** oResponse,
                      const HandlerFunction& iFunc);

};

template<typename TH>
void Resource<TH>::commonRender(const httpserver::http_request& iRequest,
                                httpserver::http_response** oResponse,
                                const HandlerFunction& iFunc)
{
    TH transactionHandler;
    myroomies::resources::HttpResponse response;
    if (isSecured())
    {
        myroomies::bom::User loggedUser;
        if (performSecurity(iRequest, loggedUser.user))
        {
            transactionHandler.setLoggedUser(loggedUser);
            transactionHandler.setServiceRegistry(getServiceRegistry());
            myroomies::resources::HttpRequest request(iRequest.get_path().substr(getUri().size()));
            request.setPayload(iRequest.get_content());
            iFunc(transactionHandler, request, response);
        }
        else
        {
            *oResponse = new httpserver::http_response(
                httpserver::http_response_builder("").basic_auth_fail_response()
            );
            return;
        }
    }
    *oResponse = new httpserver::http_response(
        httpserver::http_response_builder(
            response.getPayload(),
            response.getStatus(),
            "application/json; charset=utf-8").string_response()
    );
}

template<typename TH>
void Resource<TH>::render_GET(const httpserver::http_request& iRequest,
                              httpserver::http_response** oResponse)
{
    commonRender(iRequest, oResponse, &TH::handleGET);
}

template<typename TH>
void Resource<TH>::render_POST(const httpserver::http_request& iRequest,
                 httpserver::http_response** oResponse)
{
    commonRender(iRequest, oResponse, &TH::handlePOST);
}

template<typename TH>
void Resource<TH>::render_PUT(const httpserver::http_request& iRequest,
                httpserver::http_response** oResponse)
{
    commonRender(iRequest, oResponse, &TH::handlePUT);
}

template<typename TH>
void Resource<TH>::render_DELETE(const httpserver::http_request& iRequest,
                   httpserver::http_response** oResponse)
{
    commonRender(iRequest, oResponse, &TH::handleDELETE);
}

template<typename TH>
void Resource<TH>::render_HEAD(const httpserver::http_request& iRequest,
                 httpserver::http_response** oResponse)
{
}

template<typename TH>
void Resource<TH>::render_CONNECT(const httpserver::http_request& iRequest,
                    httpserver::http_response** oResponse)
{
    render(iRequest, oResponse);
}

template<typename TH>
void Resource<TH>::render_TRACE(const httpserver::http_request& iRequest,
                  httpserver::http_response** oResponse)
{
    render(iRequest, oResponse);
}

template<typename TH>
void Resource<TH>::render_OPTIONS(const httpserver::http_request& iRequest,
                                  httpserver::http_response** oResponse)
{
    render(iRequest, oResponse);
}

template<typename TH>
void Resource<TH>::render(const httpserver::http_request& iRequest,
                          httpserver::http_response** oResponse)
{
}

} /* namespace resources */
} /* namespace myroomies */
