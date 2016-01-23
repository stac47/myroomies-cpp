#pragma once

#include <string>
#include <memory>

#include <boost/date_time/gregorian/gregorian.hpp>

namespace myroomies {
namespace bom {

class UnmarshallerBase
{
public:
    UnmarshallerBase();
    virtual ~UnmarshallerBase();

protected:
    void parse(const std::string& iStr);

    void extractValue(const std::string& iStr, bool iOptional, bool& oBool);
    void extractValue(const std::string& iStr, bool iOptional, unsigned int& oUInt);
    void extractValue(const std::string& iStr, bool iOptional, int& oInt);
    void extractValue(const std::string& iStr, bool iOptional, std::string& oString);
    void extractValue(const std::string& iStr, bool iOptional, double& oDouble);
    void extractValue(
        const std::string& iStr,
        bool iOptional,
        boost::gregorian::date& oDate);

private:
    class Impl;
    std::unique_ptr<Impl> pImpl_;
};

} /* namespace bom */
} /* namespace myroomies */
