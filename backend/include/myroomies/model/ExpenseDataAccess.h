#pragma once

#include <myroomies/model/ExpenseTag.h>
#include <myroomies/model/Expense.h>

namespace myroomies {
namespace model {

class ExpenseDataAccess : public DataAccess
{
public:
    Expense createExpense(const Expense& iNewExpense);
    bool removeExpense(myroomies::utils::db::Key_t iExpenseId);
    Expense updateExpense(const Expense& iUpdatedExpense);
    std::vector<Expense> getAllExpenses();
    std::vector<ExpenseTag> getExpenseTags();

private:
    bool addTagToExpense(
        const std::string& iTag,
        long iExpenseId,
        const std::vector<ExpenseTag>& iAllTags);
};

} /* namespace model */
} /* namespace myroomies */
