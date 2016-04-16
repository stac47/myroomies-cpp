#pragma once

#include <string>

#include <boost/serialization/nvp.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/greg_serialize.hpp>

#include <myroomies/utils/db/Def.h>

namespace myroomies {
namespace bom {

struct Expense
{
    myroomies::utils::db::Key_t id;
    myroomies::utils::db::ForeignKey_t userId;
    boost::gregorian::date date;
    double amount;
    std::string title;
    std::string comment;
    std::vector<std::string> tags;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar & BOOST_SERIALIZATION_NVP(id)
           & BOOST_SERIALIZATION_NVP(userId)
           & BOOST_SERIALIZATION_NVP(date)
           & BOOST_SERIALIZATION_NVP(amount)
           & BOOST_SERIALIZATION_NVP(title)
           & BOOST_SERIALIZATION_NVP(comment)
           & BOOST_SERIALIZATION_NVP(tags);
    }
};

struct ExpenseNew final : public Expense
{
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar & BOOST_SERIALIZATION_NVP(date)
           & BOOST_SERIALIZATION_NVP(amount)
           & BOOST_SERIALIZATION_NVP(title)
           & BOOST_SERIALIZATION_NVP(comment)
           & BOOST_SERIALIZATION_NVP(tags);
    }
};

} /* namespace bom */
} /* namespace myroomies */
