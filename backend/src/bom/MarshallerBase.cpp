#include <string>
#include <sstream>
#include <memory>
#include <iomanip>

#include <boost/date_time/gregorian/gregorian.hpp>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <myroomies/bom/MarshallerBase.h>

using rapidjson::Document;
using rapidjson::Value;
using rapidjson::Writer;
using rapidjson::StringBuffer;

namespace myroomies {
namespace bom {

class MarshallerBase::Impl
{
public:
    Impl()
    {
        json_.SetObject();
    }

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

    void marshall(std::string& oStr)
    {
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        json_.Accept(writer);
        oStr = buffer.GetString();
    }

private:
    rapidjson::Document json_;
};

MarshallerBase::MarshallerBase()
  : pImpl_(std::make_unique<Impl>())
{}

MarshallerBase::~MarshallerBase()
{}

void MarshallerBase::putValue(const std::string& iKey, bool iBool)
{
    pImpl_->putValue(iKey, iBool);
}

void MarshallerBase::putValue(const std::string& iKey, unsigned int iUInt)
{
    pImpl_->putValue(iKey, iUInt);
}

void MarshallerBase::putValue(const std::string& iKey, int iInt)
{
    pImpl_->putValue(iKey, iInt);
}

void MarshallerBase::putValue(const std::string& iKey, const std::string& iString)
{
    pImpl_->putValue(iKey, iString);
}

void MarshallerBase::putValue(const std::string& iKey, double iDouble)
{
    pImpl_->putValue(iKey, iDouble);
}

void MarshallerBase::putValue(
    const std::string& iKey,
    const boost::gregorian::date& iDate)
{
    pImpl_->putValue(iKey, iDate);
}

void MarshallerBase::marshall(std::string& oStr)
{
    pImpl_->marshall(oStr);
}


} /* namespace bom */
} /* namespace myroomies */