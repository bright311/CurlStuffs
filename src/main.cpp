#include <iostream>
#include <boost/json.hpp>
#include <boost/json/src.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
namespace json = boost::json;
namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;

using namespace std;

void handle_request(http::request<http::string_body> req, http::response<http::string_body>& res)
{
    json::object obj;

    cout << "METHOD: " << req.method() << endl;
    cout << "TARGET: " << req.target() << endl;
    cout << "BODY: " << req.body() << endl;

    if(req.method() == http::verb::get && req.target() == "/status")
    {
        obj["status"] = "server running...";
    }
    else if(req.method() == http::verb::post && req.target() == "greet")
    {
        try
        {
            json::value parsed_value = json::parse(req.body());
            string buffer = parsed_value.as_object()["name"].as_string().c_str();
            obj["message"] = "Hello, " + buffer + "!\n";
        }catch(...){
            obj["error"] = "Invalid json format\n";
        }
    }
    else obj["errror"] = "unknown command";

    res.result(http::status::ok);
    res.set(http::field::content_type, "application/json");
    res.body() = json::serialize(obj);
    res.prepare_payload();
}

void run_server(boost::asio::io_context& io, unsigned int port)
{
    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), port));

    while(true)
    {
        tcp::socket socket(io);
        acceptor.accept(socket);
        cout << "Client connected: " << socket.remote_endpoint() << endl;
        boost::beast::flat_buffer buffer;
        http::request<http::string_body> req;
        http::read(socket, buffer, req);

        http::response<http::string_body> res;
        handle_request(req, res);
        http::write(socket, res);
    }
}

int main()
{
    boost::asio::io_context io_context;
    try
    {
        run_server(io_context, 5000);
    }catch(exception& e){
        cout << "Error: " << e.what() << "\n";
    }
}