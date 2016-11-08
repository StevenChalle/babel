#include "stdafx.h"
#include "Client.h"


Client::Client(const std::string &name, const std::string &dbPath) : _name(name), _dbPath(dbPath)
{
}

Client::~Client()
{
}

bool Client::isConnected()
{
	if (_sock != NULL)
		return true;
	return false;
}

void Client::modify(CRUD instruction, const std::string &value, boost::asio::ip::tcp::socket *socket)
{
	switch (instruction)
	{
	case IP:
		_ip = value;
		break;
	case SOCK:
		_sock = socket;
		break;
	case NAME:
		_name = value;
		break;
	case PORT:
		_listenningPort = static_cast<unsigned int>(std::stoi(value));
		break;
	}
}

bool Client::addContact(Client *client)
{
	_contacts.push_back(client);
	
	return true;
}

bool Client::deleteContact(Client *client)
{
	for (unsigned int k = 0; k < _contacts.size(); k++)
	{
		if (_contacts[k]->_name == client->_name)
			_contacts.erase(_contacts.begin() + k);
	}
	return true;
}

std::string Client::getName() const
{
	return _name;
}

std::string Client::getFilePath() const
{
	return _dbPath + "\\" + _name + ".txt";
}

boost::asio::ip::tcp::socket *Client::getSock() const
{
	return _sock;
}

std::string Client::getIp() const
{
	return _ip;
}

std::vector<Client*> Client::getContacts() const
{
	return _contacts;
}

