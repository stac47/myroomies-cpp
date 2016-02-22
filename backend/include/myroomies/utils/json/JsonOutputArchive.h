#pragma once

#include <string>
#include <array>
#include <ostream>
#include <cstddef>
#include <stack>
#include <memory>

#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/version.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/allocators.h>
#include <rapidjson/writer.h>
#include <rapidjson/ostreamwrapper.h>

namespace myroomies {
namespace utils {
namespace json {

class JsonOutputArchive
{
public:
    JsonOutputArchive(std::ostream& oStream)
      : os_(oStream)
    {}

    template<typename T>
    JsonOutputArchive& operator&(const T& t)
    {
        return *this << t;
    }

    template<typename T>
    JsonOutputArchive& operator<<(const T& t)
    {
        saveValue(t);

        if (stack_.size() == 1)
        {
            rapidjson::OStreamWrapper osw(os_);
            rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
            stack_.top()->Accept(writer);
        }
        else
        {
            rapidjson::Value value;
            value = *(stack_.top());
            stack_.pop();
            if (stack_.top()->IsArray())
            {
                stack_.top()->PushBack(value, allocator_);
            }
        }

        return *this;
    }

    template<typename T>
    JsonOutputArchive& operator<<(const boost::serialization::nvp<T>& t)
    {
        rapidjson::Value key(t.name(), allocator_);
        saveValue(t.const_value());
        rapidjson::Value value;
        value = *(stack_.top());
        stack_.pop();
        stack_.top()->AddMember(key, value, allocator_);
        return *this;
    }

private:
    std::ostream& os_;
    std::stack<std::unique_ptr<rapidjson::Value>> stack_;
    rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>  allocator_;

	template<typename T>
    void saveValue(const T &t)
	{
        typedef
        // primitive value
        typename boost::mpl::eval_if<
            boost::is_fundamental<T>,
            boost::mpl::identity<SavePrimitive<JsonOutputArchive>>,
        // std::string
        typename boost::mpl::eval_if<
            boost::is_same<std::string, T>,
            boost::mpl::identity<SaveString<JsonOutputArchive>>,
        // boost::date_time
        typename boost::mpl::eval_if<
            boost::is_same<boost::gregorian::date, T>,
            boost::mpl::identity<SaveDate<JsonOutputArchive>>,
        // object
        boost::mpl::identity<SaveObject<JsonOutputArchive>>
        >>>::type typex;
        typex::Invoke(*this, t);
    }

	template<typename T,
             typename Alloc,
             template <typename T, typename Alloc> class Container>
    void saveValue(const Container<T, Alloc>& t)
	{
        SaveCollection<JsonOutputArchive>::Invoke(*this, t);
    }

    template<typename T, size_t N>
    void saveValue(const T(&t)[N])
    {
        SaveCollection<JsonOutputArchive>::Invoke(*this, t);
    }

    template<typename T, size_t N>
    void saveValue(const std::array<T, N>& t)
    {
        SaveCollection<JsonOutputArchive>::Invoke(*this, t);
    }

    template<typename Archive>
    struct SaveObject
    {
        template<typename T>
        static void Invoke(Archive& ar, const T& t)
        {
            if (ar.stack_.empty())
            {
                ar.stack_.push(std::make_unique<rapidjson::Document>(rapidjson::kObjectType));
            }
            else
            {
                ar.stack_.push(std::make_unique<rapidjson::Value>(rapidjson::kObjectType));
            }
            boost::serialization::serialize_adl(
                ar,
                const_cast<T &>(t),
                ::boost::serialization::version<T>::value);
        }
    };

    template<typename Archive>
    struct SaveCollection
    {
        template<typename T>
        static void Invoke(Archive& ar, const T& t)
        {
            if (ar.stack_.empty())
            {
                ar.stack_.push(std::make_unique<rapidjson::Document>(rapidjson::kArrayType));
            }
            else
            {
                ar.stack_.push(std::make_unique<rapidjson::Value>(rapidjson::kArrayType));
            }
            for (const auto& element : t)
            {
                ar & element;
            }
        }
    };

    template <typename Archive>
    struct SavePrimitive
    {
        template<typename T>
        static void Invoke(Archive& ar, const T& t)
        {
            ar.stack_.push(std::make_unique<rapidjson::Value>(t));
        }
    };

    template <typename Archive>
    struct SaveString
    {
        template<typename T>
        static void Invoke(Archive& ar, const T& t)
        {
            ar.stack_.push(std::make_unique<rapidjson::Value>(t, ar.allocator_));
        }
    };

    template <typename Archive>
    struct SaveDate
    {
        template<typename T>
        static void Invoke(Archive& ar, const T& t)
        {
            ar.stack_.push(std::make_unique<rapidjson::Value>(boost::gregorian::to_iso_string(t), ar.allocator_));
        }
    };
};

} /* namespace json */
} /* namespace utils */
} /* namespace myroomies */
