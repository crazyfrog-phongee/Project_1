/*
 * main.h
 *
 * Created: 7/1/2022 5:49:47 PM
 * Author: PhongEE & Manh
 */ 


#ifndef MAIN_H_
#define MAIN_H_


#include <stdint.h>
#include "avr_config.h"

#define DATA_SIZE 4
#define MIN_WIDTH_FLOAT 5

uint8_t data[DATA_SIZE];
char str[MIN_WIDTH_FLOAT];

void config_display_lcd(void);
void get_value_dht(void);
void display_value_dht_to_lcd(void);
void config_uart(void);
void transmit_value(void);
#endif /* MAIN_H_ */