#include "stdafx.h"
#include "Connection.h"
#include <boost\bind.hpp>

Connection::Connection(boost::asio::io_service &io_service) : _socket(io_service)
{
	_rbuffer = new char[256];
	memset(_rbuffer, 0, sizeof(_rbuffer));
	_message = "Hello";
}

Connection::~Connection()
{
}

void Connection::handle_write()
{
	std::cout << "Haha, message sent, again !" << std::endl;
}

void Connection::handle_read()
{
	if (std::strlen(_rbuffer) > 0)
	{
		std::cout << "Oh, motherfucker, this is what i received : " << _rbuffer << std::endl;
		memset(_rbuffer, 0, sizeof(_rbuffer));
		// ici, la taille du buffer pour le read complet doit être fixée par le paquet header de taille fixe
		boost::asio::async_read(_socket, boost::asio::buffer(_rbuffer, 3), boost::bind(&Connection::handle_read, shared_from_this()));
	}
}

void Connection::start()
{
	// first implement handshake
	boost::asio::async_write(_socket, boost::asio::buffer(_message), boost::bind(&Connection::handle_write, shared_from_this()));
	// second implement reactive API
	// ici, la taille du buffer pour le read complet doit être fixée par le paquet header de taille fixe
	boost::asio::async_read(_socket, boost::asio::buffer(_rbuffer, 3), boost::bind(&Connection::handle_read, shared_from_this()));
}

boost::asio::ip::tcp::socket& Connection::socket()
{
	return _socket;
}
