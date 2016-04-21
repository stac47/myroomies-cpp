#pragma once

#include <map>
#include <chrono>
#include <memory>
#include <mutex>

#include <myroomies/model/User.h>

namespace myroomies {
namespace services {

class UserCache
{
public:
    explicit UserCache(const std::chrono::seconds& iTimeToLive);

    std::unique_ptr<myroomies::model::User> check(const std::string& iLogin);
    void push(const myroomies::model::User& iUser);

private:
    struct CompareUsers
    {
        bool operator()(const myroomies::model::User& iUser1,
                        const myroomies::model::User& iUser2)
        {
            return iUser1.id < iUser2.id;
        }
    };

    std::chrono::seconds ttl_;
    std::mutex cacheMutex_;
    std::map<myroomies::model::User,
             std::chrono::steady_clock::time_point,
             CompareUsers> cache_;
};

} /* namespace services */
} /* namespace myroomies */
