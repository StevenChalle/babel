#include "Udp.hpp"

Udp::Udp(int &ac, char **av) :
    QObject(), mApp(0), mUdpSocket(0), mCb(0)
{
    if (QCoreApplication::startingUp())
    {
	mApp = new QCoreApplication(ac, av);
    }
}

Udp::~Udp()
{
    if (mUdpSocket)
    {
	mUdpSocket->close();
	mUdpSocket->deleteLater();
    }
    if (mApp)
	mApp->deleteLater();
}

void Udp::update()
{
    if (mApp)
	mApp->processEvents();
}

void		Udp::setCallback(IUdpCallback *cb)
{
    mCb = cb;
}

void Udp::send(const std::string &ip, uint16_t port, const char *data, int64_t size) const
{
    QUdpSocket	sock;

    sock.writeDatagram(data, size, QHostAddress(QString::fromStdString(ip)), port);
}

uint16_t	Udp::create()
{
    if (mUdpSocket)
    {
	mUdpSocket->close();
	delete mUdpSocket;
    }
    mUdpSocket = new QUdpSocket(this);

    mUdpSocket->bind((QHostAddress)QHostAddress::LocalHost, 0);
    connect(mUdpSocket, SIGNAL(readyRead()),
	    this, SLOT(onRead()));
    return (mUdpSocket->localPort());
}

void		Udp::stop()
{
    mUdpSocket->close();
}

void		Udp::onRead()
{
    while (mUdpSocket->hasPendingDatagrams())
    {
	QByteArray	datagram;
	datagram.resize(mUdpSocket->pendingDatagramSize());
	mUdpSocket->readDatagram(datagram.data(), datagram.size());
	if (mCb)
	    mCb->onReceiveUdp(datagram.data(), datagram.size());
    }
}
