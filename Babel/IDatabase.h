#pragma once
#include <boost/filesystem.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "Client.h"

class				IDatabase
{
public:
	virtual			~IDatabase();

	virtual bool	connectClient(const std::string &, const std::string &, boost::asio::ip::tcp::socket *) = 0;
	virtual bool	disconnectClient(const std::string &) = 0;

	virtual Client	*getClient(const std::string &) const = 0;
	virtual void	addClient(Client *) = 0;
	virtual void	modifyClient(Client *, Client::CRUD, const std::string &, boost::asio::ip::tcp::socket *) = 0;
	virtual bool	addContact(Client *, Client *) = 0;
	virtual bool	delContact(Client *, Client *) = 0;

	virtual void	displayClients() const = 0;
};

