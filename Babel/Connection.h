#ifndef __CONNECTION_HH__
# define __CONNECTION_HH__

# include <iostream>
# include <boost/asio.hpp>
# include <boost/enable_shared_from_this.hpp>
# include "rfc.hpp"

class Connection : public boost::enable_shared_from_this<Connection>
{
	boost::asio::ip::tcp::socket _socket;
	std::string _message;
	Connection(boost::asio::io_service& io_service);
	void handle_write();
	void analyzeHeader(char []);
	void analyzePacket(RFC::ActionsSend, char []);
//	void handleInstruction(RFC::ActionsSend, s);

public:
	typedef boost::shared_ptr<Connection> pointer;
	~Connection();

	void start();
	boost::asio::ip::tcp::socket& socket();
	static pointer create(boost::asio::io_service& io_service)
	{
		return pointer(new Connection(io_service));
	}
};

#endif