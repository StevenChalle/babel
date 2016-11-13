#ifndef ICOMPRESS
#define ICOMPRESS

#include <cstdint>

class	ICompress
{
    public:
	virtual ~ICompress() {}

	virtual bool	init(int samplingRate) = 0;
	virtual int32_t	encode(const int16_t *in, int frameSize, unsigned char *out, int32_t max_out) = 0;
	virtual int	decode(const unsigned char *in, int32_t len, int16_t *out, int frameSize) = 0;
};

#endif // ICOMPRESS
