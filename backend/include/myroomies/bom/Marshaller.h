#pragma once

#include <string>

namespace myroomies {
namespace bom {

template<typename ObjectType>
class Marshaller
{
public:
    void marshall(ObjectType& iObject, std::string& oStr);
};

} /* namespace bom */
} /* namespace myroomies */
