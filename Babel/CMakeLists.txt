
cmake_minimum_required(VERSION 3.0)

project(babel)

set(SRCS
    Babel.cpp
	NetworkModule.h
    Database.cpp
	IDatabase.cpp
	Client.cpp
    )
    
set(HEADERS
    Client.h
	ComStruct.h
	Database.h
	IDatabase.h
	NetworkModule.h
    )

add_executable(babel ${SRCS} ${HEADERS})