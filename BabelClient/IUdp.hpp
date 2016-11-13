#ifndef IUDP_HPP_
# define IUDP_HPP_

#include <cstdint>
#include "IUdpCallback.hpp"

class IUdp
{
    public:
	virtual ~IUdp() {}
	virtual void		send(const std::string &ip, uint16_t port, const char *data, int64_t size) const = 0;
	virtual void		setCallback(IUdpCallback *) = 0;
	virtual uint16_t	create() = 0;
	virtual void		update() = 0;
	virtual void		stop() = 0;
};

#endif /* !IUDP_HPP_ */
