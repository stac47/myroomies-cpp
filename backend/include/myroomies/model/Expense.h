#pragma once

#include <string>
#include <vector>
#include <chrono>

#include <myroomies/bom/Marshaller.h>
#include <myroomies/bom/Unmarshaller.h>

#include <myroomies/model/ModelObject.h>

namespace myroomies {
namespace model {

struct Expense
{
    Key_t id;
    ForeignKey_t userId;
    std::chrono::time_point<std::chrono::system_clock> date;
    double amount;
    std::string title;
    std::string comment;
    std::vector<std::string> tags;
};

} /* namespace model */
} /* namespace myroomies */
