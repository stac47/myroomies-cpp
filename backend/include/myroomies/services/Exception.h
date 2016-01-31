#pragma once

namespace myroomies {
namespace services {

class ServiceException
{};

class ResourceNotFoundException : public ServiceException
{};

class ForbiddenResourceException : public ServiceException
{};

} /* namespace resources */
} /* namespace myroomies */
