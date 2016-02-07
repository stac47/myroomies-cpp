#pragma once

#include <string>

#include <myroomies/model/User.h>
#include <myroomies/bom/Output.h>

namespace myroomies {
namespace bom {

struct User final : public myroomies::model::User,
                    public myroomies::bom::Output
{
    void marshall(std::string& oOutputStr) override;
};


} /* namespace bom */
} /* namespace myroomies */
