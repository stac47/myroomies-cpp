#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include <boost/date_time/gregorian/gregorian.hpp>

#include <soci/soci.h>

#include <myroomies/model/DataAccess.h>
#include <myroomies/model/Expense.h>
#include <myroomies/model/ExpenseTag.h>
#include <myroomies/model/User.h>
#include <myroomies/model/TableDesc.h>
#include <myroomies/utils/db/Def.h>
#include <myroomies/utils/db/SqlTools.h>

#include <myroomies/model/ExpenseDataAccess.h>

using soci::session;
using soci::statement;
using soci::row;
using soci::rowset;
using soci::use;

using myroomies::utils::db::Key_t;
using myroomies::model::Expense;
using myroomies::model::ExpenseTable;
using myroomies::model::ExpenseTagJoinTable;
using myroomies::model::ExpenseTagTable;


namespace {

namespace db = myroomies::utils::db;

const std::string kExpenseInsert =
    db::GenerateInsertTemplate(ExpenseTable::kName,
                               ExpenseTable::kColUserId,
                               ExpenseTable::kColDate,
                               ExpenseTable::kColAmount,
                               ExpenseTable::kColTitle,
                               ExpenseTable::kColComment);

const std::string kExpenseTagInsert =
    db::GenerateInsertTemplate(ExpenseTagTable::kName,
                               ExpenseTagTable::kColTag);

const std::string kExpenseTagJoinInsert =
    db::GenerateInsertTemplate(ExpenseTagJoinTable::kName,
                               ExpenseTagJoinTable::kColExpenseId,
                               ExpenseTagJoinTable::kColExpenseTagId);

} /* namespace  */

namespace myroomies {
namespace model {

std::vector<ExpenseTag> ExpenseDataAccess::getExpenseTags()
{
    std::vector<ExpenseTag> ret;
    std::ostringstream os;
    os << "SELECT " << ExpenseTagTable::kColId << "," << ExpenseTagTable::kColTag
       << " FROM " << ExpenseTagTable::kName;
    rowset<ExpenseTag> rs = (getSession().prepare << os.str());
    std::copy(rs.begin(), rs.end(), std::back_inserter(ret));
    return ret;
}

bool ExpenseDataAccess::addTagToExpense(
    const std::string& iTag,
    long iExpenseId,
    const std::vector<ExpenseTag>& iAllTags)
{
    long id = 0L;
    auto it = std::find_if(iAllTags.begin(), iAllTags.end(),
        [&iTag] (const ExpenseTag& t) {return t.tag == iTag;});
    if (it == iAllTags.end())
    {
        getSession() << kExpenseTagInsert, use(iTag);
        getSession().get_last_insert_id(ExpenseTagJoinTable::kName, id);
    }
    else
    {
        id = it->id;
    }
    getSession() << kExpenseTagJoinInsert,
        use(iExpenseId, ExpenseTagJoinTable::kColExpenseId),
        use(id, ExpenseTagJoinTable::kColExpenseTagId);
    return true;
}

Expense ExpenseDataAccess::createExpense(const Expense& iNewExpense)
{
    Expense createdExpense = iNewExpense;

    // Insert the expense
    getSession() << kExpenseInsert,
        use(iNewExpense.userId, ExpenseTable::kColUserId),
        use(iNewExpense.date, ExpenseTable::kColDate),
        use(iNewExpense.amount, ExpenseTable::kColAmount),
        use(iNewExpense.title, ExpenseTable::kColTitle),
        use(iNewExpense.comment, ExpenseTable::kColComment);

    long id;
    getSession().get_last_insert_id(ExpenseTable::kName, id);
    createdExpense.id = id;

    // Insert the tags
    auto allTags = getExpenseTags();
    /* std::sort(allTags.begin(), allTags.end()); */
    /* std::vector<std::string> tagsToInsert; */
    /* std::set_difference(iNewExpense.tags.begin(), iNewExpense.tags.end(), */
    /*                     allTags.begin(), allTags.end(), */
    /*                     std::inserter(tagsToInsert, tagsToInsert.begin())); */
    std::for_each(iNewExpense.tags.begin(), iNewExpense.tags.end(),
                  [this, &id, &allTags] (auto& t) {this->addTagToExpense(t, id, allTags);});
    return createdExpense;
}

bool ExpenseDataAccess::removeExpense(myroomies::utils::db::Key_t iExpenseId)
{
    std::ostringstream os;
    os << "DELETE FROM " << ExpenseTable::kName
       << " WHERE " << ExpenseTable::kColId << "=" << iExpenseId;
    getSession().once << os.str();
    return true;
}

std::vector<Expense> ExpenseDataAccess::getAllExpenses()
{
    std::vector<Expense> ret;
    std::ostringstream os;
    os << "SELECT " << ExpenseTable::kName << "." << ExpenseTable::kColId << ","
                    << ExpenseTable::kName << "." << ExpenseTable::kColUserId << ","
                    << ExpenseTable::kName << "." << ExpenseTable::kColDate << ","
                    << ExpenseTable::kName << "." << ExpenseTable::kColAmount << ","
                    << ExpenseTable::kName << "." << ExpenseTable::kColTitle << ","
                    << ExpenseTable::kName << "." << ExpenseTable::kColComment << ","
                    << ExpenseTagTable::kName << "." << ExpenseTagTable::kColTag
       << " FROM " << ExpenseTable::kName
       << " LEFT JOIN " << ExpenseTagJoinTable::kName << " ON "
            << ExpenseTagJoinTable::kColExpenseId << "="
            << ExpenseTable::kName << "." << ExpenseTable::kColId
       << " LEFT JOIN " << ExpenseTagTable::kName << " ON "
            << ExpenseTagTable::kName << "." << ExpenseTagTable::kColId << "="
            << ExpenseTagJoinTable::kColExpenseTagId;
    rowset<row> rs = (getSession().prepare << os.str());
    for (auto it = rs.begin(); it != rs.end(); ++it)
    {
        int id = it->get<int>(0);
        auto expenseIt = std::find_if(ret.begin(), ret.end(),
            [id] (const Expense& e) {return e.id == id;});
        if (expenseIt == ret.end())
        {
            Expense e;
            e.id = id;
            e.userId = it->get<int>(1);
            e.date = boost::gregorian::from_string(it->get<std::string>(2));
            e.amount = it->get<double>(3);
            e.title = it->get<std::string>(4);
            e.comment = it->get<std::string>(5);
            if (it->get_indicator(6) != soci::i_null)
            {
                e.tags.push_back(it->get<std::string>(6));
            }
            ret.push_back(e);
        }
        else
        {
            expenseIt->tags.push_back(it->get<std::string>(6));
        }
    }
    return ret;
}

Expense ExpenseDataAccess::updateExpense(const Expense& iUpdatedExpense)
{
    std::ostringstream os;
    os << "UPDATE " << ExpenseTable::kName << " SET "
       << ExpenseTable::kColDate << "='"
            << boost::gregorian::to_iso_extended_string(iUpdatedExpense.date) << "',"
       << ExpenseTable::kColAmount << "='" << iUpdatedExpense.amount << "',"
       << ExpenseTable::kColTitle << "='" << iUpdatedExpense.title << "',"
       << ExpenseTable::kColComment << "='" << iUpdatedExpense.comment << "'"
       << " WHERE " << ExpenseTable::kColId << "=" << iUpdatedExpense.id;
    getSession() << os.str();
    return iUpdatedExpense;
}

} /* namespace model */
} /* namespace myroomies */

