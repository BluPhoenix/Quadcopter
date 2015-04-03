#ifndef __SPI_H__
#define __SPI_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h> //memset
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>


class Spi
{
	private:
		int m_iSpiFd; // File Descriptors
		unsigned char m_cSpiMode; // SPI_CPOL and SPI_CPHA for config, 0 = Clock idle low, data on rising edge
		unsigned char m_cBitsPerWord;
		unsigned int m_uiSpiSpeed;
		bool m_bPulseCS;
		bool m_bCSHigh;
	public:
		// Speeds that appear to work: 0.5MHz, 1MHz, smaller Speeds work short, then time out
		// ATmega48 needs a Pulse of the CS line after every Byte transmitted
		Spi(int iDevice, unsigned int uiSpiSpeed, bool bCSHigh=true, bool bPulseCS=true, bool bClkActiveLow=true, bool bClkOnRisingEdge=true, unsigned char cBitsPerWord=8);
		~Spi();
		int Transfer(unsigned char *pData, int iLength);
};

#endif //__SPI_H__
