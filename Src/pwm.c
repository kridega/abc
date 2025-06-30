/*
 * pwm.c
 *
 *  Created on: Jun 23, 2025
 *      Author: singh
 */

#include <stdint.h>
#include "pwm.h"
#include "pins.h"
/* There are four channels
 * CH 1 PA0
 * CH 2 PA1
 * CH 3 PA6
 * CH 4 PA7*/

void pwm_init_all()
{
    // Enable TIM2, TIM3
    RCC_APB1ENR |= (1 << 0);  // TIM2
    RCC_APB1ENR |= (1 << 1);  // TIM3

    // Set PA0, PA1, PA6, PA7 to AF Push-Pull (output, 2MHz)
    GPIOA_CRL &= ~((0xF << 0) | (0xF << 4) | (0xF << 24) | (0xF << 28));
    GPIOA_CRL |=  ((0b1010 << 0) | (0b1010 << 4) | (0b1010 << 24) | (0b1010 << 28));

    // TIM2 setup
    TIM2_PSC = 71;       // 72MHz / (71+1) = 1MHz
    TIM2_ARR = 255;      // 8-bit resolution
    TIM2_CCMR1 |= (0b110 << 4) | (1 << 3);   // CH1: PWM mode 1 + preload
    TIM2_CCMR1 |= (0b110 << 12) | (1 << 11); // CH2: PWM mode 1 + preload
    TIM2_CCER |= (1 << 0) | (1 << 4);        // Enable CH1 and CH2 outputs
    TIM2_CR1 |= (1 << 7);                    // Auto-reload preload
    TIM2_CR1 |= (1 << 0);                    // Enable counter

    // TIM3 setup
    TIM3_PSC = 71;       // 1MHz
    TIM3_ARR = 255;
    TIM3_CCMR1 |= (0b110 << 4) | (1 << 3);   // CH1
    TIM3_CCMR1 |= (0b110 << 12) | (1 << 11); // CH2
    TIM3_CCER |= (1 << 0) | (1 << 4);        // Enable CH1 and CH2
    TIM3_CR1 |= (1 << 7);
    TIM3_CR1 |= (1 << 0);
}

void analogWrite(uint8_t channel, uint8_t value)
{
    if (value > 255) value = 255;

    switch(channel)
    {
        case 1:
        	TIM2_CCR1 = value;
        	break; // PA0
        case 2:
        	TIM2_CCR2 = value;
        	break; // PA1
        case 3:
        	TIM3_CCR1 = value;
        	break; // PA6
        case 4:
        	TIM3_CCR2 = value;
        	break; // PA7
        default:
        	return;
    }
}


