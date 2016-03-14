#pragma once

#include <string>

namespace myroomies {
namespace model {

const std::string kColRowId = "rowid";

bool CreateTables(const std::string& iPath, bool iCreateIfNotExists);

class DataAccess
{
public:
    DataAccess(const std::string& iDatabase)
      : database_(iDatabase)
    {}

    virtual ~DataAccess()
    {}

    std::string getDatabase() const
    {
        return database_;
    }

private:
    std::string database_;
};

} /* namespace model */
} /* namespace myroomies */
