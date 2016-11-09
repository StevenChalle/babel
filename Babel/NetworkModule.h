
#ifndef NETWORKMODULE_H_
# define NETWORKMODULE_H_

# include <ctime>
# include <iostream>
# include <string>
# include <boost/asio.hpp>
# include "Database.h"

class							NetworkModule
{
	Database					_db;
	boost::asio::streambuf		_sbuf;
	boost::system::error_code	_ignoredErr;

public:
	NetworkModule(Database &);
	~NetworkModule();

	bool						start();
	std::string					recvMsg(boost::asio::ip::tcp::socket &);
};

#endif