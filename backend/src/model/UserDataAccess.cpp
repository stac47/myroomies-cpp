#include <memory>
#include <string>
#include <vector>

#include <boost/date_time/gregorian/gregorian.hpp>

#include <soci/soci.h>

#include <myroomies/model/Common.h>
#include <myroomies/model/User.h>
#include <myroomies/utils/db/Def.h>
#include <myroomies/utils/db/SqlTools.h>

#include <myroomies/model/UserDataAccess.h>

using soci::session;
using soci::statement;
using soci::use;
using soci::into;

using myroomies::model::User;

namespace {

namespace db = myroomies::utils::db;

const std::string kUserInsert =
    db::GenerateInsertTemplate(myroomies::model::kTableUser,
                               User::kColLogin,
                               User::kColPasswordHash,
                               User::kColFirstname,
                               User::kColLastname,
                               User::kColDateOfBirth,
                               User::kColEmail,
                               User::kColHouseshareId);

const std::string kUserRetrieveByHouseshare =
    db::GenerateSimpleSelectTemplate(myroomies::model::kTableUser,
                                      User::kColHouseshareId);

const std::string kUserRetrieveByLogin =
    db::GenerateSimpleSelectTemplate(myroomies::model::kTableUser,
                                      User::kColLogin);

} /* namespace  */

namespace myroomies {
namespace model {

UserDataAccess::UserDataAccess(const std::string& iDatabase)
  : DataAccess(iDatabase)
{}

User UserDataAccess::createUser(const User& iNewUser)
{
    session sql("sqlite3", getDatabase().c_str());
    //sql.once << "PRAGMA foreign_keys = ON";
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