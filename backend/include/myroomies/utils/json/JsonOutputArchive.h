#pragma once

#include <string>
#include <ostream>
#include <cstddef>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/access.hpp>

#include <myroomies/utils/json/JsonMarshaller.h>

namespace myroomies {
namespace utils {
namespace json {

class JsonOutputArchive
{
public:
    JsonOutputArchive(std::ostream& oStream)
      : marshaller_(oStream)
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
        save(t);
        marshaller_.marshall();
        return *this;
    }

    template<typename T>
    JsonOutputArchive& operator<<(const boost::serialization::nvp<T>& t)
    {
        marshaller_.putValue(t.name(), t.const_value());
        return *this;
    }

private:
    myroomies::utils::json::JsonMarshaller marshaller_;

	template<class T>
    void save(const T &t)
	{
        // TODO: Add a test on enum
        typedef typename boost::mpl::eval_if<
				// if its primitive
				boost::mpl::equal_to<
					boost::serialization::implementation_level<T>,
					boost::mpl::int_<boost::serialization::primitive_type>
				>,
				boost::mpl::identity<SavePrimitive<JsonOutputArchive>>,
				// else
				boost::mpl::identity<SaveOnly<JsonOutputArchive>>
			>::type typex;
        typex::invoke(*this, t);
    }

    template<typename Archive>
    struct SaveOnly
    {
        template<typename T>
        static void invoke(Archive& ar, const T& t)
        {
            boost::serialization::serialize_adl(
                ar,
                const_cast<T &>(t),
                ::boost::serialization::version<T>::value);
        }
    };

    template <typename Archive>
    struct SavePrimitive
    {
        template<typename T>
        static void invoke(Archive&, const T&)
        {
            // TODO report an error: Only NVP should be allowed
        }
    };
};

} /* namespace json */
} /* namespace utils */
} /* namespace myroomies */
