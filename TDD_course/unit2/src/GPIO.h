#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>

/**
 * @brief Init module 
 */
void GPIO_Init(void);

/**
 * @brief Set Pin as Output
 * @param[in] Pin Pin that will be defined with output
 * @return int Checks if the pin has been defined as output 
 */
int GPIO_SetPinAsOutput(uint8_t Pin);

/**
 * @brief Set Pin as Input
 * @param[in] Pin Pin that will be defined with Input
 * @return int Checks if the pin has been defined as Input
 */
int GPIO_SetPinAsInput(uint8_t Pin);

/**
 * @brief Set Pin High
 * @param[in] Pin Pin that will be defined with High
 * @return int Checks if the pin has been defined as High
 */
int GPIO_SetPinAsHigh(uint8_t  Pin);

/**
 * @brief Set Pin Low
 * @param[in] Pin Pin that will be defined with Low
 * @return int Checks if the pin has been defined as Low
 */
int GPIO_SetPinAsLow(uint8_t  Pin);

/**
 * @brief Read Pin
 * @param[in] Pin Pin that will be read
 * @return int read value
 */
int GPIO_ReadPin(uint8_t  Pin);



#endif //GPIO_H
