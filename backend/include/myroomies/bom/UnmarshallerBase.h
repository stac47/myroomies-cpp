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

    void extractValue(const std::string& iStr, bool iMandatory, bool& oBool);
    void extractValue(const std::string& iStr, bool iMandatory, unsigned int& oUInt);
    void extractValue(const std::string& iStr, bool iMandatory, int& oInt);
    void extractValue(const std::string& iStr, bool iMandatory, std::string& oString);
    void extractValue(const std::string& iStr, bool iMandatory, double& oDouble);
    void extractValue(
        const std::string& iStr,
        bool iMandatory,
        boost::gregorian::date& oDate);

private:
    class Impl;
    std::unique_ptr<Impl> pImpl_;
};

} /* namespace bom */
} /* namespace myroomies */
