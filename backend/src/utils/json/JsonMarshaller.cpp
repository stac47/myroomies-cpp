#include <string>
#include <sstream>
#include <memory>
#include <iomanip>
#include <ostream>

#include <boost/date_time/gregorian/gregorian.hpp>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/ostreamwrapper.h>

#include <myroomies/utils/json/JsonMarshaller.h>

using rapidjson::Document;
using rapidjson::Value;
using rapidjson::Writer;
using rapidjson::OStreamWrapper;
using rapidjson::Writer;

namespace myroomies {
namespace utils {
namespace json {

class JsonMarshaller::Impl
{
public:
    Impl(std::ostream& oStream)
      : os_(oStream)
    {
        json_.SetObject();
    }

    ~Impl()
    {}

    void putValue(const std::string& iKey, bool iBool)
    {
        Value key(iKey.c_str(), json_.GetAllocator());
        Value value(iBool);
        json_.AddMember(key, value, json_.GetAllocator());
    }

    void putValue(const std::string& iKey, unsigned int iUInt)
    {
        Value key(iKey.c_str(), json_.GetAllocator());
        Value value(iUInt);
        json_.AddMember(key, value, json_.GetAllocator());
    }

    void putValue(const std::string& iKey, int iInt)
    {
        Value key(iKey.c_str(), json_.GetAllocator());
        Value value(iInt);
        json_.AddMember(key, value, json_.GetAllocator());
    }

    void putValue(const std::string& iKey, const std::string& iString)
    {
        Value key(iKey.c_str(), json_.GetAllocator());
        Value value(iString, json_.GetAllocator());
        json_.AddMember(key, value, json_.GetAllocator());
    }

    void putValue(const std::string& iKey, double iDouble)
    {
        Value key(iKey.c_str(), json_.GetAllocator());
        Value value(iDouble);
        json_.AddMember(key, value, json_.GetAllocator());
    }

    void putValue(
        const std::string& iKey,
        const boost::gregorian::date& iDate)
    {
        Value key(iKey.c_str(), json_.GetAllocator());
        Value value(boost::gregorian::to_iso_extended_string(iDate), json_.GetAllocator());
        json_.AddMember(key, value, json_.GetAllocator());
    }

    void marshall()
    {
        OStreamWrapper osw(os_);
        Writer<OStreamWrapper> writer(osw);
        json_.Accept(writer);
    }

private:
    rapidjson::Document json_;
    std::ostream& os_;
};

JsonMarshaller::JsonMarshaller(std::ostream& oStream)
  : pImpl_(new Impl(oStream))
{}

void JsonMarshaller::putValue(const std::string& iKey, bool iBool)
{
    pImpl_->putValue(iKey, iBool);
}

void JsonMarshaller::putValue(const std::string& iKey, unsigned int iUInt)
{
    pImpl_->putValue(iKey, iUInt);
}

void JsonMarshaller::putValue(const std::string& iKey, int iInt)
{
    pImpl_->putValue(iKey, iInt);
}

void JsonMarshaller::putValue(const std::string& iKey, const std::string& iString)
{
    pImpl_->putValue(iKey, iString);
}

void JsonMarshaller::putValue(const std::string& iKey, double iDouble)
{
    pImpl_->putValue(iKey, iDouble);
}

void JsonMarshaller::putValue(
    const std::string& iKey,
    const boost::gregorian::date& iDate)
{
    pImpl_->putValue(iKey, iDate);
}

void JsonMarshaller::marshall()
{
    pImpl_->marshall();
}

} /* namespace json */
} /* namespace utils */
} /* namespace myroomies */
