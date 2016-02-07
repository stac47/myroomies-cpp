#pragma once

#include <string>

#include <myroomies/model/User.h>
#include <myroomies/bom/Input.h>

namespace myroomies {
namespace bom {

struct UserNew final : public myroomies::model::User,
                       public myroomies::bom::Input
{
    void unmarshall() override;
    void validate() const override;

    std::string password;
};

} /* namespace bom */
} /* namespace myroomies */
