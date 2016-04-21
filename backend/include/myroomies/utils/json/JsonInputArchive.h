#pragma once

#include <string>
#include <array>
#include <cstddef>
#include <deque>
#include <memory>
#include <sstream>

#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/version.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/join.hpp>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/document.h>
#include <rapidjson/pointer.h>

namespace myroomies {
namespace utils {
namespace json {

class JsonInputArchive
{
    std::deque<std::string> stack_;
    rapidjson::Document doc_;

public:
    explicit JsonInputArchive(const std::string& iJsonStr)
    {
        doc_.Parse(iJsonStr);
    }

    template<typename T>
    JsonInputArchive& operator&(T& t)
    {
        return *this >> t;
    }

    template<typename T>
    JsonInputArchive& operator>>(T& t)
    {
        loadValue(t);
        return *this;
    }

    template<typename T>
    JsonInputArchive& operator>>(const boost::serialization::nvp<T>& t)
    {
        stack_.push_back(t.name());
        loadValue(t.value());
        stack_.pop_back();
        return *this;
    }

private:
	template<typename T>
    void loadValue(T& t)
	{
        typedef
        // primitive value
        typename boost::mpl::eval_if<
            boost::is_fundamental<T>,
            boost::mpl::identity<LoadPrimitive<JsonInputArchive>>,
        // std::string
        typename boost::mpl::eval_if<
            boost::is_same<std::string, T>,
            boost::mpl::identity<LoadString<JsonInputArchive>>,
        // boost::date_time
        typename boost::mpl::eval_if<
            boost::is_same<boost::gregorian::date, T>,
            boost::mpl::identity<LoadDate<JsonInputArchive>>,
        // object
        boost::mpl::identity<LoadObject<JsonInputArchive>>
        >>>::type typex;
        typex::Invoke(*this, t);
    }

	template<typename T,
             typename Alloc,
             template <typename, typename> class Container>
    void loadValue(Container<T, Alloc>& t)
    {
        if (rapidjson::Value* value = rapidjson::Pointer(getPath()).Get(doc_))
        {
            int counter = 0;
            for (rapidjson::Value::ConstValueIterator itr = value->Begin();
                    itr != value->End(); ++itr)
            {
                stack_.push_back(boost::lexical_cast<std::string>(counter));
                T element;
                *this >> element;
                t.push_back(element);
                counter++;
                stack_.pop_back();
            }
        }
    }

    template<typename T, size_t N>
    void loadValue(T(&t)[N])
    {
        if (rapidjson::Value* value = rapidjson::Pointer(getPath()).Get(doc_))
        {
            int counter = 0;
            for (rapidjson::Value::ConstValueIterator itr = value->Begin();
                    itr != value->End(); ++itr)
            {
                stack_.push_back(boost::lexical_cast<std::string>(counter));
                T element;
                *this >> element;
                t[counter] = element;
                counter++;
                stack_.pop_back();
            }
        }
    }

    template<typename T, size_t N>
    void loadValue(std::array<T, N>& t)
    {
        if (rapidjson::Value* value = rapidjson::Pointer(getPath()).Get(doc_))
        {
            int counter = 0;
            for (rapidjson::Value::ConstValueIterator itr = value->Begin();
                    itr != value->End(); ++itr)
            {
                stack_.push_back(boost::lexical_cast<std::string>(counter));
                T element;
                *this >> element;
                t[counter] = element;
                counter++;
                stack_.pop_back();
            }
        }
    }

    template<typename Archive>
    struct LoadObject
    {
        template<typename T>
        static void Invoke(Archive& ar, T& t)
        {
            boost::serialization::serialize_adl(
                ar,
                t,
                ::boost::serialization::version<T>::value);
        }
    };

    template <typename Archive>
    struct LoadPrimitive
    {
        template<typename T>
        static void Invoke(Archive& ar, T& t)
        {
            if (rapidjson::Value* value = rapidjson::Pointer(ar.getPath()).Get(ar.doc_))
            {
                t = value->Get<T>();
            }
        }
    };

    template <typename Archive>
    struct LoadString
    {
        template<typename T>
        static void Invoke(Archive& ar, T& t)
        {
            if (rapidjson::Value* value = rapidjson::Pointer(ar.getPath()).Get(ar.doc_))
            {
                t = value->GetString();
            }
        }
    };

    template <typename Archive>
    struct LoadDate
    {
        template<typename T>
        static void Invoke(Archive& ar, T& t)
        {
            if (rapidjson::Value* value = rapidjson::Pointer(ar.getPath()).Get(ar.doc_))
            {
                t = boost::gregorian::from_undelimited_string(value->GetString());
            }
        }
    };

    std::string getPath() const
    {
        std::ostringstream os;
        if (!stack_.empty())
        {
            os << "/" << boost::algorithm::join(stack_, "/");
        }
        else
        {
            os << "";
        }
        return os.str();
    }

};

} /* namespace json */
} /* namespace utils */
} /* namespace myroomies */
