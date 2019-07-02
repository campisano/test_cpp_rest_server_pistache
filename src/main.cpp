#include <pistache/router.h>
#include <pistache/endpoint.h>

using namespace Pistache;

class ErrorHandler
{
public:
    Rest::Route::Result notFound(
        const Rest::Request & _request, Http::ResponseWriter _response)
    {
        std::string err
        {
            "Unknown request: \"" + _request.resource() + "\"\n"};
        _response.send(Http::Code::Not_Found, err);

        return Rest::Route::Result::Ok;
    }
};

class HealthHandler
{
public:
    Rest::Route::Result handle(
        const Rest::Request &, Http::ResponseWriter _response)
    {
        _response.send(Http::Code::Ok, "{\"status\":\"UP\"}\n");

        return Rest::Route::Result::Ok;
    }
};

class Server
{
public:
    void notFound(const Rest::Route::Handler & _handler)
    {
        Rest::Routes::NotFound(m_router, _handler);
    }

    void route(
        const std::string & _path, const Rest::Route::Handler & _handler)
    {
        Rest::Routes::Get(m_router, _path, _handler);
    }

    void startAndWait(
        const Ipv4 & _ip, unsigned int _port, unsigned int _threads)
    {
        Http::Endpoint m_endpoint(Address(_ip, _port));
        m_endpoint.init(Http::Endpoint::options().threads(_threads));
        m_endpoint.setHandler(m_router.handler());
        m_endpoint.serve();
        m_endpoint.shutdown();
    }

private:
    Rest::Router m_router;
};

int main(const int /*_argc*/, const char ** /*_argv*/)
{
    Ipv4 ip = Ipv4::any();
    unsigned int port = 8080;
    unsigned int threads = 1;

    using namespace Pistache::Rest;
    ErrorHandler eh;
    HealthHandler hh;

    Server server;
    server.notFound(Routes::bind(&ErrorHandler::notFound, &eh));
    server.route("/health", Routes::bind(&HealthHandler::handle, &hh));
    server.startAndWait(ip, port, threads);

    return EXIT_SUCCESS;
}
