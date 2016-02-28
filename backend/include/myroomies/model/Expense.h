#pragma once

#include <string>
#include <vector>

#include <boost/date_time/gregorian/gregorian.hpp>

#include <myroomies/utils/db/Def.h>

namespace myroomies {
namespace model {

const std::string kTableExpense = "expense";

struct Expense
{
    static const std::string kColId;
    static const std::string kColUserId;
    static const std::string kColHouseshareId;
    static const std::string kColDate;
    static const std::string kColAmount;
    static const std::string kColTitle;
    static const std::string kColComment;

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
