
#define _CRT_SECURE_NO_WARNINGS 

#include "NetworkModule.h"

using boost::asio::ip::tcp;

NetworkModule::NetworkModule(Database &db) : _db(db)
{

}

NetworkModule::~NetworkModule()
{

}

bool NetworkModule::start()
{
	try
	{
		boost::asio::io_service io_service;
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));
		
		while (true)
		{
			tcp::socket socket(io_service);
			acceptor.accept(socket);

			std::string name(recvMsg(socket));
			if (!_db.getClient(name))
				std::cout << "client:" << name << " is unknown." << std::endl;
			else
			{
				std::string ip(socket.remote_endpoint().address().to_string());
				_db.connectClient(name, ip, &socket);
				
				std::cout << name << " is connected :" << _db.getClient(name)->isConnected() << std::endl << " with ip : " << ip << std::endl;
				//boost::asio::write(socket, boost::asio::buffer(contacts), _ignoredErr);

				_db.disconnectClient(name);
			}
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return true;
}

std::string NetworkModule::recvMsg(tcp::socket &socket)
{
	std::size_t n = boost::asio::read_until(socket, _sbuf, '\n');

	boost::asio::streambuf::const_buffers_type bufs = _sbuf.data();
	std::string msg(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + n);
	msg = msg.substr(0, msg.size() - 1);
	return msg;
}

//std::string contacts("");
//for (auto contact : _db.getClient(name)->getContacts())
//{
//	if (contact->getName() == _db.getClient(name)->getContacts()[_db.getClient(name)->getContacts().size() - 1]->getName())
//		contacts += contact->getName();
//	else
//		contacts += contact->getName() + ", ";
//}