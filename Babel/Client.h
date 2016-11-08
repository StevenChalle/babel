
#ifndef CLIENT_H_
# define CLIENT_H_

# include <boost/asio.hpp>
# include <iostream>
# include <vector>
# include <string>

class								Client
{
	std::string						_name;
	std::string						_dbPath;
	std::string						_ip;
	boost::asio::ip::tcp::socket	*_sock;
	unsigned int					_listenningPort;
	std::vector<Client*>			_contacts;

public:
	enum CRUD
	{
		IP,
		SOCK,
		NAME,
		PORT
	};

	Client(const std::string &, const std::string &);
	~Client();

	bool							isConnected();
	void							modify(CRUD, const std::string &, boost::asio::ip::tcp::socket *);
	bool							addContact(Client *);
	bool							deleteContact(Client *);

	std::string						getName() const;
	std::string						getFilePath() const;
	boost::asio::ip::tcp::socket	*getSock() const;
	std::string						getIp() const;
	std::vector<Client*>			getContacts() const;
};

#endif