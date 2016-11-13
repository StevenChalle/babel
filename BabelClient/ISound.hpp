#ifndef ISOUND_HPP
#define ISOUND_HPP

#include <cstdint>

class ISound
{
    public:
	virtual ~ISound() {}

	virtual bool	init() = 0;
	virtual bool	startStream(double samplingRate, unsigned long frameSize) = 0;
	virtual bool	stopStream() = 0;
	virtual bool	closeStream() = 0;
	virtual bool	readStream(void *) = 0;
	virtual bool	writeStream(const void *) = 0;
};

#endif // ISOUND_HPP

