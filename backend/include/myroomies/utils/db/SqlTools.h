#pragma once

#include <string>
#include <sstream>

#include <myroomies/utils/StringUtils.h>

namespace myroomies {
namespace utils {
namespace db {

template<typename ... Args>
static std::string GenerateInsertTemplate(const std::string& iTableName, Args&&... iColName)
{
    std::ostringstream os;
    os << "INSERT INTO " << iTableName
       << BuildCompositeStringHelper("(", ")", ",")(std::forward<Args>(iColName)...)
       << " VALUES"
       << BuildCompositeStringHelper("(:", ")", ",:")(std::forward<Args>(iColName)...);
    return os.str();
}

static std::string GenerateSimpleSelectTemplate(const std::string& iTableName,
                                                const std::string& iColName)
{
    std::ostringstream os;
    os << "SELECT * FROM " << iTableName << " WHERE "
       << iColName << "=:" << iColName;
    return os.str();
}

} /* namespace db */
} /* namespace utils */
} /* namespace myroomies */
