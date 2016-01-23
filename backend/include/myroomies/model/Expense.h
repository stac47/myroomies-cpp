#pragma once

#include <string>
#include <vector>

#include <boost/date_time/gregorian/gregorian.hpp>

#include <myroomies/model/ModelObject.h>

namespace myroomies {
namespace model {

struct Expense
{
    Key_t id;
    ForeignKey_t userId;
    boost::gregorian::date date;
    double amount;
    std::string title;
    std::string comment;
    std::vector<std::string> tags;
};

} /* namespace model */
} /* namespace myroomies */
