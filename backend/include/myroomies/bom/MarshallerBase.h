#pragma once

#include <string>
#include <memory>
#include <chrono>

namespace myroomies {
namespace bom {

class MarshallerBase
{
public:
    MarshallerBase();
    virtual ~MarshallerBase();

protected:
    void putValue(const std::string& iKey, bool iBool);
    void putValue(const std::string& iKey, unsigned int iUInt);
    void putValue(const std::string& iKey, int iIint);
    void putValue(const std::string& iKey, const std::string& iString);
    void putValue(const std::string& iKey, double iDouble);
    void putValue(
        const std::string& iKey,
        const std::chrono::time_point<std::chrono::system_clock>& iDate);
    void marshall(std::string& oStr);

private:
    class Impl;
    std::unique_ptr<Impl> pImpl_;
};

} /* namespace bom */
} /* namespace myroomies */
