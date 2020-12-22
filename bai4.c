#include <io.h>
#include <alcd.h>
#include <stdlib.h>
#include <delay.h>
#define BT1 PINB.2
#define BT2 PINB.3
int mode = 0;
int count = 0;
char buffer[32];
void updateLCD(int c) {
    itoa(c, buffer);
    lcd_clear();
    lcd_puts(buffer);
}
void main(void) {
    DDRB = 0x00;
    PORTB = 0x0c;
    DDRD = 0xc0; // 1100 0000
    PORTD.7 = 1;
    lcd_init(16);
    updateLCD(0);
    while(1) {
        if (BT1 == 0) {
            delay_ms(250);
            if (mode == 2) {
                if (count > 0) {
                    delay_ms(250);
                    count = count - 1;
                    updateLCD(count);
                }
                mode = 0;
            } else {
                mode = 1;
            }
        }
        else if (BT2 == 0) {
            delay_ms(250);
            if (mode == 1) {
                delay_ms(250);
                count = count + 1;
                updateLCD(count);
                mode = 0;
            } else {
                mode = 2;
            }
        }
        if (count > 0) {
            PORTD.6 = 1;
        } else {
            PORTD.6 = 0;
        }
    }
}
