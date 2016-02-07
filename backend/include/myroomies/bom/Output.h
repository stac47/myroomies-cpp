#pragma once

#include <string>
#include <vector>
#include <memory>

#include <boost/algorithm/string/join.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace myroomies {
namespace bom {

class Output
{
public:
    Output();
    virtual ~Output();

    virtual void marshall(std::string& oOutputStr) = 0;

protected:
    void putValue(const std::string& iKey, bool iBool);
    void putValue(const std::string& iKey, unsigned int iUInt);
    void putValue(const std::string& iKey, int iIint);
    void putValue(const std::string& iKey, const std::string& iString);
    void putValue(const std::string& iKey, double iDouble);
    void putValue(const std::string& iKey, const boost::gregorian::date& iDate);
    void marshallObject(std::string& oStr);

private:
    class Impl;
    // Must be a shared_ptr. All copies should share the same instance of this
    // utility class.
    std::shared_ptr<Impl> pImpl_;
};

template<typename Collection>
void MarshallCollection(const Collection& iCollection, std::string& oStr)
{
    std::vector<std::string> marshalledObjects;
    for (auto o : iCollection)
    {
        std::string s;
        o.marshall(s);
        marshalledObjects.push_back(s);
    }
    oStr += "[";
    oStr += boost::algorithm::join(marshalledObjects, ",");
    oStr += "]";
}

} /* namespace bom */
} /* namespace myroomies */
