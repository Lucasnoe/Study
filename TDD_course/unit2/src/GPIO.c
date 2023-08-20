#include "GPIO.h"
#include "MK20DX256.h"

void GPIO_Init(void)
{
    PORTC.PDDR = 0x1012A000;
    PORTC.PSOR = 0x10102000;
    PORTC.PCOR = 0x00028000;
}

int GPIO_SetPinAsOutput(uint8_t  Pin)
{   if(Pin>=32 || Pin< 0)
{
    return 0;
}
        else
        {
            PORTC.PDDR |= BIT_TO_MASK(Pin);
            return 1;
        }
}
int GPIO_SetPinAsInput(uint8_t  Pin)
{  if(Pin>=32 || Pin< 0)
{
    return 0;
}
        else
        {
            PORTC.PDDR &= ~(BIT_TO_MASK(Pin));
            return 1;
        }
    

}
int GPIO_SetPinAsHigh(uint8_t  Pin)
{   if(Pin<32 && Pin >= 0)
    {
      
        if(((BIT_TO_MASK(Pin)&(PORTC.PDDR)) == 0))
        {   
            PORTC.PDDR |= BIT_TO_MASK(Pin);
        } //end if

        if((BIT_TO_MASK(Pin)&(PORTC.PCOR)) > 0)
        {
            PORTC.PCOR &= ~(BIT_TO_MASK(Pin));
        } //end if

    PORTC.PSOR |= BIT_TO_MASK(Pin);
    return GPIO_OK;

    } //end if
    else
    {
        return 0;   
        
    } //end else
      
}//end function

int GPIO_SetPinAsLow(uint8_t  Pin)
{   if(Pin<32 && Pin >= 0)
    {
      
        if(((BIT_TO_MASK(Pin)&(PORTC.PDDR)) == 0))
        {   
            PORTC.PDDR |= BIT_TO_MASK(Pin);
        } //end if

        if((BIT_TO_MASK(Pin)&(PORTC.PSOR)) > 0)
        {
            PORTC.PCOR &= ~(BIT_TO_MASK(Pin));
        } //end if

    PORTC.PCOR |= BIT_TO_MASK(Pin);
    return GPIO_OK;

    } //end if
    else
    {
        return 0;   
        
    } //end else
      
}//end function

int GPIO_ReadPin(uint8_t  Pin)
{
    if(Pin<32 && Pin >= 0) //verfica se o pino é válido
    {
        if(((BIT_TO_MASK(Pin)&(PORTC.PDDR)) > 0)) // verifica se o pino já foi definido como Entrada
        {   
            PORTC.PDDR &= ~(BIT_TO_MASK(Pin));
        } //end if

        if((BIT_TO_MASK(Pin)&PORTC.PDIR) > 0)
        {
            return 1;
        }
        else if((BIT_TO_MASK(Pin)&PORTC.PDIR) == 0)
        {
            return 0;
        }
    }
    else
    {
        return -1;
    }
}
