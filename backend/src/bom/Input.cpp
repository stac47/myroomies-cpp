#include <string>
#include <memory>

#include <boost/date_time/gregorian/gregorian.hpp>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>

#include <myroomies/bom/Input.h>

namespace myroomies {
namespace bom {

class Input::Impl
{
public:
    void parse(const std::string& iStr)
    {
        json_.Parse(iStr.c_str());
    }

    void extractValue(const std::string& iStr, bool iMandatory, bool& oBool)
    {
        const char* key = iStr.c_str();
        if (!json_.HasMember(key) && !iMandatory)
        {
            return;
        }
        else
        {
            oBool = json_[key].GetBool();
        }
    }

    void extractValue(const std::string& iStr, bool iMandatory, unsigned int& oUInt)
    {
        const char* key = iStr.c_str();
        if (!json_.HasMember(key) && !iMandatory)
        {
            return;
        }
        else
        {
            oUInt = json_[key].GetUint();
        }
    }

    void extractValue(const std::string& iStr, bool iMandatory, int& oInt)
    {
        const char* key = iStr.c_str();
        if (!json_.HasMember(key) && !iMandatory)
        {
            return;
        }
        else
        {
            oInt = json_[key].GetInt();
        }
    }

    void extractValue(const std::string& iStr, bool iMandatory, std::string& oString)
    {
        const char* key = iStr.c_str();
        if (!json_.HasMember(key) && !iMandatory)
        {
            return;
        }
        else
        {
            oString = json_[key].GetString();
        }
    }

    void extractValue(const std::string& iStr, bool iMandatory, double& oDouble)
    {
        const char* key = iStr.c_str();
        if (!json_.HasMember(key) && !iMandatory)
        {
            return;
        }
        else
        {
            oDouble = json_[key].GetDouble();
        }
    }

    void extractValue(
        const std::string& iStr,
        bool iMandatory,
        boost::gregorian::date& oDate)
    {
        const char* key = iStr.c_str();
        if (!json_.HasMember(key) && !iMandatory)
        {
            return;
        }
        else
        {
            std::string dateStr = json_[key].GetString();
            oDate = boost::gregorian::from_string(dateStr);
        }
    }

private:
    rapidjson::Document json_;
};

Input::Input()
  : pImpl_(std::make_unique<Impl>())
{}

Input::~Input()
{}

void Input::parse(const std::string& iInputStr)
{
    pImpl_->parse(iInputStr);
    unmarshall();
    validate();
}

void Input::extractValue(const std::string& iStr, bool iMandatory, bool& oBool)
{
    pImpl_->extractValue(iStr, iMandatory, oBool);
}

void Input::extractValue(const std::string& iStr, bool iMandatory, unsigned int& oUInt)
{
    pImpl_->extractValue(iStr, iMandatory, oUInt);
}

void Input::extractValue(const std::string& iStr, bool iMandatory, int& oInt)
{
    pImpl_->extractValue(iStr, iMandatory, oInt);
}

void Input::extractValue(const std::string& iStr, bool iMandatory, std::string& oString)
{
    pImpl_->extractValue(iStr, iMandatory, oString);
}

void Input::extractValue(const std::string& iStr, bool iMandatory, double& oDouble)
{
    pImpl_->extractValue(iStr, iMandatory, oDouble);
}

void Input::extractValue(
    const std::string& iStr,
    bool iMandatory,
    boost::gregorian::date& oDate)
{
    pImpl_->extractValue(iStr, iMandatory, oDate);
}

} /* namespace bom */
} /* namespace myroomies */
