#include <map>
#include <mutex>
#include <algorithm>
#include <chrono>
#include <memory>

#include <myroomies/model/User.h>
#include <myroomies/utils/LoggingMacros.h>

#include "UserCache.h"

namespace myroomies {
namespace services {

UserCache::UserCache(const std::chrono::seconds& iTimeToLive)
  : ttl_(iTimeToLive)
{}

std::unique_ptr<myroomies::model::User> UserCache::check(const std::string& iLogin)
{
    std::lock_guard<std::mutex> guard(cacheMutex_);
    auto it = std::find_if(cache_.begin(), cache_.end(),
        [&iLogin] (auto p) {return p.first.login == iLogin;});
    if (it == std::end(cache_))
    {
        MYROOMIES_LOG_INFO("User [login=" << iLogin << "] "
                           << "not found in the cache");
        return nullptr;
    }
    auto now = std::chrono::steady_clock::now();
    if (it->second + ttl_ < now)
    {
        MYROOMIES_LOG_INFO("User [login=" << iLogin << "] "
                           << "found in the cache but his last "
                           << "login was done after more than " << ttl_.count()
                           << "ms");
        cache_.erase(it);
        return nullptr;
    }
    else
    {
        it->second = now;
    }
    return std::make_unique<myroomies::model::User>(it->first);
}

void UserCache::push(const myroomies::model::User& iUser)
{
    std::lock_guard<std::mutex> guard(cacheMutex_);
    cache_[iUser] = std::chrono::steady_clock::now();
}

} /* namespace services */
} /* namespace myroomies */

