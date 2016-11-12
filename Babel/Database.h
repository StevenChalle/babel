
#ifndef DATABASE_H_
# define DATABASE_H_

# include <stdint.h>
# include <boost/asio.hpp>
# include <boost/filesystem.hpp>
# include <iostream>
# include <vector>
# include <fstream>
# include "Client.h"

class						Database
{
	bool					_loaded;
	std::string				_rootPath;
	std::vector<Client*>	_clients;

public:
	Database();
	~Database();

	bool					loadDatabase();
	bool					loadClients();
	bool					retrieveClientsData();
	bool					parseInfo(Client *, std::string &);

	bool					connectClient(const std::string &, const std::string &, boost::asio::ip::tcp::socket *);
	bool					disconnectClient(const std::string &);
	
	Client					*getClient(const std::string &) const;
	bool					addContact(Client *, Client *);
	bool					delContact(Client *, Client *);
	void					addClient(Client *);
	void					modifyClient(Client *, Client::CRUD, const std::string &, boost::asio::ip::tcp::socket *);

	void					displayClients() const;
};

#endif