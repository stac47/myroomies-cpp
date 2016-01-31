#pragma once

#include <string>
#include <vector>

#include <boost/date_time/gregorian/gregorian.hpp>

#include <myroomies/utils/db/Def.h>

namespace myroomies {
namespace model {

struct Expense
{
    myroomies::utils::db::Key_t id;
    myroomies::utils::db::ForeignKey_t userId;
    myroomies::utils::db::ForeignKey_t houseshareId;
    boost::gregorian::date date;
    double amount;
    std::string title;
    std::string comment;
    std::vector<std::string> tags;
};

} /* namespace model */
} /* namespace myroomies */
