#include <string>

#include <boost/test/unit_test.hpp>

#include <soci/soci.h>

#include <myroomies/model/Houseshare.h>
#include <myroomies/model/DataAccess.h>
#include <myroomies/model/HouseshareDataAccess.h>
#include <myroomies/utils/db/Def.h>

#include "ModelTools.h"

using myroomies::model::Houseshare;
using myroomies::model::DataAccess;
using myroomies::model::HouseshareDataAccess;
using myroomies::model::ModelFixture;
using myroomies::utils::db::Key_t;

BOOST_AUTO_TEST_SUITE(ModelTest)

BOOST_FIXTURE_TEST_CASE(HouseshareDataAccessTest, ModelFixture)
{
    Houseshare houseshare = myroomies::model::BuildHouseshares(1)[0];
    HouseshareDataAccess houseshareDao;
    Key_t houseshareId = houseshareDao.createHouseshare(houseshare).id;
    BOOST_CHECK_EQUAL(1, houseshareId);
    auto retrieved = houseshareDao.getHouseshareById(houseshareId);
    BOOST_CHECK_EQUAL(houseshare.name, retrieved->name);
    BOOST_CHECK_EQUAL(houseshare.language, retrieved->language);
}

BOOST_AUTO_TEST_SUITE_END()

