#pragma once

namespace myroomies {
namespace utils {

class BuildCompositeStringHelper
{
public:
    BuildCompositeStringHelper(const std::string& iHeader = "",
                               const std::string& iTrailer = "",
                               const std::string& iSeparator = "")
      : header_(iHeader),
        trailer_(iTrailer),
        separator_(iSeparator),
        deepness_(0)
    {
        os_ << std::boolalpha;
    }

    std::string operator()()
    {
        return header_ + trailer_;
    }

    template<typename T>
    std::string operator()(T&& s)
    {
        if (deepness_ == 0)
        {
            os_ << header_;
        }
        os_ << s << trailer_;
        return os_.str();
    }


    template<typename T, typename ... Args>
    std::string operator()(T&& s, Args&&... args)
    {
        if (deepness_ == 0)
        {
            os_ << header_;
        }
        deepness_++;
        os_ << std::forward<T>(s);
        if (deepness_ > 0)
        {
            os_ << separator_;
        }
        (*this)(std::forward<Args>(args)...);
        return os_.str();
    }

private:
    std::ostringstream os_;
    std::string header_;
    std::string trailer_;
    std::string separator_;
    int deepness_;
};

template<typename T, typename ... Args>
std::string BuildSimpleCompositeString(T&& s, Args&&... args)
{
    return BuildCompositeStringHelper()(std::forward<T>(s), std::forward<Args>(args)...);
}

} /* namespace utils */
} /* namespace myroomies */
