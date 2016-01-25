#include <csignal>
#include <iostream>
#include <functional>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <httpserver.hpp>

#include <myroomies/utils/LoggingMacros.h>
#include <myroomies/utils/Configuration.h>

#include <myroomies/services/ServiceRegistry.h>

#include <myroomies/resources/StaticResource.h>
#include <myroomies/resources/Resource.h>
#include <myroomies/resources/MoneyHandler.h>

namespace po = boost::program_options;

using httpserver::webserver;

using myroomies::utils::Configuration;

using myroomies::services::ServiceRegistry;

using myroomies::resources::StaticResource;
using myroomies::resources::Resource;
using myroomies::resources::MoneyHandler;

namespace {

void LogAccess(const std::string& iLog)
{
    spdlog::get("access")->info() << iLog;
}

void LogError(const std::string& iLog)
{
    spdlog::get("error")->error() << iLog;
}

webserver* gWebServer;

void signalHandler(int signal)
{
    MYROOMIES_LOG_INFO("Stopping server because signal " << signal);
    gWebServer->stop();
}

} // namespace

int main(int argc, const char* argv[])
{
    myroomies::utils::InitLoggers();
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("development", "start the server in development mode")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return 1;
    }

    MYROOMIES_LOG_INFO("MyRoomies server is starting...");
    boost::filesystem::path programPath = argv[0];
    MYROOMIES_LOG_INFO("Binary: " << boost::filesystem::absolute(programPath).native());
    MYROOMIES_LOG_INFO("Working directory: " << boost::filesystem::current_path().native());


    // TODO fill the configuration object
    Configuration config;

    // Create the ServiceRegistry
    auto serviceRegistry = std::make_shared<ServiceRegistry>(config);

    webserver ws = httpserver::create_webserver(8080)
                   .start_method(httpserver::http::http_utils::INTERNAL_SELECT)
                   .max_threads(5)
                   .max_connections(5)
                   .log_access(LogAccess)
                   .log_error(LogError);

    gWebServer = &ws;

    MYROOMIES_LOG_INFO("Registering resources...");
    if (vm.count("development"))
    {
        MYROOMIES_LOG_WARNING("Development mode activated. DO NOT USE IT IN PRODUCTION.");
        static StaticResource staticResource(programPath.parent_path());
        ws.register_resource("/static", &staticResource, true);
    }

    Resource<MoneyHandler> moneyResource(serviceRegistry, "/money", true);
    ws.register_resource(moneyResource.getUri(), &moneyResource, true);
    MYROOMIES_LOG_INFO("Resources registered");
    MYROOMIES_LOG_INFO("Server up and running");

    std::signal(SIGINT, &signalHandler);
    std::signal(SIGTERM, &signalHandler);
    std::signal(SIGKILL, &signalHandler);

    // Blocking call
    ws.start(true);

    MYROOMIES_LOG_INFO("Exit process");
    return 0;
}
