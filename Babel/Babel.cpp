
#include <iostream>
#include "Database.h"
#include "NetworkModule.h"

int main()
{
	Database *db = new Database();

	NetworkModule network(db);

	//network.start();

	/*db->displayClients();
	std::cout << "_____________________________________________________" << std::endl;

	db->addContact(db->getClient("Jahman"), db->getClient("SantaClaus"));

	db->displayClients();
	std::cout << "_____________________________________________________" << std::endl;
	
	db->delContact(db->getClient("Jahman"), db->getClient("SantaClaus"));

	db->displayClients();*/
    
	return 0;
}