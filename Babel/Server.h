#ifndef __SERVER_HH__
# define __SERVER_HH__

# include <boost/asio.hpp>
# include <boost/bind.hpp>
# include "Connection.h"

class Server
{
	boost::asio::ip::tcp::acceptor _acceptor;
public:
	Server(boost::asio::io_service & io_service);
	~Server();
	void start_accept();
	void handle_accept(Connection::pointer new_connection, const boost::system::error_code & error);
};

#endif