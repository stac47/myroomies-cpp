#include <iostream>
#include <functional>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <httpserver.hpp>

#include <myroomies/utils/LoggingMacros.h>

#include <myroomies/resources/StaticResource.h>
#include <myroomies/resources/MoneyResource.h>
#include <myroomies/resources/BalanceResource.h>

namespace po = boost::program_options;

using std::placeholders::_1;

using httpserver::webserver;
using myroomies::resources::StaticResource;
using myroomies::resources::MoneyResource;
using myroomies::resources::BalanceResource;

namespace {

void LogAccess(const std::string& iLog)
{
    spdlog::get("access")->info() << iLog;
}

void LogError(const std::string& iLog)
{
    spdlog::get("error")->error() << iLog;
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

    /* auto log_access = std::bind(&Log, "ACCESS", _1); */
    webserver ws = httpserver::create_webserver(8080)
                   .start_method(httpserver::http::http_utils::INTERNAL_SELECT)
                   .max_threads(5)
                   .max_connections(5)
                   .log_access(LogAccess)
                   .log_error(LogError);

    MYROOMIES_LOG_INFO("Registering resources...");
    if (vm.count("development"))
    {
        MYROOMIES_LOG_WARNING("Development mode activated. DO NOT USE IT IN PRODUCTION.");
        static StaticResource staticResource(programPath.parent_path());
        ws.register_resource("/static", &staticResource, true);
    }
    static MoneyResource moneyResource;
    static BalanceResource balanceResource;
    ws.register_resource("/money", &moneyResource, true);
    ws.register_resource("/money/balance", &balanceResource, true);
    MYROOMIES_LOG_INFO("Resources registered");
    MYROOMIES_LOG_INFO("Server up and running");

    // Blocking call
    ws.start(true);
    return 0;
}
