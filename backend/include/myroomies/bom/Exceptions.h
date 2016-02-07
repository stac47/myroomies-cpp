#pragma once

#include <exception>
namespace myroomies {
namespace bom {

class Exception : public std::exception
{};

class UnmarshallException : public Exception
{};

class ValidationException : public Exception
{};

} /* namespace bom */
} /* namespace myroomies */
