#include <iostream>

#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <httpserver.hpp>

#include <myroomies/resources/StaticResource.h>

namespace po = boost::program_options;

using httpserver::webserver;
using myroomies::resources::StaticResource;

int main(int argc, const char* argv[])
{
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

    BOOST_LOG_TRIVIAL(info) << "MyRoomies server is starting...";
    boost::filesystem::path programPath = argv[0];
    BOOST_LOG_TRIVIAL(info) << "Binary: " << boost::filesystem::absolute(programPath).native();
    BOOST_LOG_TRIVIAL(info) << "Working directory: " << boost::filesystem::current_path().native();

    webserver ws = httpserver::create_webserver(8080)
                   .start_method(httpserver::http::http_utils::INTERNAL_SELECT)
                   .max_threads(5);

    BOOST_LOG_TRIVIAL(info) << "Registering resources...";
    if (vm.count("development"))
    {
        BOOST_LOG_TRIVIAL(warning) << "Development mode activated. DO NOT USE IT IN PRODUCTION.";
        static StaticResource staticResource(programPath.parent_path());
        ws.register_resource("/static", &staticResource, true);
    }
    BOOST_LOG_TRIVIAL(info) << "Resources registered";
    BOOST_LOG_TRIVIAL(info) << "Server up and running";

    // Blocking call
    ws.start(true);
    return 0;
}
