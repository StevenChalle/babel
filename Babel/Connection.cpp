#include "stdafx.h"
#include "Connection.h"
#include <boost\bind.hpp>
# include "rfc.hpp"

Connection::Connection(boost::asio::io_service &io_service) : _socket(io_service)
{
	_message = "Hello";
}

Connection::~Connection()
{
}

void Connection::handle_write()
{
	std::cout << "Haha, message sent, again !" << std::endl;
}

void Connection::analyzeHeader(char instr[])
{

	instr[1] = '\0';
	std::cout << "received some shit, try analyse header:" << std::endl;
	RFC::Data header;

	memcpy(&header, instr, 1);
	std::cout << "headercode=" << (int)header.code << std::endl;
	if (std::strlen(instr) > 0)
	{
		std::cout << "la" << std::endl;
		switch (header.code)
		{
		case RFC::ActionsSend::HANDSHAKE:
			std::cout << "recognized handshake" << std::endl;
			char rbuffer[sizeof(RFC::Handshake)];
			boost::asio::async_read(_socket, boost::asio::buffer(rbuffer, sizeof(RFC::Handshake)), boost::bind(&Connection::analyzePacket, shared_from_this(), RFC::ActionsSend::HANDSHAKE, rbuffer)); break;
		//default :
		//	char buffer[1];
		//	memset(buffer, 0, sizeof(rbuffer));
		//	boost::asio::async_read(_socket, boost::asio::buffer(buffer, sizeof(char)), boost::bind(&Connection::analyzeHeader, shared_from_this(), buffer));
		//	break;
		}
	}
}

void Connection::analyzePacket(RFC::ActionsSend action, char packet[])
{
	std::cout << "received packet, analyzing it" << std::endl;
	switch (action)
	{
	case RFC::ActionsSend::HANDSHAKE:
		std::cout << "trying handshake transform" << std::endl;
		void			*generic = new char[sizeof(RFC::Handshake)]; memcpy(generic, packet, sizeof(RFC::Handshake)); RFC::Handshake	*data = static_cast<RFC::Handshake*>(generic);
		std::cout << "reinterpreted hdshake struct" << std::endl;
		//handleInstruction(action, data);
		break;
	}
}

void Connection::start()
{
	char rbuffer[1];

	memset(rbuffer, 0, sizeof(rbuffer));
	boost::asio::async_read(_socket, boost::asio::buffer(rbuffer, 1), boost::bind(&Connection::analyzeHeader, shared_from_this(), rbuffer));
	//async_read() header struct into -> analyzeHeader()
	//{
	//	casts header, discover instruction to come and launch relative analyze;
	//	async_read() data struct   into -> analyzePacket(type struct);	
	//}
/*
	analysePacket()
	{
		casts msg received into struct data;
		call handleInstruction();
	}

	handleInstruction()
	{
		handles instruction;
		analyzeHeader();
	}*/
	//

	// first implement handshake
	//boost::asio::async_write(_socket, boost::asio::buffer(_message), boost::bind(&Connection::handle_write, shared_from_this()));
	// second implement reactive API
	// ici, la taille du buffer pour le read complet doit être fixée par le paquet header de taille fixe
	//boost::asio::async_read(_socket, boost::asio::buffer(_rbuffer, 3), boost::bind(&Connection::handle_read, shared_from_this()));
}

boost::asio::ip::tcp::socket& Connection::socket()
{
	return _socket;
}
