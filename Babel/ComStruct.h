
#ifndef COMSTRUCT_H_
# define COMSTRUCT_H_

# include <stdint.h>

enum MsgType :  unsigned char
{
	AUTH = 0,
	ERROR,
	PING,
	DONE,
	ADD,
	DEL,
	INVIT,
	CALL,
	IP,
	HANDSHAKE
};

/*

Before Auth (HandShake) :
C: 9 -> S
S: 9 -> C
C: 9 -> S

Auth :
C: 0 -> S
S: 1 -> C
Or
S: 3 -> C

AddContact :
C: 4 -> S
S: 1 -> C
Or
S: 3 -> C

RecvInvite :
S: 6 -> C
C: 1 -> S
Or
C: 3 -> S

DelContact :
C: 5 -> S
S: 1 -> C
Or
S: 3 -> C

Ping :
S: 2 -> C
C: 2 -> S

Call :
C: 7 -> S
     <- 1 Or 7 -> C2
	           <- 1 Or
			   <- 8 (create listenning port)
	 <- 8
	----------> connect on listenning port
*/

struct		Message
{
	enum MsgType	type;
	char	data[0];
};

struct auth
{
	char	username[64];
	char	pass[64];
};

struct user
{
	char	username[64];
};

struct handshake
{
	unsigned char	hand;
};

struct error
{
	unsigned char errno;
};

struct ip
{
	char		ip[39];
	int64_t		port;
};

#endif