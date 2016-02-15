#pragma once

#include <string>
#include <ostream>
#include <cstddef>
#include <stack>
#include <memory>

#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/access.hpp>
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

    // Implement requirements for archive concept
    typedef boost::mpl::bool_<false> is_loading;
    typedef boost::mpl::bool_<true> is_saving;

    // this can be a no-op since we ignore pointer polymorphism
    template<class T>
    void register_type(const T * = NULL)
    {}

    unsigned int get_library_version()
    {
        return 0;
    }

    void save_binary(const void* address, std::size_t count)
    {
        // Not supported
    }

    template<typename T>
    JsonOutputArchive& operator&(const T& t)
    {
        return *this << t;
    }

    template<typename T>
    JsonOutputArchive& operator<<(const T& t)
    {
        stack_.push(std::make_unique<rapidjson::Document>(rapidjson::kObjectType, &allocator_));
        auto& doc = stack_.top();
        boost::serialization::serialize_adl(
            *this,
            const_cast<T &>(t),
            ::boost::serialization::version<T>::value);
        // TODO check is the stack size is 1
        rapidjson::OStreamWrapper osw(os_);
        rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
        doc->Accept(writer);
        return *this;
    }

    template<typename T>
    JsonOutputArchive& operator<<(const boost::serialization::nvp<T>& t)
    {
        saveNVP(t.name(), t.const_value());
        return *this;
    }

private:
    std::ostream& os_;
    std::stack<std::unique_ptr<rapidjson::Value>> stack_;
    rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>  allocator_;

	template<class T>
    void saveNVP(const std::string& k, const T &t)
	{
        typedef
        // primitive value
        typename boost::mpl::eval_if<
        boost::mpl::equal_to<
            boost::serialization::implementation_level<T>,
            boost::mpl::int_<boost::serialization::primitive_type>
        >,
        boost::mpl::identity<SavePrimitive<JsonOutputArchive>>,
        // std::string
        typename boost::mpl::eval_if<
            boost::is_same<std::string, T>,
            boost::mpl::identity<SaveString<JsonOutputArchive>>,
        typename boost::mpl::eval_if<
            boost::is_same<boost::gregorian::date, T>,
            boost::mpl::identity<SaveDate<JsonOutputArchive>>,
        // object
        boost::mpl::identity<SaveObject<JsonOutputArchive>>
        >>>::type typex;
        typex::invoke(*this, k, t);
    }

    template<typename Archive>
    struct SaveObject
    {
        template<typename T>
        static void invoke(Archive& ar, const std::string& k, const T& t)
        {
            ar.stack_.push(std::make_unique<rapidjson::Value>(rapidjson::kObjectType));
            boost::serialization::serialize_adl(
                ar,
                const_cast<T &>(t),
                ::boost::serialization::version<T>::value);
            rapidjson::Value newObject(rapidjson::kObjectType);
            newObject = *(ar.stack_.top());
            ar.stack_.pop();
            rapidjson::Value key(k.c_str(), ar.allocator_);
            ar.stack_.top()->AddMember(key, newObject, ar.allocator_);
        }
    };

    template <typename Archive>
    struct SavePrimitive
    {
        template<typename T>
        static void invoke(Archive& ar, const std::string& k, const T& t)
        {
            rapidjson::Value key(k.c_str(), ar.allocator_);
            rapidjson::Value value(t);
            ar.stack_.top()->AddMember(key, value, ar.allocator_);
        }
    };

    template <typename Archive>
    struct SaveString
    {
        template<typename T>
        static void invoke(Archive& ar, const std::string& k, const T& t)
        {
            rapidjson::Value key(k.c_str(), ar.allocator_);
            rapidjson::Value value(t, ar.allocator_);
            ar.stack_.top()->AddMember(key, value, ar.allocator_);
        }
    };

    template <typename Archive>
    struct SaveDate
    {
        template<typename T>
        static void invoke(Archive& ar, const std::string& k, const T& t)
        {
            rapidjson::Value key(k.c_str(), ar.allocator_);
            rapidjson::Value value(boost::gregorian::to_iso_string(t), ar.allocator_);
            ar.stack_.top()->AddMember(key, value, ar.allocator_);
        }
    };
};

} /* namespace json */
} /* namespace utils */
} /* namespace myroomies */
