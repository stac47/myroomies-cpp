#include <string>
#include <algorithm>
#include <vector>

#include <boost/test/unit_test.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include <soci/soci.h>

#include <myroomies/model/User.h>
#include <myroomies/model/Expense.h>
#include <myroomies/model/Houseshare.h>
#include <myroomies/model/DataAccess.h>
#include <myroomies/model/HouseshareDataAccess.h>
#include <myroomies/model/ExpenseDataAccess.h>
#include <myroomies/model/UserDataAccess.h>
#include <myroomies/utils/db/Def.h>

#include "ModelTools.h"

using myroomies::model::User;
using myroomies::model::Expense;
using myroomies::model::Houseshare;
using myroomies::model::DataAccess;
using myroomies::model::HouseshareDataAccess;
using myroomies::model::ExpenseDataAccess;
using myroomies::model::UserDataAccess;
using myroomies::model::ModelFixture;
using myroomies::utils::db::Key_t;

BOOST_AUTO_TEST_SUITE(ModelTest)

BOOST_FIXTURE_TEST_CASE(ExpenseDataAccessTest, ModelFixture)
{
    Houseshare houseshare = myroomies::model::BuildHouseshares(1)[0];
    HouseshareDataAccess houseshareDao;
    Key_t houseshareId = houseshareDao.createHouseshare(houseshare).id;
    BOOST_CHECK(houseshareId > 0);

    auto users = myroomies::model::BuildUsers(2u, houseshareId);

    UserDataAccess dao;

    int count = 0;
    for (auto& u : users)
    {
        ++count;
        auto createdUser = dao.createUser(u);
        BOOST_CHECK_EQUAL(createdUser.id, count);
        u.id = createdUser.id;
    }

    BOOST_CHECK_EQUAL(2, count);

    ExpenseDataAccess expenseDao;
    auto expenses = expenseDao.getExpenses(houseshareId);
    BOOST_CHECK_EQUAL(0u, expenses.size());

    {
        Expense newExpense;
        newExpense.userId = users[0].id;
        newExpense.date = boost::gregorian::date(2002, 1, 12);
        newExpense.amount = 12.5;
        newExpense.title = "title1";
        newExpense.comment = "comment1";
        newExpense.tags.push_back("tag1");
        newExpense.tags.push_back("tag2");
        Expense createdExpense = expenseDao.createExpense(newExpense);
        BOOST_CHECK_EQUAL(createdExpense.id, 1);
    }

    expenses = expenseDao.getExpenses(houseshareId);
    BOOST_CHECK_EQUAL(1u, expenses.size());

    {
        Expense newExpense;
        newExpense.userId = users[0].id;
        newExpense.date = boost::gregorian::date(2003, 1, 12);
        newExpense.amount = 6666;
        newExpense.title = "title2";
        newExpense.comment = "comment2";
        Expense createdExpense = expenseDao.createExpense(newExpense);
        BOOST_CHECK_EQUAL(createdExpense.id, 2);
    }

    expenses = expenseDao.getExpenses(houseshareId);
    BOOST_CHECK_EQUAL(2u, expenses.size());

    {
        Expense newExpense;
        newExpense.userId = users[1].id;
        newExpense.date = boost::gregorian::date(2002, 1, 12);
        newExpense.amount = 16;
        newExpense.title = "title3";
        newExpense.comment = "comment3";
        newExpense.tags.push_back("tag2");
        newExpense.tags.push_back("tag3");
        Expense createdExpense = expenseDao.createExpense(newExpense);
        BOOST_CHECK_EQUAL(createdExpense.id, 3);
    }

    expenses = expenseDao.getExpenses(houseshareId);
    BOOST_CHECK_EQUAL(3u, expenses.size());

    // Delete
    expenseDao.removeExpense(1);
    expenses = expenseDao.getExpenses(0);
    BOOST_CHECK_EQUAL(2u, expenses.size());

    // Update expense 3
    auto it = std::find_if(expenses.begin(), expenses.end(),
        [] (const Expense& e) {return e.id == 3;});
    it->title = "Modified Title 3";
    expenseDao.updateExpense(*it);
}

BOOST_AUTO_TEST_SUITE_END()

