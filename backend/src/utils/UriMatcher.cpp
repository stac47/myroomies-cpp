#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <exception>

#include <boost/date_time/gregorian/gregorian.hpp>

#include <myroomies/utils/UriMatcher.h>

namespace myroomies {
namespace utils {

UriMatcher::UriMatcher(const std::string& iRegex)
{
    try
    {
        regex_ = std::regex(iRegex, std::regex::icase);
    }
    catch (const std::regex_error& e)
    {
        throw UriMatcherException(e.what());
    }
}

bool UriMatcher::match(const std::string& iUri)
{
    groups_.clear();
    std::smatch results;
    if (!std::regex_match(iUri, results, regex_))
    {
        return false;
    }
    std::transform(
        results.cbegin(),
        results.cend(),
        std::back_inserter(groups_),
        [] (const auto& match) {return match.str();});

    return true;
}

template<>
boost::gregorian::date UriMatcher::get(unsigned int iGroupNb)
{
    auto dateStr = groups_[iGroupNb];
    try
    {
        return boost::gregorian::from_undelimited_string(dateStr);
    }
    catch (const std::exception&)
    {
        throw UriMatcherException("Invalid date format [" + dateStr + "]");
    }
}


} /* namespace utils */
} /* namespace myroomies */
