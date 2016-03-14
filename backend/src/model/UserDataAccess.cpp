#include <memory>
#include <string>
#include <vector>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/format.hpp>

#include <soci/soci.h>

#include <myroomies/model/Common.h>
#include <myroomies/model/User.h>
#include <myroomies/utils/db/Def.h>

#include <myroomies/model/UserDataAccess.h>

using soci::session;
using soci::statement;
using soci::use;
using soci::into;

using myroomies::model::User;

namespace {

std::string kUserInsert =
    boost::str(boost::format(
                "INSERT INTO %1%(%2%,%3%,%4%,%5%,%6%,%7%,%8%) "
                "VALUES(:%2%,:%3%,:%4%,:%5%,:%6%,:%7%,:%8%)")
               % myroomies::model::kTableUser
               % User::kColLogin
               % User::kColPasswordHash
               % User::kColFirstname
               % User::kColLastname
               % User::kColDateOfBirth
               % User::kColEmail
               % User::kColHouseshareId);

std::string kUserRetrieveByHouseshare =
    boost::str(boost::format(
                "SELECT * FROM %1% WHERE %2%=:%2%")
               % myroomies::model::kTableUser
               % User::kColHouseshareId);

std::string kUserRetrieveByLogin =
    boost::str(boost::format(
                "SELECT * FROM %1% WHERE %2%=:%2%")
               % myroomies::model::kTableUser
               % User::kColLogin);

} /* namespace  */

namespace myroomies {
namespace model {

UserDataAccess::UserDataAccess(const std::string& iDatabase)
  : DataAccess(iDatabase)
{}

User UserDataAccess::createUser(const User& iNewUser)
{
    session sql("sqlite3", getDatabase().c_str());
    sql << kUserInsert, use(iNewUser);
    User user = iNewUser;
    long id;
    sql.get_last_insert_id(myroomies::model::kTableUser, id);
    user.id = static_cast<int>(id);
    return user;
}

std::vector<User> UserDataAccess::getUsersFromHouseshare(
    myroomies::utils::db::Key_t iHouseshareId)
{
    session sql("sqlite3", getDatabase().c_str());
    std::vector<User> result;
    User user;
    statement st = (sql.prepare << kUserRetrieveByHouseshare,
                        use(iHouseshareId, User::kColHouseshareId),
                        into(user));
    st.execute();
    while (st.fetch())
    {
        result.push_back(user);
    }
    return result;
}

std::unique_ptr<User> UserDataAccess::getUserFromLogin(const std::string& iLogin)
{
    session sql("sqlite3", getDatabase().c_str());
    User user;
    sql << kUserRetrieveByLogin, into(user), use(iLogin);
    auto result = std::make_unique<User>(user);
    return std::move(result);
}

} /* namespace model */
} /* namespace myroomies */
