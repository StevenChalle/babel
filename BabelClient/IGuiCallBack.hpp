#ifndef IGUICALLBACK_HPP
#define IGUICALLBACK_HPP

#include <string>
#include <cstdint>

class	IGuiCallBack
{
    public:
	virtual ~IGuiCallBack() {}
	virtual	bool	callContactCallback(const std::string &name) = 0;
	virtual	bool	addContactCallback(const std::string &name) = 0;
	virtual	bool	delContactCallback(const std::string &name) = 0;
	virtual bool	connectCallback(const std::string &ip, uint16_t port, const std::string &name, const std::string &pass) = 0;
	virtual bool	registerCallback(const std::string &ip, uint16_t port, const std::string &name, const std::string &pass) = 0;
	virtual void	closeCallback() = 0;
	virtual int	openDirectCall() = 0;
	virtual void	stopDirectCall() = 0;
	virtual void	startDirectCall(const std::string &ip, int port) = 0;
};

#endif // IGUICALLBACK_HPP
