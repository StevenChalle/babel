#include "Opus.hpp"

Opus::Opus() :
m_error(0), m_de(0), m_en(0)
{}

Opus::~Opus()
{
    opus_decoder_destroy(m_de);
    opus_encoder_destroy(m_en);
}

bool Opus::init(int samplingRate)
{
    m_en = opus_encoder_create(samplingRate, 2, OPUS_APPLICATION_VOIP, &m_error);
    m_de = opus_decoder_create(samplingRate, 2, &m_error);
}

int32_t Opus::encode(const int16_t *in, int frameSize, unsigned char *out, int32_t max_out)
{
    return opus_encode(m_en, in, frameSize, out, max_out);
}

int Opus::decode(const unsigned char *in, int32_t len, int16_t *out, int frameSize)
{
    return opus_decode(m_de, in, len, out, frameSize, 0);
}
