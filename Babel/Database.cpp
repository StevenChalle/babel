
# include "Database.h"
# include <string>

Database::Database() : _loaded(false)
{
	_rootPath = "../Database";
	loadDatabase();
	//std::string content;
	//std::cout << "Enter the path of your database folder :" << std::endl;
	//std::getline(std::cin, content);
	//_rootPath = content; //
	//while (!loadDatabase())
	//{
	//	std::cerr << "Database not found." << std::endl;
	//	std::cout << "Enter the path of your database folder :" << std::endl;
	//	std::getline(std::cin, content);
	//	std::cout << "path chosen =" << content << std::endl;
	//	_rootPath = content;
	//}
	//std::cout << "Database loaded." << std::endl;
}

Database::~Database()
{
	for (auto client : _clients)
		delete(client);
	_clients.clear();
}

bool Database::loadDatabase()
{
	if (!loadClients())
		return false;

	if (!retrieveClientsData())
		return false;


	_loaded = true;

	return false;
}

bool Database::loadClients()
{
	boost::filesystem::path root(_rootPath);
	if (!boost::filesystem::is_directory(root))
	{
		std::cout << "Error: can't find database." << std::endl;
		return false;
	}

	boost::filesystem::recursive_directory_iterator end;
	for (boost::filesystem::recursive_directory_iterator i(root); i != end; ++i)
	{
		const boost::filesystem::path cp = (*i);
		std::string name = cp.filename().string().substr(0, cp.filename().string().find('.'));
		_clients.push_back(new Client(name, _rootPath));
	}

	return true;
}

bool Database::retrieveClientsData()
{
	for (auto client : _clients)
	{
		std::string content, tool;
		std::fstream cdata(client->getFilePath(), std::ios::in);
		if (!cdata)
			return false;
		while (std::getline(cdata, tool))
			content += tool;
		cdata.close();

		if (!parseInfo(client, content))
			return false;
	}

	return true;
}

bool Database::parseInfo(Client *client, std::string &data)
{
	std::string tool, tool2;
	bool multiple = false;

	data = data.substr(data.find('|') + 1);
	tool = data.substr(0, data.find('|'));
	tool = tool.substr(tool.find(':') + 2);
	tool2 = tool;
	while (tool.find(',') != tool.npos)
	{
		multiple = true;
		tool2 = tool.substr(0, tool.find(','));
		for (auto cl : _clients)
			if (cl->getName() == tool2)
				client->addContact(cl);
		if (tool.find(',') != tool.npos)
			tool = tool.substr(tool.find(',') + 2);
	}
	if (multiple)
		tool2 = tool;
	for (auto cl : _clients)
		if (cl->getName() == tool2)
			client->addContact(cl);

	/*data = data.substr(data.find('|') + 1);
	tool = data.substr(0, data.find('|'));
	tool = tool.substr(tool.find(':') + 2);
	if (tool.size())
		modifyClient(client, Client::IP, tool);

	data = data.substr(data.find('|') + 1);
	tool = data.substr(0, data.find('|'));
	tool = tool.substr(tool.find(':') + 2);
	if (tool.size())
		modifyClient(client, Client::SOCK, tool);*/

	return true;
}

bool Database::connectClient(const std::string &name, const std::string &ip, boost::asio::ip::tcp::socket *socket)
{
	for (auto client : _clients)
	{
		if (client->getName() == name)
		{
			modifyClient(client, Client::IP, ip, NULL);
			modifyClient(client, Client::SOCK, "", socket);
			return true;
		}
	}
	return false;
}

bool Database::disconnectClient(const std::string &name)
{
	for (auto client : _clients)
	{
		if (name == client->getName())
		{
			modifyClient(client, Client::IP, std::string(""), NULL);
			modifyClient(client, Client::SOCK, std::string(""), NULL);
		}
	}
	return false;
}

Client * Database::getClient(const std::string &name) const
{
	for (auto client : _clients)
		if (client->getName() == name)
			return (client);
	return NULL;
}

bool Database::addContact(Client *a, Client *b)
{
	std::fstream	file(a->getFilePath(), std::ios::out | std::ios::trunc);
	std::string		tool("");

	if (!file)
		return false;
	tool += "name : " + a->getName() + "|\ncontacts : ";
	for (auto cl : a->getContacts())
	{
		if (cl->getName() == a->getContacts()[a->getContacts().size() - 1]->getName())
			tool += cl->getName();
		else
			tool += cl->getName() + ", ";
	}
	tool += ", " + b->getName() + "|";
	file << tool;
	file.close();
	
	a->addContact(b);

	return true;
}

bool Database::delContact(Client *a, Client *b)
{
	std::fstream	file(a->getFilePath(), std::ios::out | std::ios::trunc);
	std::string		tool("");

	if (!file)
		return false;
	tool += "name : " + a->getName() + "|\ncontacts : ";
	for (auto cl : a->getContacts())
	{
		if (cl->getName() == a->getContacts()[a->getContacts().size() - 1]->getName())
			if (cl->getName() != b->getName())
			{
				tool += cl->getName() + "|";
			}
			else
				tool += "|";
		else
			if (cl->getName() != b->getName())
				tool += cl->getName() + ", ";
	}
	file << tool;
	file.close();

	a->deleteContact(b);

	return true;
}

void Database::addClient(Client *client)
{
	_clients.push_back(client);
}

void Database::modifyClient(Client *client, Client::CRUD instruction, const std::string &value, boost::asio::ip::tcp::socket *socket)
{
	client->modify(instruction, value, socket);
}

void Database::displayClients() const
{
	std::cout << _clients.size() << " Clients : " << std::endl;
	for (auto client : _clients)
	{
		std::cout << "- " << client->getName() << " :" << std::endl;
		std::cout << "ip = " << client->getIp() << std::endl;
		if (client->getSock())
			std::cout << "sock = filled" << std::endl;
		else
			std::cout << "sock = empty" << std::endl;
		std::cout << "contacts = ";
		for (auto cl : client->getContacts())
			std::cout << cl->getName() << " ";
		std::cout << std::endl << std::endl;
	}
}
