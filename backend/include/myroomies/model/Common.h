#pragma once

#include <string>

namespace myroomies {
namespace model {

const std::string kColRowId = "rowid";

bool CreateTables(const std::string& iPath, bool iCreateIfNotExists);

} /* namespace model */
} /* namespace myroomies */
