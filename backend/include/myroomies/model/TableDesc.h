#pragma once

#include <string>

namespace myroomies {
namespace model {

struct HouseshareTable
{
    static constexpr const char* kName = "houseshare";
    static constexpr const char* kColId = "id";
    static constexpr const char* kColName = "name";
    static constexpr const char* kColLanguage = "language";
};

struct UserTable
{
    static constexpr const char* kName = "user";
    static constexpr const char* kColId = "id";
    static constexpr const char* kColLogin = "login";
    static constexpr const char* kColPasswordHash = "password_hash";
    static constexpr const char* kColFirstname = "firstname";
    static constexpr const char* kColLastname = "lastname";
    static constexpr const char* kColDateOfBirth = "date_of_birth";
    static constexpr const char* kColEmail = "email";
    static constexpr const char* kColHouseshareId = "houseshare_id";
};

struct ExpenseTable
{
    static constexpr const char* kName = "expense";
    static constexpr const char* kColId = "id";
    static constexpr const char* kColUserId = "user_id";
    static constexpr const char* kColDate = "date";
    static constexpr const char* kColAmount = "amount";
    static constexpr const char* kColTitle = "title";
    static constexpr const char* kColComment = "comment";
};

struct ExpenseTagTable
{
    static constexpr const char* kName = "expensetag";
    static constexpr const char* kColId = "id";
    static constexpr const char* kColTag = "tag";
};

struct ExpenseTagJoinTable
{
    static constexpr const char* kName = "expense_expensetag";
    static constexpr const char* kColExpenseId = "expense_id";
    static constexpr const char* kColExpenseTagId = "expensetag_id";
};

} /* namespace model */
} /* namespace myroomies */
