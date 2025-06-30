/*
 * pwm.h
 *
 *  Created on: Jun 23, 2025
 *      Author: singh
 */
#include <stdint.h>

#ifndef PWM_H_
#define PWM_H_

void pwm_init_all();
void analogWrite(uint8_t channel, uint8_t value);

#endif /* PWM_H_ */
