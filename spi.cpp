#include "spi.h"

Spi::Spi(int iDevice, unsigned int uiSpiSpeed, bool bCSHigh, bool bPulseCS, bool bClkActiveLow, bool bClkOnRisingEdge, unsigned char cBitsPerWord)
{
	m_bCSHigh = bCSHigh;
	m_bPulseCS = bPulseCS;
	m_cSpiMode = (bClkActiveLow ? 0 : SPI_CPOL) | (bClkOnRisingEdge ? 0 : SPI_CPHA) | (bCSHigh ? SPI_CS_HIGH : 0);
	m_uiSpiSpeed = uiSpiSpeed;
	m_cBitsPerWord = cBitsPerWord;
	m_iSpiFd = (iDevice == 0 ? open("/dev/spidev0.0", O_RDWR) : open("/dev/spidev0.1", O_RDWR));
	if (m_iSpiFd < 0)
	{
		perror("Error opening /dev/spidev0.*");
		exit(EXIT_FAILURE);
	}
	if (ioctl(m_iSpiFd, SPI_IOC_WR_MODE, &m_cSpiMode) < 0)
	{
		perror("Error SPI_IOC_WR_MODE");
		exit(EXIT_FAILURE);
	}
	if (ioctl(m_iSpiFd, SPI_IOC_RD_MODE, &m_cSpiMode) < 0)
	{
		perror("Error SPI_IOC_RD_MODE");
		exit(EXIT_FAILURE);
	}
	if (ioctl(m_iSpiFd, SPI_IOC_WR_BITS_PER_WORD, &m_cBitsPerWord) < 0)
	{
		perror("Error SPI_IOC_WR_BITS_PER_WORD");
		exit(EXIT_FAILURE);
	}
	if (ioctl(m_iSpiFd, SPI_IOC_RD_BITS_PER_WORD, &m_cBitsPerWord) < 0)
	{
		perror("Error SPI_IOC_RD_BITS_PER_WORD");
		exit(EXIT_FAILURE);
	}
	if (ioctl(m_iSpiFd, SPI_IOC_WR_MAX_SPEED_HZ, &m_uiSpiSpeed) < 0)
	{
		perror("Error SPI_IOC_WR_MAX_SPEED_HZ");
		exit(EXIT_FAILURE);
	}
	if (ioctl(m_iSpiFd, SPI_IOC_RD_MAX_SPEED_HZ, &m_uiSpiSpeed) < 0)
	{
		perror("Error SPI_IOC_RD_MAX_SPEED_HZ");
		exit(EXIT_FAILURE);
	}
}

int Spi::Transfer(unsigned char *pData, int iLength)
{
	struct spi_ioc_transfer spi;
	memset(&spi, 0, sizeof(spi)); //Really important!
	int iReturn = -1;

	spi.tx_buf = (unsigned long)pData;
	spi.rx_buf = (unsigned long)pData;
	spi.len = iLength;
	spi.delay_usecs = 0;
	spi.speed_hz = m_uiSpiSpeed;
	spi.bits_per_word = m_cBitsPerWord;
	spi.cs_change = m_bPulseCS;
	iReturn = ioctl(m_iSpiFd, SPI_IOC_MESSAGE(1), &spi);
	if (iReturn < 0) 
	{
		perror("Error Transmitting Data");
		exit(EXIT_FAILURE);
	}
	return iReturn;
}

Spi::~Spi()
{
	close(m_iSpiFd);
}
