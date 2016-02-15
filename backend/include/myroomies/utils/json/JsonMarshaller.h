#pragma once

#include <ostream>
#include <string>
#include <vector>
#include <memory>

#include <boost/date_time/gregorian/gregorian.hpp>

namespace myroomies {
namespace utils {
namespace json {

class JsonMarshaller final
{
public:
    JsonMarshaller(std::ostream& oStream);

    void putValue(const std::string& iKey, bool iBool);
    void putValue(const std::string& iKey, unsigned int iUInt);
    void putValue(const std::string& iKey, int iIint);
    void putValue(const std::string& iKey, const std::string& iString);
    void putValue(const std::string& iKey, double iDouble);
    void putValue(const std::string& iKey, const boost::gregorian::date& iDate);

    void marshall();

private:
    class Impl;
    // Must be a shared_ptr. All copies should share the same instance of this
    // utility class.
    std::shared_ptr<Impl> pImpl_;
};

} /* namespace json */
} /* namespace utils */
} /* namespace myroomies */

