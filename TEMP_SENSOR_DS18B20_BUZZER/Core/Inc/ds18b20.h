/*
 * ds18b20.h
 *
 *  Created on: Nov 10, 2024
 *      Author: Aleh
 */

#ifndef INC_DS18B20_H_
#define INC_DS18B20_H_

float DS18B20_Temp(void);
void DS18B20_Write(uint8_t byte);
uint8_t DS18B20_Read(void);
uint8_t DS18B20_Reset(void);
void SetPinToOutput(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void SetPinToInput(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif /* INC_DS18B20_H_ */
