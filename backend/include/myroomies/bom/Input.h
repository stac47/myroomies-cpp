#pragma once

#include <string>
#include <memory>
#include <iomanip>

#include <boost/date_time/gregorian/gregorian.hpp>

namespace myroomies {
namespace bom {

class Input
{
public:
    Input();
    Input(Input&&) = default;
    Input& operator=(Input&&) = default;
    virtual ~Input();

    void parse(const std::string& i);

protected:
    virtual void unmarshall() = 0;
    virtual void validate() const = 0;

    // Utility methods to be used in unmarshall method implementation
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
