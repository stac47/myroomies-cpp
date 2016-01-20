#pragma once

#include <string>
#include <vector>

#include <myroomies/bom/UnmarshallerBase.h>

namespace myroomies {
namespace bom {

template<typename ObjectType>
class Unmarshaller : public UnmarshallerBase
{
public:
    void unmarshall(const std::string& iStr, ObjectType& oObject);
};

} /* namespace bom */
} /* namespace myroomies */
