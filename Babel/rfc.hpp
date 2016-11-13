#ifndef RFC_HPP
#define RFC_HPP

#include <cstdint>

namespace RFC 
{

	enum ActionsSend
	{
    PING = 1,
    RETURN,
    HANDSHAKE,
    REGISTER,
    LOGIN,
    STATUS,
    CONTACT_REQUEST,
    ACCEPT_CONTACT,
    DELETE_CONTACT,
    CALL,
    ACCEPT_CALL,
    HANGUP,
    EXIT,
    MESSAGE,
    LIST
	};

	enum ActionsReceived
	{
    SUCCESS = 0,
    UNKNOWN_ERROR,
    UNKNOWN_COMMAND,
    WRONG_PACKET_FORMAT,
    NOT_HANDSHAKED,
    YOU_NEED_TO_LOG_IN,
    INVALID_ID,
    INVALID_PASSWORD,
    ID_ALREADY_EXISTS,
    ID_DOESNT_EXISTS,
    ID_ALREADY_LOGGED_IN,
    YOU_ALREADY_LOGGED_IN,
    ALREADY_IN_CONTACT_LIST,
    NOT_IN_CONTACT_LIST,
    CONTACT_BUSY,
    CONTACT_NOT_CONNECTED,
    CANT_CONF_CALL,
    CANT_ADD_YOURSELF,
    CANT_CALL_YOURSELF,
    CANT_MESSAGE_YOURSELF
	};

#pragma pack(push, 1)
struct Data
{
    char    code;
    char    *data;
};

struct Return
{
    char    lastCmdCode;
    char    errCode;
};

struct Handshake
{
    char    magicNbr;
};

struct Register
{
    char    userId[64];
    char    password[64];
};

struct Login
{
    char    userId[64];
    char    password[64];
};

struct AddContact
{
    char    userId[64];
};

struct AcceptContact
{
    char    userId[64];
};

struct DelContact
{
    char    userId[64];
};

struct CallClient
{
    char	userId[64];
    uint16_t	port;
};

struct AcceptCallClient
{
    char	userId[64];
    uint16_t	port;
};

struct StartCall
{
    char	userId[64];
    uint32_t	ip;
    uint16_t	port;
};

struct AudioPacket
{
    int32_t timestamp;
    char    soundData[0];
};
#pragma pack(pop)

};

#endif // RFC_HPP
