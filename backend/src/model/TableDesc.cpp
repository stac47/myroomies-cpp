#include <myroomies/model/TableDesc.h>

namespace myroomies {
namespace model {

constexpr const char* HouseshareTable::kName;
constexpr const char* HouseshareTable::kColId;
constexpr const char* HouseshareTable::kColName;
constexpr const char* HouseshareTable::kColLanguage;

constexpr const char* UserTable::kName;
constexpr const char* UserTable::kColId;
constexpr const char* UserTable::kColLogin;
constexpr const char* UserTable::kColPasswordHash;
constexpr const char* UserTable::kColFirstname;
constexpr const char* UserTable::kColLastname;
constexpr const char* UserTable::kColDateOfBirth;
constexpr const char* UserTable::kColEmail;
constexpr const char* UserTable::kColHouseshareId;

constexpr const char* ExpenseTable::kName;
constexpr const char* ExpenseTable::kColId;
constexpr const char* ExpenseTable::kColUserId;
constexpr const char* ExpenseTable::kColDate;
constexpr const char* ExpenseTable::kColAmount;
constexpr const char* ExpenseTable::kColTitle;
constexpr const char* ExpenseTable::kColComment;

constexpr const char* ExpenseTagTable::kName;
constexpr const char* ExpenseTagTable::kColId;
constexpr const char* ExpenseTagTable::kColTag;

constexpr const char* ExpenseTagJoinTable::kName;
constexpr const char* ExpenseTagJoinTable::kColExpenseId;
constexpr const char* ExpenseTagJoinTable::kColExpenseTagId;

} /* namespace model */
} /* namespace myroomies */
