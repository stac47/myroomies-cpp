#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <myroomies/utils/LoggingMacros.h>

class MyRoomiesGlobalFixture
{
public:
    MyRoomiesGlobalFixture()
    {
        myroomies::utils::Logger::Init(".");
    }

    ~MyRoomiesGlobalFixture()
    {
    }
};

BOOST_GLOBAL_FIXTURE(MyRoomiesGlobalFixture)
