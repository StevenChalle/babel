#ifndef IUDPCALLBACK_HPP
#define IUDPCALLBACK_HPP

#include <cstdint>

class IUdpCallback
{
    public:
	virtual ~IUdpCallback() {}
	virtual void	onReceiveUdp(char *data, uint64_t size) = 0;
};

#endif // IUDPCALLBACK_HPP
