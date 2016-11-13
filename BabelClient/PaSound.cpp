#include "PaSound.hpp"

PaSound::~PaSound()
{
    closeStream();
    Pa_Terminate();
}

bool PaSound::init()
{
    PaError err;

    if ((err = Pa_Initialize()) != paNoError)
    {
	std::cerr << "Port audio error :" << Pa_GetErrorText(err) << std::endl;
	return false;
    }
    return true;
}

bool PaSound::startStream(double samplingRate, unsigned long frameSize)
{
    PaError err;

    m_frameSize = frameSize;
    if (m_stream)
    {
	closeStream();
    }
    if ((err=Pa_OpenDefaultStream(&m_stream, 2, 2, paInt16, samplingRate, frameSize, 0, 0)))
    {
	std::cerr << "Port audio error :" << Pa_GetErrorText(err) << std::endl;
	return false;
    }
    if ((err = Pa_StartStream(m_stream)) != paNoError)
    {
	std::cerr << "Port audio error :" << Pa_GetErrorText(err) << std::endl;
	return false;
    }
    return true;
}

bool PaSound::stopStream()
{
    PaError err;

    if (m_stream)
    {
	if ((err = Pa_StopStream(m_stream)) != paNoError)
	{
	    std::cerr << "Port audio error :" << Pa_GetErrorText(err) << std::endl;
	    return false;
	}
    }
    return true;
}

bool PaSound::closeStream()
{
    PaError err;

    if (m_stream)
    {
	if ((err = Pa_CloseStream(m_stream)) != paNoError)
	{
	    std::cerr << "Port audio error :" << Pa_GetErrorText(err) << std::endl;
	    return false;
	}
	m_stream = 0;
    }
    return true;
}

bool PaSound::readStream(void *buf)
{
    PaError err;

    if ((err = Pa_ReadStream(m_stream, buf, m_frameSize)) != paNoError)
    {
	std::cerr << "Port audio read error :" << Pa_GetErrorText(err) << std::endl;
	return false;
    }
    return true;
}

bool PaSound::writeStream(const void *buf)
{
    PaError err;

    if ((err = Pa_WriteStream(m_stream, buf, m_frameSize)) != paNoError)
    {
	std::cerr << "Port audio write error :" << Pa_GetErrorText(err) << std::endl;
	return false;
    }
    return true;
}
