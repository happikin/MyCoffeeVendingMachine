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
typedef struct {
	char* coffee_name;
	uint8_t price;
} menu_items;

menu_items coffee_types[] = {
	{"cappuccino",50},
	{"espresso",27},
	{"black coffee",10},
	{"smoothie",45},
	{"americano",79},
	{"cafe cubano",101},
	{"frappuccino",156}
};
typedef enum {invalid,valid} flag;
typedef struct {
		char *mode_name;
		flag mode_status;
} modes;

volatile int item=0,previtem;
void showItem();
uint8_t sw_up = 0;
int main(void)
{	
	set_all(DDRA);
	set_all(DDRC);
	clr_all(DDRB);
	set_pin(PORTB,PINB7);
	set_pin(PORTB,PINB6);
	set_pin(PORTB,PINB5);
	
	modes wlcm,menu,cnfrm;
	
	wlcm.mode_name = "Welcome!";
	wlcm.mode_status = invalid;
	
	menu.mode_name = "Menu";
	menu.mode_status = invalid;
	
	cnfrm.mode_name = "Confirm order?";
	cnfrm.mode_status = invalid;
	
	__init_lcd_();
	
	previtem=item;
    while (1)  
    {
		if(_switch_up_) {
			sw_up  = 1;
		}
		else {
			sw_up = 0;
		}
		
		/*previtem = item;
		if(_switch_up_) {
			item++;
		}
		if(_switch_down_) {
			item--;
		}
		if(/* the button is pressed ) {
			showItem();
		}
		if(previtem == item) {
			lcd_curPos(1,0);
			lcd_print(coffee_types[item].coffee_name);
			_delay_ms(1000);
			lcd_NumPrint(coffee_types[item].price);
			_delay_ms(1000);
		}*/
    }
}