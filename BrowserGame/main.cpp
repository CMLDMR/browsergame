#include "MainApplication.h"
#include <iostream>

#include <mongocxx/instance.hpp>
#include <mongocxx/logger.hpp>
#include <MongoCore/MongoCore.h>

#include <Wt/WServer.h>

#include "Logger.h"


class logger final : public mongocxx::logger {
public:
    explicit logger(std::ostream* stream) : _stream(stream) {}

    void operator()(mongocxx::log_level level,
                    bsoncxx::stdx::string_view domain,
                    bsoncxx::stdx::string_view message) noexcept override {
        if (level >= mongocxx::log_level::k_trace)
            return;
        // *_stream << "Level: " << level;
        *_stream << '[' << mongocxx::to_string(level) << '@' << domain << "] " << message << '\n';
    }

private:
    std::ostream* const _stream;
};

using namespace std;

int main()
{

    setupLogger( "root" , quill::LogLevel::TraceL3 );

    // Load MongoDB cxx Driver
    mongocxx::instance instance{bsoncxx::stdx::make_unique<logger>(&std::cout)};

    int argc1   = 6;
    auto argv1 = std::unique_ptr<char*[]>(new char*[argc1]);

    const std::string port = "--http-port=8080";

    argv1[0] = (char *) "Spartan Monitoring";
    argv1[1] = (char *) "--http-address=0.0.0.0";
    argv1[2] = (char *) port.data();
    argv1[3] = (char *) "--docroot=./docroot";
    argv1[4] = (char *) "--approot=./approot";
    argv1[5] = (char *) "--accesslog=-";



    try {
        Wt::WServer server{argc1, argv1.get(), WTHTTP_CONFIGURATION};


        // WT_API void addEntryPoint(EntryPointType type, ApplicationCreator callback,
        //                           const std::string& path = std::string(),
        //                           const std::string& favicon = std::string());

        server.addEntryPoint(Wt::EntryPointType::Application ,[](const Wt::WEnvironment &env){
            return std::make_unique<MainApplication>( env );
        });

        // server.addEntryPoint(Wt::EntryPointType::WidgetSet ,[](const Wt::WEnvironment &env){
        //     return std::make_unique<DocumentationApp>( env );
        // } , "hello.js");


        // server.addEntryPoint(Wt::EntryPointType::Application ,[](const Wt::WEnvironment &env){
        //     return std::make_unique<MainApplication2>( env );
        // },"newApp");

        // if (server.start()) {
        //     Wt::WServer::waitForShutdown();
        //     server.stop();
        // }


        server.run();
    } catch (const Wt::WServer::Exception &e) {
        return 1;
    } catch (const std::exception &e) {
        return 1;
    }
    return 0;
}
