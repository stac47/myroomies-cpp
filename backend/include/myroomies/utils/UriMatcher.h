#pragma once

#include <string>
#include <sstream>
#include <stdexcept>
#include <regex>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/date_time/gregorian/greg_date.hpp>

namespace myroomies {
namespace utils {

class UriMatcherException : public std::runtime_error
{
public:
    explicit UriMatcherException(const std::string& iWhat)
      : std::runtime_error(iWhat)
    {}

    explicit UriMatcherException(const char* iWhat)
      : std::runtime_error(iWhat)
    {}
};

class UriMatcher
{
public:
    UriMatcher(const std::string& iRegex);
    UriMatcher(const UriMatcher&) = delete;
    UriMatcher& operator=(const UriMatcher&) = delete;

    bool match(const std::string& iUri);

    template<typename T>
    T get(unsigned int iGroupNb);

private:
    std::regex regex_;
    std::vector<std::string> groups_;
};

template<typename T>
T UriMatcher::get(unsigned int iGroupNb)
{
    if (iGroupNb >= groups_.size())
    {
        std::ostringstream os;
        os << "Found only " << groups_.size() << " groups "
           << "and trying to access " << iGroupNb + 1 << " th group";
        throw UriMatcherException(os.str());
    }
    try
    {
        return boost::lexical_cast<T>(groups_[iGroupNb]);
    }
    catch (const boost::bad_lexical_cast&)
    {
        std::ostringstream os;
        os << "Lexical cast from std::string to " << typeid(T).name();
        throw UriMatcherException(os.str());
    }
}

template<>
boost::gregorian::date UriMatcher::get(unsigned int iGroupNb);


} /* namespace utils */
} /* namespace myroomies */
