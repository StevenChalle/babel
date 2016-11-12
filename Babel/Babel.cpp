
#include <iostream>
#include "Database.h"
#include "NetworkModule.h"

int main()
{
	Database db;
	NetworkModule network(db);

	network.start();
    
	return 0;
}