/*
 * firmware-project-1.c
 *
 * Created: 7/3/2022 1:08:30 AM
 * Author : PhongEE & Manh
 */ 

#include "main.h"
#include <avr/io.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcdpcf8574.h"
#include "DHT.h"
#include "uart.h"


int main(void)
{
	DHT_Setup();
	config_display_lcd();
	config_uart();
	while(1) {
		get_value_dht();
		/* Sensor needs 1-2s to stabilize its readings */
		transmit_value();
		_delay_ms(2000);
	}
}

void config_display_lcd() {
	lcd_init(LCD_DISP_ON_BLINK);
	lcd_home();
	lcd_led(LED_LCD);
	lcd_puts("Humidity: ");
	lcd_gotoxy(0,1);
	lcd_puts("Temp: ");
}
void get_value_dht() {
	DHT_ReadRaw(data);
	switch (DHT_GetStatus())
	{
		case (DHT_Ok):
			display_value_dht_to_lcd();
			break;
		case (DHT_Error_Checksum):
			break;
		case (DHT_Error_Timeout):
			break;
	}
}
void display_value_dht_to_lcd() {
	itoa(data[0],str,10);
	lcd_gotoxy(10,0);
	lcd_puts(str);
	lcd_puts(".");
	
	itoa(data[1],str,10);
	lcd_puts(str);
	lcd_puts("%");

	itoa(data[2],str,10);
	lcd_gotoxy(10,1);
	lcd_puts(str);
	lcd_puts(".");
	
	itoa(data[3],str,10);
	lcd_puts(str);
	lcd_putc(0xDF);
	lcd_puts("C");
}
void config_uart() {
	uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));
	sei();
	uart_puts("Starting...");
}
void transmit_value() {
	char buffer_transmit[32];
	sprintf(buffer_transmit, "Humidity: %2d.%1d%%  Temp: %2d.%1d%cC\n", data[0], data[1], data[2], data[3], 0xB0);
	uart_puts(buffer_transmit);
}

