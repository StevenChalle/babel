#include "stdafx.h"
#include "Server.h"

Server::Server(boost::asio::io_service& io_service) : _acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 13))
{
	start_accept();
}

Server::~Server()
{
}

void Server::start_accept()
{
	Connection::pointer new_connection = Connection::create(_acceptor.get_io_service());

	_acceptor.async_accept(new_connection->socket(), boost::bind(&Server::handle_accept, this, new_connection, boost::asio::placeholders::error));
}

void Server::handle_accept(Connection::pointer new_connection, const boost::system::error_code& error)
{
	if (!error)
	{
		new_connection->start();
	}

	start_accept();
}