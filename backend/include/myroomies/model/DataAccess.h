#pragma once

#include <string>
#include <memory>

#include <soci/soci.h>

namespace myroomies {
namespace model {

class DataAccess
{
public:
    static void ConfigureConnectionPool(size_t iPoolSize,
                                        const std::string& iDatabase);
    DataAccess();
    virtual ~DataAccess();

protected:
    soci::session& getSession();

private:
    soci::session session_;
};

} /* namespace model */
} /* namespace myroomies */
