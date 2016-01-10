#ifndef __RESOURCEBASE_H__
#define __RESOURCEBASE_H__

#include <httpserver.hpp>

namespace myroomies {
namespace resources {

class ResourceBase : public httpserver::http_resource
{
public:
    ResourceBase(bool iSecured);

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

protected:
    virtual void onGET(const httpserver::http_request& iRequest,
                       httpserver::http_response**);
    virtual void onPOST(const httpserver::http_request& iRequest,
                        httpserver::http_response**);
    virtual void onPUT(const httpserver::http_request& iRequest,
                       httpserver::http_response**);
    virtual void onDELETE(const httpserver::http_request& iRequest,
                          httpserver::http_response**);

private:
    bool secured_;
};

} // namespace resources
} // namespace myroomies

#endif /* __RESOURCEBASE_H__ */
