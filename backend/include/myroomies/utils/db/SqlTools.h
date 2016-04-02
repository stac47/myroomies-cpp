#pragma once

#include <string>
#include <sstream>

#include <myroomies/utils/StringUtils.h>

namespace myroomies {
namespace utils {
namespace db {

template<typename ... Args>
std::string GenerateInsertTemplate(const std::string& iTableName, Args&&... iColName)
{
    std::ostringstream os;
    os << "INSERT INTO " << iTableName
       << BuildCompositeStringHelper("(", ")", ",")(std::forward<Args>(iColName)...)
       << " VALUES"
       << BuildCompositeStringHelper("(:", ")", ",:")(std::forward<Args>(iColName)...);
    return os.str();
}
std::string GenerateSimpleSelectTemplate(const std::string& iTableName,
                                         const std::string& iColName);

std::string GenerateSelectAllTemplate(const std::string& iTableName);

} /* namespace db */
} /* namespace utils */
} /* namespace myroomies */
