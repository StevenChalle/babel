#include "BabelClient.hpp"

BabelClient::BabelClient(IGui &gui, ISound &sound, ICompress &com, IUdp &udp):
    mGui(gui), mSound(sound), mCompress(com), mUdp(udp),
    mRun(true), lastRecivedPacket(0), mPort(0)
{
    mSound.init();
    mCompress.init(48000);
    mGui.setCallback(this);
    mUdp.setCallback(this);
}

int BabelClient::run()
{
    std::chrono::milliseconds base(30);

    mGui.notice("Welcome !");
    while (mRun)
    {
	auto start = std::chrono::high_resolution_clock::now();
	mGui.update();
	mUdp.update();
	if (mPort)
	    sendPacket();
	auto end = std::chrono::high_resolution_clock::now();
	if (!mPort)
	    std::this_thread::sleep_for(base - (end - start));
    }
    return (0);
}

bool BabelClient::callContactCallback(const std::string &name)
{

}

bool BabelClient::addContactCallback(const std::string &name)
{

}

bool BabelClient::delContactCallback(const std::string &name)
{

}

bool BabelClient::connectCallback(const std::string &ip, uint16_t port, const std::string &name, const std::string &pass)
{

}

bool BabelClient::registerCallback(const std::string &ip, uint16_t port, const std::string &name, const std::string &pass)
{

}

void BabelClient::closeCallback()
{
    mRun = false;
}

int BabelClient::openDirectCall()
{
    return mUdp.create();
}

void BabelClient::stopDirectCall()
{
    mPort = 0;
    mUdp.stop();
    mSound.closeStream();
}

void BabelClient::startDirectCall(const std::string &ip, int port)
{
    mSound.startStream(48000, 480);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    mIp = ip;
    mPort = port;
}

void BabelClient::onReceiveUdp(char *data, uint64_t size)
{
    RFC::AudioPacket	*ap;
    int16_t		buf[480 * 2];

    ap = (RFC::AudioPacket *)data;
    if (ap->timestamp < lastRecivedPacket)
	return;
    lastRecivedPacket = ap->timestamp;
    mCompress.decode(ap->soundData, (int32_t)(size - sizeof(ap->timestamp)), buf, 480);
    mSound.writeStream(buf);
}

void BabelClient::sendPacket()
{
    int16_t    baseAudio[480 * 2];
    char    baseData[512];
    int32_t len;
    RFC::AudioPacket	*ap = (RFC::AudioPacket *)baseData;

    ap->timestamp = std::time(0);
    mSound.readStream(baseAudio);
    len = mCompress.encode(baseAudio, 480, ap->soundData, 512 - sizeof(ap->timestamp));
    mUdp.send(mIp, mPort, baseData, len + sizeof(ap->timestamp));
}
