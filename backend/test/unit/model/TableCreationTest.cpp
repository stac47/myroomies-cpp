#include <string>
#include <vector>
#include <sstream>

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/format.hpp>

#include <soci/soci.h>

#include <myroomies/utils/db/Def.h>
#include <myroomies/model/Common.h>
#include <myroomies/model/Houseshare.h>
#include <myroomies/model/User.h>
#include <myroomies/model/Expense.h>

using myroomies::model::kTableHouseshare;
using myroomies::model::kTableUser;
using myroomies::model::kTableExpense;
using myroomies::model::kColRowId;
using myroomies::model::Houseshare;
using myroomies::model::User;
using myroomies::model::Expense;
using myroomies::utils::db::Key_t;

using soci::row;
using soci::use;
using soci::into;
using soci::rowset;
using soci::session;

namespace {

class BuildCompositeStringHelper
{
public:
    std::string operator()()
    {
        return "";
    }

    template<typename T, typename ... Args>
    std::string operator()(T&& s, Args&&... args)
    {
        os_ << std::forward<T>(s);
        (*this)(std::forward<Args>(args)...);
        return os_.str();
    }

private:
    std::ostringstream os_;
};

template<typename T, typename ... Args>
std::string BuildCompositeString(T&& s, Args&&... args)
{
    return BuildCompositeStringHelper()(std::forward<T>(s), std::forward<Args>(args)...);
}

std::vector<Houseshare> BuildHouseshares(unsigned int iNumber)
{
    if (iNumber < 1)
    {
        iNumber = 1;
    }
    std::vector<Houseshare> ret;
    for (unsigned int i=0; i<iNumber; ++i)
    {
        Houseshare h;
        h.name = BuildCompositeString("Houseshare name", i);
        h.language = i % 2 == 0 ? "FR" : "EN";
        ret.push_back(h);
    }
    return ret;
}

std::vector<User> BuildUsers(unsigned int iNumber, Key_t iHouseshareId)
{
    if (iNumber < 1)
    {
        iNumber = 1;
    }
    std::vector<User> ret;
    auto compositeString =
        [iHouseshareId] (const std::string& s, unsigned int i)
        {return BuildCompositeString(s, iHouseshareId, i);};
    for (unsigned int i=0; i<iNumber; ++i)
    {
        User u;
        u.login = compositeString("login", i);
        u.passwordHash = compositeString("pass", i);
        u.firstname = compositeString("firstname", i);
        u.lastname = compositeString("lastname", i);
        u.dateOfBirth = boost::gregorian::date(2002 + i, 1, 12);
        u.email = compositeString("email", i);
        u.houseshareId = iHouseshareId;
        ret.push_back(u);
    }
    return ret;
}


} /* namespace  */

BOOST_AUTO_TEST_SUITE(ModelTest)

BOOST_AUTO_TEST_CASE(TableCreation)
{
    boost::filesystem::path dbFile = "myroomies-test.db3";
    boost::filesystem::remove(dbFile);
    myroomies::model::CreateTables(dbFile.c_str(), true);

    session sql("sqlite3", dbFile.c_str());

    auto houseshares = BuildHouseshares(1);

    std::string insertHouseshare =
        boost::str(boost::format("INSERT INTO %1%(%2%, %3%) VALUES(:%2%,:%3%)")
                   % kTableHouseshare
                   % Houseshare::kColName
                   % Houseshare::kColLanguage);
    sql << insertHouseshare, use(houseshares[0]);
    long id;
    if (!sql.get_last_insert_id(kTableHouseshare, id))
    {}
    Houseshare houseshare;
    sql << "SELECT rowid, name, language FROM " << kTableHouseshare << " WHERE rowid=" << id,
        into(houseshare.id),
        into(houseshare.name),
        into(houseshare.language);
        /* into(houseshare); */

    BOOST_CHECK(!houseshare.name.empty());
    BOOST_CHECK_EQUAL(1u, houseshare.id);
    BOOST_CHECK_EQUAL(houseshares[0].name, houseshare.name);
    BOOST_CHECK_EQUAL(houseshares[0].language, houseshare.language);

    auto users = BuildUsers(2u, houseshare.id);
    for (User u : users)
    {
        sql << "INSERT INTO " << kTableUser << " VALUES ("
            << ":login, :pass, :fn, :ln, :dob, :email, :hid)",
            use(u.login, "login"),
            use(u.passwordHash, "pass"),
            use(u.firstname, "fn"),
            use(u.lastname, "ln"),
            use(boost::gregorian::to_simple_string(u.dateOfBirth), "dob"),
            use(u.email, "email"),
            use(u.houseshareId, "hid");
    }
    BOOST_TEST_MESSAGE(kTableUser << " is populated with "
                                  << users.size() << " users");
    rowset<row> rs = (sql.prepare
        << "SELECT " << User::kColLogin << ","
                     << User::kColDateOfBirth << " "
        << "FROM " << kTableUser << " "
        << "WHERE " << User::kColHouseshareId << "=" << houseshare.id);
    int userCounter = 0;
    for (rowset<row>::const_iterator it = rs.begin(); it != rs.end(); ++it)
    {
        BOOST_CHECK_EQUAL(users[userCounter].login, it->get<std::string>(0));
        boost::gregorian::date dob = boost::gregorian::from_string(it->get<std::string>(1));
        BOOST_CHECK_EQUAL(users[userCounter].dateOfBirth, dob);
        userCounter++;
    }
}

BOOST_AUTO_TEST_SUITE_END()

