#pragma once

#include <string>
#include <vector>
#include <chrono>

namespace myroomies {
namespace model {

struct Expense
{
    uint32_t id;
    uint32_t userId;
    std::chrono::time_point<std::chrono::system_clock> date;
    double amount;
    std::string title;
    std::string comment;
    std::vector<std::string> tags;
};

} /* namespace model */
} /* namespace myroomies */
