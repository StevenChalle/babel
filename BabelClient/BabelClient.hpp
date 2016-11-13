#ifndef BABEL_HH
#define BABEL_HH

#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include "IGui.hpp"
#include "ISound.hpp"
#include "ICompress.hpp"
#include "IUdp.hpp"
#include "rfc.hpp"

class BabelClient : public IGuiCallBack, public IUdpCallback
{
    public:
	BabelClient(IGui &gui, ISound &sound, ICompress &com, IUdp &udp);
	~BabelClient() {}
	int run();

	bool	callContactCallback(const std::string &name);
	bool	addContactCallback(const std::string &name);
	bool	delContactCallback(const std::string &name);
	bool	connectCallback(const std::string &ip, uint16_t port, const std::string &name, const std::string &pass);
	bool	registerCallback(const std::string &ip, uint16_t port, const std::string &name, const std::string &pass);
	void	closeCallback();

	int	openDirectCall();
	void	stopDirectCall();
	void	startDirectCall(const std::string &ip, int port);

	void	onReceiveUdp(char *data, uint64_t size);
    private:
	void	    sendPacket();

	IGui	    &mGui;
	ISound	    &mSound;
	ICompress   &mCompress;
	IUdp	    &mUdp;

	int32_t	    lastRecivedPacket;
	bool	    mRun;

	std::string mIp;
	int	    mPort;
};

#endif // BABEL_HH
