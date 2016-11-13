#ifndef PORTAUDIOSOUND_HH
#define PORTAUDIOSOUND_HH

#define CHECK_OVERFLOW  (0)
#define CHECK_UNDERFLOW  (0)
#define DITHER_FLAG     (0)

#include <iostream>
#include "ISound.hpp"
#include "portaudio.h"

class PaSound : public ISound
{
    public:
	PaSound() : m_stream(0), m_frameSize(0) {}
	~PaSound();

	bool	init();
	bool	startStream(double samplingRate, unsigned long frameSize);
	bool	stopStream();
	bool	closeStream();
	bool	readStream(void *buf);
	bool	writeStream(const void *buf);

    private:
	PaStream	*m_stream;
	unsigned long	m_frameSize;
};

#endif // PORTAUDIOSOUND_HH
