/*
 * ds18b20.c
 *
 *  Created on: Nov 10, 2024
 *      Author: Aleh
 */

#include "main.h"
#include "ds18b20.h"

float DS18B20_Temp(void)
{
    uint8_t temp_lsb, temp_msb;
    int16_t raw_temp;

    DS18B20_Reset();       // Initialize communication
    DS18B20_Write(0xCC);   // Skip ROM command
    DS18B20_Write(0x44);   // Start temperature conversion
    HAL_Delay(750);        // Wait for conversion (750 ms for 12-bit resolution)

    DS18B20_Reset();       // Reset the bus
    DS18B20_Write(0xCC);   // Skip ROM command
    DS18B20_Write(0xBE);   // Read Scratchpad

    // Read temperature data
    temp_lsb = DS18B20_Read();
    temp_msb = DS18B20_Read();

    // Convert raw temperature to Celsius
    raw_temp = (temp_msb << 8) | temp_lsb;

    return (float)raw_temp / 16.0;
}

void DS18B20_Write(uint8_t byte)
{
	for (int i = 0; i < 8; i++)
	{
		if (byte & (1 << i))
		{
			setPinToOutput(GPIOA, GPIO_PIN_1);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
			delayUS_ASM(6);
			setPinToInput(GPIOA, GPIO_PIN_1);
			delayUS_ASM(64);
		}
		else
		{
			setPinToOutput(GPIOA, GPIO_PIN_1);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
            delayUS_ASM(60);
            setPinToInput(GPIOA, GPIO_PIN_1);
            delayUS_ASM(10);
		}
	}
}

uint8_t DS18B20_Read(void)
{
    uint8_t read_byte = 0;

    for (int i = 0; i < 8; i++)
    {
    	setPinToOutput(GPIOA, GPIO_PIN_1);
    	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
    	delayUS_ASM(6);
    	setPinToInput(GPIOA, GPIO_PIN_1);
        delayUS_ASM(9);

        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET)
        {
            read_byte |= (1 << i);
        }
        delayUS_ASM(55);
    }

    return read_byte;
}

uint8_t DS18B20_Reset(void)
{
	uint8_t sensor_present;

	setPinToOutput(GPIOA, GPIO_PIN_1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	delayUS_ASM(480);

	setPinToInput(GPIOA, GPIO_PIN_1);
	delayUS_ASM(60);

	//Checking presence pulse
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
    {
    	// Complete the reset sequence
        sensor_present = 1;
        delayUS_ASM(480);
    }
    else
    {
    	sensor_present = 0;
    }

    return sensor_present;
}

void setPinToInput(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    uint32_t 		  position = 0;
    uint32_t 		  register_offset;
    volatile uint32_t *config_register;
    uint32_t 		  temp;

    while (GPIO_Pin)
    {
        if (GPIO_Pin & 0x01)
        {
            register_offset = (position < 8) ? 0 : 1;
            config_register = &GPIOx->CRL + register_offset;

            temp =  *config_register;
            temp &= ~(0x0F << ((position & 0x07) * 4));
            temp |= (0x04 << ((position & 0x07) * 4));  // Input floating

            *config_register = temp;
        }

        position++;
        GPIO_Pin >>= 1;
    }
}

void setPinToOutput(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    uint32_t 		  position = 0;
    uint32_t 		  register_offset;
    volatile uint32_t *config_register;
    uint32_t 		  temp;

    while (GPIO_Pin)
    {
        if (GPIO_Pin & 0x01)
        {
            register_offset = (position < 8) ? 0 : 1;
            config_register = &GPIOx->CRL + register_offset;

            temp =  *config_register;
            temp &= ~(0x0F << ((position & 0x07) * 4));
            temp |= (0x01 << ((position & 0x07) * 4));  // Output push-pull

            *config_register = temp;
        }

        position++;
        GPIO_Pin >>= 1;
    }
}
