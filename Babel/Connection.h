#ifndef __CONNECTION_HH__
# define __CONNECTION_HH__

# include <iostream>
# include <boost/asio.hpp>
# include <boost/enable_shared_from_this.hpp>

class Connection : public boost::enable_shared_from_this<Connection>
{
	boost::asio::ip::tcp::socket _socket;
	std::string _message;
	Connection(boost::asio::io_service& io_service);
	char *_rbuffer;
	void handle_write();
	void handle_read();
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