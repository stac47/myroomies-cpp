#ifndef __HTTPUTILS_H__
#define __HTTPUTILS_H__

#include <string>

#include <boost/filesystem.hpp>

namespace myroomies {
namespace utils {

class HttpUtils final
{
public:
    static const std::string getContentType(const boost::filesystem::path&);
};

} // namespace utils
} // namespace myroomies
#endif /* __HTTPUTILS_H__ */
