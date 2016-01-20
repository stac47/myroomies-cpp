#include <string>
#include <memory>
#include <chrono>
#include <ctime>

#include <time.h>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>

#include <myroomies/bom/MarshallCommon.h>
#include <myroomies/bom/UnmarshallerBase.h>

namespace myroomies {
namespace bom {

class UnmarshallerBase::Impl
{
public:
    void parse(const std::string& iStr)
    {
        json_.Parse(iStr.c_str());
    }

    void extractValue(const std::string& iStr, bool iOptional, bool& oBool)
    {
        const char* key = iStr.c_str();
        if (!json_.HasMember(key) && !iOptional)
        {
            return;
        }
        else
        {
            oBool = json_[key].GetBool();
        }
    }

    void extractValue(const std::string& iStr, bool iOptional, unsigned int& oUInt)
    {
        const char* key = iStr.c_str();
        if (!json_.HasMember(key) && !iOptional)
        {
            return;
        }
        else
        {
            oUInt = json_[key].GetUint();
        }
    }

    void extractValue(const std::string& iStr, bool iOptional, int& oInt)
    {
        const char* key = iStr.c_str();
        if (!json_.HasMember(key) && !iOptional)
        {
            return;
        }
        else
        {
            oInt = json_[key].GetInt();
        }
    }

    void extractValue(const std::string& iStr, bool iOptional, std::string& oString)
    {
        const char* key = iStr.c_str();
        if (!json_.HasMember(key) && !iOptional)
        {
            return;
        }
        else
        {
            oString = json_[key].GetString();
        }
    }

    void extractValue(const std::string& iStr, bool iOptional, double& oDouble)
    {
        const char* key = iStr.c_str();
        if (!json_.HasMember(key) && !iOptional)
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
        bool iOptional,
        std::chrono::time_point<std::chrono::system_clock>& oDate)
    {
        const char* key = iStr.c_str();
        if (!json_.HasMember(key) && !iOptional)
        {
            return;
        }
        else
        {
            std::string dateStr = json_[key].GetString();
            std::tm tm = {};
            if (nullptr == ::strptime(dateStr.c_str(), kCommonDateFormat.c_str(), &tm))
            {
                // TODO hadle error
            }
            oDate = std::chrono::system_clock::from_time_t(std::mktime(&tm));
        }
    }

private:
    rapidjson::Document json_;
};

UnmarshallerBase::UnmarshallerBase()
  : pImpl_(std::make_unique<Impl>())
{}

UnmarshallerBase::~UnmarshallerBase()
{}

void UnmarshallerBase::parse(const std::string& oStr)
{
    pImpl_->parse(oStr);
}

void UnmarshallerBase::extractValue(const std::string& iStr, bool iOptional, bool& oBool)
{
    pImpl_->extractValue(iStr, iOptional, oBool);
}

void UnmarshallerBase::extractValue(const std::string& iStr, bool iOptional, unsigned int& oUInt)
{
    pImpl_->extractValue(iStr, iOptional, oUInt);
}

void UnmarshallerBase::extractValue(const std::string& iStr, bool iOptional, int& oInt)
{
    pImpl_->extractValue(iStr, iOptional, oInt);
}

void UnmarshallerBase::extractValue(const std::string& iStr, bool iOptional, std::string& oString)
{
    pImpl_->extractValue(iStr, iOptional, oString);
}

void UnmarshallerBase::extractValue(const std::string& iStr, bool iOptional, double& oDouble)
{
    pImpl_->extractValue(iStr, iOptional, oDouble);
}

void UnmarshallerBase::extractValue(
    const std::string& iStr,
    bool iOptional,
    std::chrono::time_point<std::chrono::system_clock>& oDate)
{
    pImpl_->extractValue(iStr, iOptional, oDate);
}

} /* namespace bom */
} /* namespace myroomies */
