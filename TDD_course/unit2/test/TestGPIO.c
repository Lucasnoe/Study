/**@file TestGPIO.c
 * Arquivo de teste do módulo GPIO
 * O driver de GPIO deve ter as seguintes especificações
 *  1. Each pin can be set as Input/output
 *  2. Each pin can be set as high or low
 *  3. Each pin can be read
 *  4. Each port can be read in one word
 *  5. Has init function to be config defaults by pin
 *  6. Each pin can be configured for GPIO
 *  7. Each pin can have its active polarity reversed
*/
#include "unity.h"
#include "GPIO.h"
#include "MK20DX256.h"
#include <stdint.h>

#define TEST_GPIO ALL

#if (TEST_GPIO == 0 || TEST_GPIO == ALL) /// Funções que testam registrador de direção - Output

/**Testa a função "SetPinAsOutput e deve configurar a direção do Pino usando os valor do registrador"*/
void test_SetPinAsOutput_should_ConfigurePInDirection_UsingRegisterValues(void)
{
    PORTC.PDDR =0;

    GPIO_SetPinAsOutput(0);
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0), PORTC.PDDR);
    GPIO_SetPinAsOutput(22);
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0) | BIT_TO_MASK(22), PORTC.PDDR);
    GPIO_SetPinAsOutput(31);
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(31)|BIT_TO_MASK(22)|BIT_TO_MASK(0), PORTC.PDDR);
    
}
/**Testa a função "SetPinAsOutput e deve configurar a direção do Pino usando o retorno da função"*/
void test_SetPinAsOutput_should_ConfigurePInDirection_UsingFunctionReturn(void)
{
    PORTC.PDDR =0;
    for(int i=0; i<32; i++)
    {
    TEST_ASSERT_EQUAL(1, GPIO_SetPinAsOutput(i));
    }
}

/**Testa a função "SetPinAsOutput e não deve configurar a direção do Pino se o valor de entrada não correspoder a um pino válido"*/
void test_SetPinAsOutput_should_NotUpdatePinDirection_when_PinsNotValid(void)
{
    PORTC.PDDR = 0;
    GPIO_SetPinAsOutput(32);
    TEST_ASSERT_EQUAL_HEX32(0, PORTC.PDDR);
}

#endif 

#if (TEST_GPIO == 1 || TEST_GPIO == ALL)  /// Funções que testam registrador de direção - Output

/**Testa a função "SetPinAsOutput e deve configurar a direção do Pino usando os valor do registrador"*/
void test_SetPinAsInput_should_ConfigurePInDirection_UsingRegisterValues(void)
{
    PORTC.PDDR =0xFFFFFFFF;

    GPIO_SetPinAsInput(0);
    TEST_ASSERT_EQUAL_HEX32(~BIT_TO_MASK(0), PORTC.PDDR);
    GPIO_SetPinAsInput(22);
    TEST_ASSERT_EQUAL_HEX32(~(BIT_TO_MASK(0) | BIT_TO_MASK(22)), PORTC.PDDR);
    GPIO_SetPinAsInput(31);
    TEST_ASSERT_EQUAL_HEX32(~(BIT_TO_MASK(31)|BIT_TO_MASK(22)|BIT_TO_MASK(0)), PORTC.PDDR);
    
}
/**Testa a função "SetPinAsOutput e deve configurar a direção do Pino usando o retorno da função"*/
void test_SetPinAsInput_should_ConfigurePInDirection_UsingFunctionReturn(void)
{
    PORTC.PDDR =0xFFFFFFFF;
    for(int i=0; i<32; i++)
    {
    TEST_ASSERT_EQUAL(1, GPIO_SetPinAsInput(i));
    }
}

/**Testa a função "SetPinAsOutput e não deve configurar a direção do Pino se o valor de entrada não correspoder a um pino válido"*/
void test_SetPinAsInput_should_NotUpdatePinDirection_when_PinsNotValid(void)
{
    PORTC.PDDR =0xFFFFFFFF;
    GPIO_SetPinAsInput(32);
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFF, PORTC.PDDR);
}

#endif 

#if (TEST_GPIO == 2 || TEST_GPIO == ALL) /// Funções que testam registrador de Saída de dados

void test_Setpin_should_SetOutputHigh(void)
{
    PORTC.PDDR = 0x00000000;
    PORTC.PSOR = 0x00000000;
    PORTC.PCOR = 0x00000000;
    uint32_t mask = 0x00000000;

    for(int i=0; i<32; i++ )
    {
        TEST_ASSERT_EQUAL(GPIO_OK, GPIO_SetPinAsHigh(i));
        mask|= BIT_TO_MASK(i);
        TEST_ASSERT_EQUAL_HEX32(mask, PORTC.PDDR);
        TEST_ASSERT_EQUAL_HEX32(mask, PORTC.PSOR);
        TEST_ASSERT_EQUAL_HEX32(0,PORTC.PCOR);
    }
    
}

