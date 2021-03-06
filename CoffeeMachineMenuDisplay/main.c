/*
 * CoffeeMachineMenuDisplay.c
 *
 * Created: 4/11/2021 12:04:40 PM
 * Author : happikin(Yashesvi)
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include "util/delay.h"
#include "liquidCrystal.h"
#define _switch_up_ !(PINB & (1 << 7))
#define _switch_down_ !(PINB & (1 << 6))
#define _switch_ok_ !(PINB & (1 << 5))
#define _switch_cancel_ !(PINB & (1 << 4))
typedef struct {
	char* coffee_name;
	uint8_t price;
} menu_items;

menu_items coffee_types[] = {
	{"cappuccino    50",50},
	{"espresso      27",27},
	{"black coffee  10",10},
	{"smoothie      45",45},
	{"americano     79",79},
	{"cafe cubano  101",101},
	{"frappuccino  156",156}
};
typedef enum {invalid,valid} flag;
typedef struct {
		char *mode_name;
		flag mode_status;
} modes;

volatile int item=0,previtem;
void showItem();
uint8_t sw_up = 0;
void lcd_FloatingPrint(char*);
int menu_nav();
int main(void)
{	
	set_all(DDRA);
	set_all(DDRC);
	clr_all(DDRB);
	set_pin(PORTB,PINB7);
	set_pin(PORTB,PINB6);
	set_pin(PORTB,PINB5);
	set_pin(PORTB,PINB4);
	
	modes wlcm,menu,cnfrm;
	
	wlcm.mode_name = "Welcome!";
	wlcm.mode_status = valid;
	
	menu.mode_name = "Menu";
	menu.mode_status = invalid;
	
	cnfrm.mode_name = "Confirm order?";
	cnfrm.mode_status = invalid;
	
	__init_lcd_();
	int selection = -1;
	flag confirmation=invalid;
	previtem=item;
    while (1)  
    {
		//--main framework for the vending machine--
		if(wlcm.mode_status == valid){
			lcd_FloatingPrint("Welcome!        A project by Yashesvi(happikin)                ");
			lcd_cmd(clearLCD);
			wlcm.mode_status = invalid;
			menu.mode_status = valid;
		}
		else if(menu.mode_status == valid) {
			lcd_cmd(clearLCD);
			lcd_curPos(0,0);
			lcd_print("make a selection");
			confirmation = invalid;
			selection = -1;
			_delay_ms(3000);
			selection = menu_nav();
			lcd_cmd(clearLCD);
			//if menu selection is done then 
			menu.mode_status = invalid;
			cnfrm.mode_status = valid;
		}
		else if(cnfrm.mode_status == valid) {
			lcd_cmd(clearLCD);
			lcd_NumPrint(selection);
			_delay_ms(1500);
			lcd_cmd(clearLCD);
			lcd_curPos(0,0);
			lcd_print("TO CONFIRM ORDER");
			lcd_curPos(1,0);
			lcd_print("PRESS OK/CANCEL");
			uint8_t choice = 0;
			while(!choice) {
				if(_switch_ok_) {
					confirmation = valid;
					choice = 1;
				}
				else if(_switch_cancel_) {
					confirmation = invalid;
					choice = 1;
				}
			}
			
			if(confirmation == valid) {
				lcd_cmd(clearLCD);
				lcd_curPos(0,0);
				lcd_print("ORDER CONFIRMED!");
				_delay_ms(2000);
			} else if(confirmation == invalid) {
				lcd_cmd(clearLCD);
				lcd_curPos(0,0);
				lcd_print("ORDER CANCELLED!");
				_delay_ms(2000);
			}
			//if confirmed the selection then
			//display thank you!
			// if declined then
			cnfrm.mode_status = invalid;
			menu.mode_status = valid;
		}		
		//- - - - - - - - - - - - - - - - - - - - -
		
    }
}
void lcd_FloatingPrint(char* txt) {
	char dispArr[16];
	uint8_t mainIndex=0;
	char* dispText;

	while(mainIndex<47) {
		dispText = txt;
			for(uint8_t i=0;i<16;i++) {
				if(dispText){dispArr[i] = *dispText++;}
				else{dispArr[i]=' ';}
			}
			lcd_print(dispArr);
			if(mainIndex!=0) {
				_delay_ms(250);	
			}
			else {
				_delay_ms(1000);
			}
			lcd_curPos(1,0);
			mainIndex++;
			txt++;
	}
}
int menu_nav() {
	int8_t choice = -1,navIndex=0;
	
	while(choice == -1) {
		if(_switch_up_){navIndex++;while(_switch_up_);}
		else if(_switch_down_) {navIndex--;while(_switch_down_);}
		if(navIndex>6){navIndex=0;}
		if(navIndex<0){navIndex=6;}
		lcd_curPos(1,0);
		lcd_print(coffee_types[navIndex].coffee_name);		
		while(!_switch_up_ & !_switch_down_ & !_switch_ok_);
		if(_switch_ok_){choice=navIndex;}
	}
	return choice;
}