#include <string>

#include <myroomies/utils/db/SqlTools.h>

namespace myroomies {
namespace utils {
namespace db {

std::string GenerateSimpleSelectTemplate(const std::string& iTableName,
                                         const std::string& iColName)
{
    std::ostringstream os;
    os << "SELECT * FROM " << iTableName << " WHERE "
       << iColName << "=:" << iColName;
    return os.str();
}

std::string GenerateSelectAllTemplate(const std::string& iTableName)
{
    std::ostringstream os;
    os << "SELECT * FROM " << iTableName;
    return os.str();
}

} /* namespace db */
} /* namespace utils */
} /* namespace myroomies */
