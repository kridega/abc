/*
 * pins.h
 *
 *  Created on: Jun 23, 2025
 *      Author: singh
 */
#include <stdint.h>
// ===============================
// RCC Registers
// ===============================
#define RCC_APB2ENR    (*(volatile uint32_t *)(0x40021018))
#define RCC_APB1ENR    (*(volatile uint32_t *)(0x4002101C))

// ===============================
// TIM2 Registers
// ===============================
#define TIM2_PSC       (*(volatile uint32_t *)(0x40000028))
#define TIM2_ARR       (*(volatile uint32_t *)(0x4000002C))
#define TIM2_CCR1      (*(volatile uint32_t *)(0x40000034))
#define TIM2_CCR2      (*(volatile uint32_t *)(0x40000038))
#define TIM2_CCMR1     (*(volatile uint32_t *)(0x40000018))
#define TIM2_CCER      (*(volatile uint32_t *)(0x40000020))
#define TIM2_CR1       (*(volatile uint32_t *)(0x40000000))

// ===============================
// TIM3 Registers
// ===============================
#define TIM3_PSC       (*(volatile uint32_t *)(0x40000428))
#define TIM3_ARR       (*(volatile uint32_t *)(0x4000042C))
#define TIM3_CCR1      (*(volatile uint32_t *)(0x40000434))
#define TIM3_CCR2      (*(volatile uint32_t *)(0x40000438))
#define TIM3_CCMR1     (*(volatile uint32_t *)(0x40000418))
#define TIM3_CCER      (*(volatile uint32_t *)(0x40000420))
#define TIM3_CR1       (*(volatile uint32_t *)(0x40000400))

// ===============================
// GPIOA and GPIOB
// ===============================
#define GPIOA_CRL      (*(volatile uint32_t *)(0x40010800))
#define GPIOA_CRH      (*(volatile uint32_t *)(0x40010804))
#define GPIOA_IDR      (*(volatile uint32_t *)(0x40010808))
#define GPIOA_ODR      (*(volatile uint32_t *)(0x4001080C))

#define GPIOB_CRL      (*(volatile uint32_t *)(0x40010C00))
#define GPIOB_CRH      (*(volatile uint32_t *)(0x40010C04))
#define GPIOB_IDR      (*(volatile uint32_t *)(0x40010C08))
#define GPIOB_ODR      (*(volatile uint32_t *)(0x40010C0C))

// ===============================
// USART2 Registers
// ===============================
#define USART2_SR      (*(volatile uint32_t *)(0x40004400 + 0x00))
#define USART2_DR      (*(volatile uint32_t *)(0x40004400 + 0x04))
#define USART2_BRR     (*(volatile uint32_t *)(0x40004400 + 0x08))
#define USART2_CR1     (*(volatile uint32_t *)(0x40004400 + 0x0C))
#define USART2_CR2     (*(volatile uint32_t *)(0x40004400 + 0x10))
#define USART2_CR3     (*(volatile uint32_t *)(0x40004400 + 0x14))

// ===============================
// NVIC Interrupt Enable
// ===============================
#define NVIC_ISER1     (*(volatile uint32_t *)(0xE000E100 + 0x04))  // For IRQ >= 32

#ifndef PINS_H_
#define PINS_H_

/*
typedef struct{//0x40021018
	uint32_t afio_en   :1;
	uint32_t reserved1 :1;
	uint32_t ioa_en    :1;
	uint32_t iob_en    :1;
	uint32_t ioc_en    :1;
	uint32_t iod_en    :1;
	uint32_t ioe_en    :1;
	uint32_t reserved2 :2;
	uint32_t adc1_en   :1;
	uint32_t adc2_en   :1;
	uint32_t tim1_en   :1;
	uint32_t spi1_en   :1;
	uint32_t reserved3 :1;
	uint32_t usart1_en :1;
	uint32_t reserved4 :17;
}RCC_APB2ENR_t;

typedef struct{
	uint32_t mode0 :2;
	uint32_t cnf0  :2;
	uint32_t mode1 :2;
	uint32_t cnf1  :2;
	uint32_t mode2 :2;
	uint32_t cnf2  :2;
	uint32_t mode3 :2;
	uint32_t cnf3  :2;
	uint32_t mode4 :2;
	uint32_t cnf4  :2;
	uint32_t mode5 :2;
	uint32_t cnf5  :2;
	uint32_t mode6 :2;
	uint32_t cnf6  :2;
	uint32_t mode7 :2;
	uint32_t cnf7  :2;
}GPIOx_CRL_t;

typedef struct{
	uint32_t mode8  :2;
	uint32_t cnf8   :2;
	uint32_t mode9  :2;
	uint32_t cnf9   :2;
	uint32_t mode10 :2;
	uint32_t cnf10  :2;
	uint32_t mode11 :2;
	uint32_t cnf11  :2;
	uint32_t mode12 :2;
	uint32_t cnf12  :2;
	uint32_t mode13 :2;
	uint32_t cnf13  :2;
	uint32_t mode14 :2;
	uint32_t cnf14  :2;
	uint32_t mode15 :2;
	uint32_t cnf15  :2;
}GPIOx_CRH_t;

typedef struct{
	uint32_t pin_0 :1;
	uint32_t pin_1 :1;
	uint32_t pin_2 :1;
	uint32_t pin_3 :1;
	uint32_t pin_4 :1;
	uint32_t pin_5 :1;
	uint32_t pin_6 :1;
	uint32_t pin_7 :1;
	uint32_t pin_8 :1;
	uint32_t pin_9 :1;
	uint32_t pin_10 :1;
	uint32_t pin_11 :1;
	uint32_t pin_12 :1;
	uint32_t pin_13 :1;
	uint32_t pin_14 :1;
	uint32_t pin_15 :1;
	uint32_t reserved :16;
}GPIOx_ODR_t;

typedef struct{
	uint32_t pin_0 :1;
	uint32_t pin_1 :1;
	uint32_t pin_2 :1;
	uint32_t pin_3 :1;
	uint32_t pin_4 :1;
	uint32_t pin_5 :1;
	uint32_t pin_6 :1;
	uint32_t pin_7 :1;
	uint32_t pin_8 :1;
	uint32_t pin_9 :1;
	uint32_t pin_10 :1;
	uint32_t pin_11 :1;
	uint32_t pin_12 :1;
	uint32_t pin_13 :1;
	uint32_t pin_14 :1;
	uint32_t pin_15 :1;
	uint32_t reserved :16;
}GPIOx_IDR_t;
*/


#endif /* PINS_H_ */
