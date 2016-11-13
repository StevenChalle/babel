#ifndef UDP_HPP_
# define UDP_HPP_

#include <QUdpSocket>
#include <QCoreApplication>
#include <QHostAddress>
#include <QArrayData>
#include "IUdp.hpp"

Q_DECLARE_INTERFACE(IUdp, "UDP Interface")

class Udp : public QObject, public IUdp
{
	Q_OBJECT
	Q_INTERFACES(IUdp)
    public:
	Udp(int &ac, char **av);
	~Udp();

	void		send(const std::string &ip, uint16_t port, const char *data, int64_t size) const;
	void		setCallback(IUdpCallback *cb);
	uint16_t	create();
	void		update();
	void		stop();

    private slots:
	void	onRead();


    private:
	QCoreApplication    *mApp;
	QUdpSocket	    *mUdpSocket;
	IUdpCallback	    *mCb;
};

#endif /* !UDP_HPP_ */
