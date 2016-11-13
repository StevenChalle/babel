#ifndef OPUS_HH
#define OPUS_HH

#include "ICompress.hpp"
#include "opus.h"

class Opus : public ICompress
{
    public:
	Opus();
	~Opus();
	bool	init(int samplingRate);
	int32_t	encode(const int16_t *in, int frameSize, unsigned char *out, int32_t max_out);
	int	decode(const unsigned char *in, int32_t len, int16_t *out, int frameSize);
    private:
	int m_error;
	OpusDecoder *m_de;
	OpusEncoder *m_en;
};

#endif // OPUS_HH
