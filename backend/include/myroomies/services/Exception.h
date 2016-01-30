#pragma once

namespace myroomies {
namespace services {

class ServiceEexception
{};

class ResourceNotFoundException : public ServiceEexception
{};

class ForbiddenResourceException : public ServiceEexception
{};

} /* namespace resources */
} /* namespace myroomies */
