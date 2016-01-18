#pragma once

#include <string>
#include <vector>

#include <boost/algorithm/string/join.hpp>

namespace myroomies {
namespace bom {

template<typename ObjectType>
class Marshaller
{
public:
    void marshallObject(const ObjectType& iObject, std::string& oStr);

    template<typename Collection>
    void marshallCollection(const Collection& iCollection, std::string& oStr)
    {
        std::vector<std::string> marshalledObjects;
        for (auto o : iCollection)
        {
            std::string s;
            marshallObject(o, s);
            marshalledObjects.push_back(s);
        }
        oStr += "[";
        oStr += boost::algorithm::join(marshalledObjects, ",");
        oStr += "]";
    }
};

} /* namespace bom */
} /* namespace myroomies */
