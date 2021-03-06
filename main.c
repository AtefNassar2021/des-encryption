/*
 * File:   main.c
 * Author: Atef
 *
 * Created on April 20, 2022, 2:10 PM
 */


#include <avr/io.h>
#include "config.h"

static int i = 0;
ubyte message1[15];

ISR(USART_RXC_vect) {
   
    message1[i] = uart_receive();

    LCD_write_4bit(uart_receive());
    i++;
}

int main(int argc, const char * argv[]) {

    init_uart(9600, 1, 1);
    init_LCD_4bit();
   
    int len;
    char e[] = "welcome";
    char m[] = "MASSAGE_IS";

    LCD_write_str_4bit(e);
    _delay_ms(1000);
    LCD_clear_4bit();
    LCD_write_str_4bit(m);
    LCD_goto_4bit(1, 0);
    
    sei();
    while (1) {

        if (i == 15) {
            const key_t keys[] = {
                {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1},
                {0x0E, 0x32, 0x92, 0x32, 0xEA, 0x6D, 0x0D, 0x73},
                {0x0E, 0x32, 0x92, 0x32, 0xEA, 0x6D, 0x0D, 0x73}
            };

            len = sizeof (message1) / sizeof (ubyte);
            driver(keys[0], message1, len);

        }
    }

}







