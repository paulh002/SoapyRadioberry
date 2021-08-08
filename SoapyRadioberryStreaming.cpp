#include "SoapyRadioberry.hpp"

 void SoapyRadioberry::setSampleRate( const int direction, const size_t channel, const double rate ) {
	SoapySDR_log(SOAPY_SDR_INFO, "SoapyRadioberry::setSampleRate called");
	
	int irate = floor(rate);
	uint32_t	ucom =0x00000004;
	
	 if (rate < 48001.0)
		 ucom = 0x00000004;
	 if (rate > 48000.0 && rate < 96001.0)
		 ucom = 0x01000004;
	 if (rate > 96000.0 && rate < 192001.0)
		 ucom = 0x02000004;
	 if (rate > 192000.0)
		 ucom = 0x03000004;
	
	this->SoapyRadioberry::controlRadioberry(0, ucom);
}

SoapySDR::RangeList SoapyRadioberry::getSampleRateRange(const int direction, const size_t channel) const 
{
	
	SoapySDR_log(SOAPY_SDR_INFO, "SoapyRadioberry::getSampleRateRange called");
	
	SoapySDR::RangeList rangeList;
	
	if (direction == SOAPY_SDR_RX) 	rangeList.push_back(SoapySDR::Range(48000.0, 192000.0, 1.0));
	if (direction == SOAPY_SDR_TX) 	rangeList.push_back(SoapySDR::Range(48000.0, 48000.0, 1.0));
	
	return rangeList;
}

std::vector<std::string> SoapyRadioberry::getStreamFormats(const int direction, const size_t channel) const
{
	SoapySDR_log(SOAPY_SDR_INFO, "SoapyRadioberry::getStreamFormats called");
	
	std::vector<std::string> formats;

	formats.push_back(SOAPY_SDR_CF32);

	return formats;
}

std::string SoapyRadioberry::getNativeStreamFormat(const int direction, const size_t channel, double &fullScale) const
{
	SoapySDR_log(SOAPY_SDR_INFO, "SoapyRadioberry::getNativeStreamFormat called");
	
	if (direction == SOAPY_SDR_RX) {
		fullScale = 2048; // RX expects 12 bit samples LSB aligned
	}
	else if (direction == SOAPY_SDR_TX) {
		fullScale = 32768; // TX expects 12 bit samples MSB aligned
	}
	return SOAPY_SDR_CF32;
}

SoapySDR::ArgInfoList SoapyRadioberry::getStreamArgsInfo(const int direction, const size_t channel) const
{
	SoapySDR::ArgInfoList streamArgs;
	
	SoapySDR::ArgInfo bufflenArg;
    bufflenArg.key = "bufflen";
    bufflenArg.value = "64"; 
    bufflenArg.name = "Buffer Size";
    bufflenArg.description = "Number of bytes per buffer, multiples of 512 only.";
    bufflenArg.units = "bytes";
    bufflenArg.type = SoapySDR::ArgInfo::INT;

    streamArgs.push_back(bufflenArg);

	return streamArgs;
}

SoapySDR::Stream *SoapyRadioberry::setupStream(
		const int direction,
		const std::string &format,
		const std::vector<size_t> &channels,
		const SoapySDR::Kwargs &args )
{
	SoapySDR_log(SOAPY_SDR_INFO, "SoapyRadioberry::setupStream called");
	
	//check the format
	if (format == SOAPY_SDR_CF32) {
		SoapySDR_log(SOAPY_SDR_INFO, "Using format CF32.");
	}
	else {
		throw std::runtime_error(
			"setupStream invalid format '" + format + "' -- Only CF32 is supported by SoapyRadioberrySDR module.");
	}

	return (SoapySDR::Stream *) this;

}

int SoapyRadioberry::readStream(
		SoapySDR::Stream *handle,
		void * const *buffs,
		const size_t numElems,
		int &flags,
		long long &timeNs,
		const long timeoutUs )
{
	int i;
	int iq = 0;
	int left_sample;
	int right_sample;
	int nr_samples;
	 
	void *buff_base = buffs[0];
	float *target_buffer = (float *) buff_base;
	
	char rx_buffer[512];
	for(int ii = 0 ; ii < npackages ; ii++)
	{
		nr_samples = read(fd_rb, rx_buffer, sizeof(rx_buffer));
		//printf("nr_samples %d sample: %d %d %d %d %d %d\n",nr_samples, (int)rx_buffer[0],(int)rx_buffer[1],(int)rx_buffer[2],(int)rx_buffer[3],(int)rx_buffer[4],(int)rx_buffer[5]);
		for(i = 0 ; i < nr_samples ; i += 6) {
			left_sample   = (int)((signed char) rx_buffer[i]) << 16;
			left_sample  |= (int)((((unsigned char)rx_buffer[i + 1]) << 8) & 0xFF00);
			left_sample  |= (int)((unsigned char)rx_buffer[i + 2] & 0xFF);
			right_sample  = (int)((signed char)rx_buffer[i + 3]) << 16;
			right_sample |= (int)((((unsigned char)rx_buffer[i + 4]) << 8) & 0xFF00);
			right_sample |= (int)((unsigned char)rx_buffer[i + 5] & 0xFF);

			target_buffer[iq++] = (float)left_sample / 2048.0;  // 12 bit sample
			target_buffer[iq++] = (float)right_sample / 2048.0;  // 12 bit sample
		}
	}
	
	return (npackages * nr_samples / 6); //return the number of IQ samples
}
