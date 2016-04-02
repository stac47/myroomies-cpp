#pragma once

#include <string>

#include <boost/serialization/nvp.hpp>

#include <myroomies/model/Expense.h>

#include <boost/date_time/gregorian/greg_serialize.hpp>

namespace myroomies {
namespace bom {

struct Expense final : public myroomies::model::Expense
{
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

struct ExpenseNew final : public myroomies::model::Expense
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