void test_Setpin_should_SetOutputLow(void)
{
    PORTC.PDDR = 0x00000000;
    PORTC.PSOR = 0x00000000;
    PORTC.PCOR = 0x00000000;
    uint32_t mask = 0x00000000;

    for(int i=0; i<32; i++ )
    {
        TEST_ASSERT_EQUAL(GPIO_OK, GPIO_SetPinAsLow(i));
        mask|= BIT_TO_MASK(i);
        TEST_ASSERT_EQUAL_HEX32(mask, PORTC.PDDR);
        TEST_ASSERT_EQUAL_HEX32(mask, PORTC.PCOR);
        TEST_ASSERT_EQUAL_HEX32(0,PORTC.PSOR);
    }
}

void test_Setpin_should_ForceToOutput_when_ConfiguredAsInput(void)
{
    PORTC.PDDR=0x00000000;
    uint32_t mask_High = 0x00000000;
    uint32_t mask_Low = 0x00000000;

    for(int i = 0; i<32; i++)
    {
        GPIO_SetPinAsHigh(i);
        GPIO_SetPinAsLow(i);
        mask_Low|= BIT_TO_MASK(i);
        mask_High|= BIT_TO_MASK(i);
        TEST_ASSERT_EQUAL_HEX32(mask_Low, PORTC.PDDR);
        TEST_ASSERT_EQUAL_HEX32(mask_High, PORTC.PDDR);
    }
}

#endif

#if (TEST_GPIO == 3 || TEST_GPIO == ALL) /// Funções que testam registrador Entrada de dados
void test_ReadPin_should_ReturnPinValue(void)
{
    PORTC.PDIR = 0x845AC3E1;

    TEST_ASSERT_EQUAL(1, GPIO_ReadPin(0));
    TEST_ASSERT_EQUAL(0, GPIO_ReadPin(3));
    TEST_ASSERT_EQUAL(0, GPIO_ReadPin(29));
    TEST_ASSERT_EQUAL(1, GPIO_ReadPin(31));
    TEST_ASSERT_EQUAL(-1, GPIO_ReadPin(35));

    TEST_ASSERT_EQUAL_HEX32(0x845AC3E1, PORTC.PDIR);
}

void test_init_should_ConfigurePinsToDefaults(void)
{
    PORTC.PDDR = 0;
    PORTC.PSOR = 0;
    PORTC.PCOR = 0;

    GPIO_Init();
    TEST_ASSERT_EQUAL_HEX32(0x1012A000,PORTC.PDDR);
    TEST_ASSERT_EQUAL_HEX32(0x10102000,PORTC.PSOR);
    TEST_ASSERT_EQUAL_HEX32(0x00028000,PORTC.PCOR);
    // UNITY_TEST_ASSERT_EQUAL_HEX32(,PORTC.PDIR);
}

#endif
///Executa antes de cada teste
void setUp(void){ 
    GPIO_Init();
}      

///Exectuta depois de cada teste
void tearDown(void){}   


int main(void) 
{
    UNITY_BEGIN();
    #if (TEST_GPIO == 0 || TEST_GPIO == ALL) 
    RUN_TEST(test_SetPinAsOutput_should_NotUpdatePinDirection_when_PinsNotValid);
    RUN_TEST(test_SetPinAsOutput_should_ConfigurePInDirection_UsingRegisterValues);
    RUN_TEST(test_SetPinAsOutput_should_ConfigurePInDirection_UsingFunctionReturn);
    #endif

    #if (TEST_GPIO == 1 || TEST_GPIO == ALL) 
    RUN_TEST(test_SetPinAsInput_should_NotUpdatePinDirection_when_PinsNotValid);
    RUN_TEST(test_SetPinAsInput_should_ConfigurePInDirection_UsingRegisterValues);
    RUN_TEST(test_SetPinAsInput_should_ConfigurePInDirection_UsingFunctionReturn);
    #endif

    #if (TEST_GPIO == 2 || TEST_GPIO == ALL) 
    RUN_TEST(test_Setpin_should_SetOutputHigh);
    RUN_TEST(test_Setpin_should_SetOutputLow);
    RUN_TEST(test_Setpin_should_ForceToOutput_when_ConfiguredAsInput);
    #endif

    #if (TEST_GPIO == 3 || TEST_GPIO == ALL)
    RUN_TEST(test_ReadPin_should_ReturnPinValue);
    RUN_TEST(test_init_should_ConfigurePinsToDefaults);
    #endif

    return UNITY_END();
}
