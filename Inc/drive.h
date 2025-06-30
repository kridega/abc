/*
 * drive.h
 *
 *  Created on: Jun 26, 2025
 *      Author: singh
 */

#ifndef DRIVE_H_
#define DRIVE_H_

#include <stdint.h>


void drive_init(void);
void drive_command(char cmd);
void drive_direction(uint8_t channel, uint8_t state);

#endif /* DRIVE_H_ */
