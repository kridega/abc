/*
 * drive.h
 *
 *  Created on: Jun 26, 2025
 *      Author: singh
 */

#ifndef DRIVE_H_
#define DRIVE_H_

#include <stdint.h>

const int MAX_AXES = 8;
float axes[MAX_AXES] = {0.0};

const int MAX_BUTTONS = 15;
int buttons[MAX_BUTTONS] = {0};


void drive_init(void);
void drive_command(char cmd);
void drive_direction(uint8_t channel, uint8_t state);

#endif /* DRIVE_H_ */
