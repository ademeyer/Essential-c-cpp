// Listen on websock
// ping pong on websock
//
#include <boost/beast.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

namespace net = boost::asio;
namespace beast = boost::beast;
using namespace boost::beast;
using namespace boost::beast::websocket;

int main()
{

  // create connection: localhost
  std::string host = "localhost";
  int16 port = 8082;

  return 0;
}