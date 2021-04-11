/*
 * LCD-Task1.c
 *
 * Created: 4/10/2021 5:07:44 PM
 * Author : happikin
 */ 
/*#define F_CPU 16000000L
#include <avr/io.h>
#include "util/delay.h"*/

#define clearLCD 0x01
#define returnHome 0x02
#define decCursor 0x04
#define shrDisplay 0x05
#define incCursor 0x06
#define shlDisplay 0x07
#define dispOffcurOff 0x08
#define dispOffcuron 0x0A
#define dispOncurOff 0x0C
#define displayOnCursonBlink1 0x0E
#define displayOnCursonBlink2 0x0F
#define shlCursor 0x10
#define shrCursor 0x14
#define shlFullDisplay 0x18
#define shrFullDisplay 0x1C
#define begLine1 0x80
#define begLine2 0xC0
#define activate 0x38

#define set_pin(reg_name,pin_num) reg_name |= (1 << pin_num)
#define clr_pin(reg_name,pin_num) reg_name &= ~(1 << pin_num)
#define set_all(reg_name) reg_name = 0xff 
#define clr_all(reg_name) reg_name = 0x00

#define cmd_mode() clr_pin(PORTC,PINC7)
#define data_mode() set_pin(PORTC,PINC7)

#define write_mode() clr_pin(PORTC,PINC6)
#define read_mode() set_pin(PORTC,PINC6)

#define enable_high() set_pin(PORTC,PINC5)
#define enable_low() clr_pin(PORTC,PINC5)

/*
#define _swtch_inc_ !(PINB & (1 << PINB0))
#define _swtch_dec_ !(PINB & (1 << PINB1))
#define _switch3_ !(PINB & (1 << PINB2))
#define _switch4_ !(PIND & (1 << PIND7))
*/

#define __lcdport_ PORTA
/*
enum mode {
	Task1,
	Task2
};
*/

/*void __init_lcd_();
void lcd_data(uint8_t);
void lcd_cmd(uint8_t);
void lcd_curPos(uint8_t,uint8_t);
void lcd_NumPrint(int);
void lcd_print(char*);
int checkMode();
*/
void lcd_cmd(uint8_t cmd) {
	__lcdport_ = cmd;
	cmd_mode();
	enable_high();
	_delay_ms(2);
	enable_low();
}
void lcd_data(uint8_t data) {
	__lcdport_ = data;
	data_mode();
	enable_high();
	_delay_ms(2);
	enable_low();
}
void __init_lcd_() {
	uint8_t commands[] = {
		0x38,
		0x02,
		0x01,
		0x06,
		0x0F,
		0xC0
	};
	for(uint8_t i=0; i<6;i++) {
		lcd_cmd(commands[i]);
		_delay_ms(5);
	}
}
void lcd_print(char* p) {
	while(*p != '\0') {
		lcd_data(*p);
		p++;
	}
}
void lcd_curPos(uint8_t row, uint8_t col) {
	if(row == 0) {
		//cursor in top row
		lcd_cmd(begLine1+col);
	}
	else if(row == 1) {
		//cursor in bottom row
		lcd_cmd(begLine2+col);
	}
}
void lcd_NumPrint(int a) {
	lcd_cmd(clearLCD);
	_delay_ms(2);
	uint32_t q,r;
	q=a;
	int i=0;
	while(q) {
		r=q%10;
		q=q/10;
		r+=48;
		lcd_curPos(1,15-i);
		lcd_data((uint8_t)r);
		i++;
	}
	lcd_curPos(1,15-i);
}
/*
int checkMode() {
	if(_switch4_) {
		return Task1;
	}
	else {
		return Task2;
	}
}*/