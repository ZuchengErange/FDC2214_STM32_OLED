#ifndef __SPI_H__
#define __SPI_H__

#define SPI1_GPIO GPIOA
#define SPI1_GPIO_Init RCC_APB2Periph_GPIOA
#define SPI1_CLK_Init GPIO_Pin_5
#define SPI1_MISO_Init GPIO_Pin_6
#define SPI1_MOSI_Init GPIO_Pin_7

#define SPI2_GPIO GPIOB
#define SPI2_GPIO_Init RCC_APB2Periph_GPIOB
#define SPI2_CLK_Init GPIO_Pin_13
#define SPI2_MISO_Init GPIO_Pin_14
#define SPI2_MOSI_Init GPIO_Pin_15

#define SPI_Buff(SPIx) SPIx->DR
#define SPI_SendBusy(SPIx) (SPIx->SR & SPI_I2S_FLAG_TXE)
#define SPI_RecvBusy(SPIx) (SPIx->SR & SPI_I2S_FLAG_RXNE)
#define SPI_SetDataSize_8b(SPIx) (SPIx->CR1&=~(0x01<<11))
#define SPI_SetDataSize_16b(SPIx) (SPIx->CR1|=(0x01<<11))

void SPI1_Init(unsigned short CPOL,unsigned short CPHA);
void SPI2_Init(unsigned short CPOL,unsigned short CPHA);
void SPI_SetSpeed(SPI_TypeDef* SPIx,unsigned char SPI_BaudRatePrescaler);

#endif
