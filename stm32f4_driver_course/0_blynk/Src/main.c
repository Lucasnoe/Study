// Placa STM32WL Nucleo-64 board (MB1389)
// LED ON Board:
// LED user 1 - PB15
// LED user 2 - PB9
// LED user 3 - PB11

// **** Mapeando os endereços dos barramentos ****

#define PERIPH_BASE 		(0x40000000UL) // Endereço inicial dos periféricos

#define AHB2PERIPH_OFFSET 	(0x08000000UL) // Endereço relativo inicial do barramento AHB2 de periféricos

#define AHB2PERIPH_BASE 	(PERIPH_BASE + AHB2PERIPH_OFFSET) //ENdereço global do Barramento AHB2

//#define GPIOB_OFFSET  		(0x0400UL) // Endereço relativo inicial do GPIO_B A partir do Endereço Inicial do Barramento AHB2

#define GPIOB_BASE  		(AHB2PERIPH_BASE) //Endereço global do GPIOB

#define AHB3PERIPH_OFFSET 	(0x18000000UL) // Endereço relativo inicial do barramento AHB3 de periféricos

#define AHB3PERIPH_BASE  	(PERIPH_BASE + AHB3PERIPH_OFFSET) //ENdereço global do Barramento AHB3

#define RCC_OFFSET  		(0x0000UL) //Endereço relativo do RCC - CLOCL CONTROL REGISTER a partir do barramento AHB3

#define RCC_BASE 			(AHB3PERIPH_BASE + RCC_OFFSET) //Endereço global do RCC

#define AHB2EN_R_OFFSET  	(0x004CUL) // Endereço relativo do peripheral clock enable register a partir do endereço RCC_BASE

#define RCC_AHB2EN_R 		(*(volatile unsigned int *)(RCC_BASE + AHB2EN_R_OFFSET)) //Endereço global do registrador de habilitação do clock nos periférico GPIO

#define MODEB_R_OFFSET 		(0x0400UL) // Endereço relativo do registrador mode register no portB em relação ao GPIOB_BASE

#define GPIOB_MODE_R  		(*(volatile unsigned int *)(GPIOB_BASE + MODEB_R_OFFSET)) //Endereço global do registrador Mode register no portB

#define GPIOB_OD_R_OFFSET 	(0x0414UL) // Endereço relativo do registrador GPIO Output Datw

#define GPIOB_OD_R  		(*(volatile unsigned int *)(GPIOB_OD_R_OFFSET + GPIOB_BASE)) //ENdereço global do registrador GPIO Output Data

#define GPIOBEN  			(1U<<1) // Habilitar o clock para a GPIOB

#define PIN15 				(1U << 15)
#define PIN11 				(1U << 11)
#define PIN9  				(1U << 9)

/* ----Macros---- */

//set bit

#define set_bit(Y,bit_x) (Y|=(1<<bit_x))

//clear bit

#define clr_bit(Y,bit_x) (Y&=~(1<<bit_x))

//toggle bit

#define tog_bit(Y,bit_x) (Y^=(1<<bit_x))

int main(void){

	RCC_AHB2EN_R |= (1<<1);   //Habilita o acesso do clock ao PORTB
	GPIOB_MODE_R |= (1<<22);  //Define o pino 9 como OUTPUT
	GPIOB_MODE_R &= ~(1<<23);  //Define o pino 9 como OUTPUT

	GPIOB_MODE_R |= (1<<18);  //Define o pino 9 como OUTPUT
	GPIOB_MODE_R &= ~(1<<19);  //Define o pino 9 como OUTPUT

	GPIOB_MODE_R |= (1<<30);  //Define o pino 9 como OUTPUT
	GPIOB_MODE_R &= ~(1<<31);  //Define o pino 9 como OUTPUT


//	set_bit(RCC_AHB2EN_R,1);
//	set_bit(GPIOB_MODE_R,22);
//	clr_bit(GPIOB_MODE_R,23);

	while(1){
//		GPIOB_OD_R ^= PIN11;   //HAbilita o pino 9
		tog_bit(GPIOB_OD_R,11);
		for(int i =0; i<100000 ; i++){}
		tog_bit(GPIOB_OD_R,9);
		for(int i =0; i<100000 ; i++){}
		tog_bit(GPIOB_OD_R,15);
		for(int i =0; i<100000 ; i++){}

	}

}






