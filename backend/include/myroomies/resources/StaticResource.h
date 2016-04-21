#pragma once

#include <boost/filesystem.hpp>

#include <httpserver.hpp>

namespace myroomies {
namespace resources {

class StaticResource : public httpserver::http_resource
{
public:
    explicit StaticResource(const boost::filesystem::path& iBackendPath);

    void render(const httpserver::http_request& iRequest,
                httpserver::http_response**) override;

private:
    boost::filesystem::path staticRootPath_;
};

} /* namespace resources */
} /* namespace myroomies */
