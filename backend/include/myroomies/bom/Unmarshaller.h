#pragma once

#include <string>

namespace myroomies {
namespace bom {

class UnmarshallerBase {};

template<typename ObjectType>
class Unmarshaller : public UnmarshallerBase
{
public:
    void unmarshall(const std::string& iStr, ObjectType& oObject);
};

} /* namespace bom */
} /* namespace myroomies */
