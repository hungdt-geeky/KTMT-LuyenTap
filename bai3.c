#include <io.h>
#include <alcd.h>
#include <delay.h>
#define BT1 PINB.2
#define BT2 PINB.3
#define BT3 PINB.0

unsigned i;
int k, j, m = 0;
unsigned char str1[12] = {' ', 'H', 'e', 'l', 'l', 'o', '-', 'w', 'o', 'r', 'l', 'd'};
unsigned char str_1[12] = {'H', 'e', 'l', 'l', 'o', '-', 'w', 'o', 'r', 'l', 'd', ' '};
unsigned char str2[11];

void main(void) {
    DDRB = 0x00;
    PORTB = 0x0D;
    DDRD = 0x80;
    PORTD.7 = 1;
    lcd_init(16);
    while (1) {
        if(BT1 == 0) {
            delay_ms(250);
            for(i = 11; i > 0; i--) {
                for(j = 0; j <= (15-m); j++) {
                    lcd_clear();
                    for(k = m; k > 0; k--) {
                        lcd_gotoxy((16-k), 0);
                        lcd_putchar(str2[k-1]);
                    }                    
                    lcd_gotoxy(j, 0);
                    lcd_putchar(str1[i]);
                    delay_ms(100);
                }
                str2[m++] = str1[i];
            }
            m = 0;
            delay_ms(200);
        }
        
        if(BT2 == 0) {
            delay_ms(250);
            for(i = 0; i < 11; i++) {
                for(j = 15; j >= m; j--) {
                    lcd_clear();
                    for(k = 0; k < m; k++) {
                        lcd_gotoxy(k, 0);
                        lcd_putchar(str2[k]);
                    }                    
                    lcd_gotoxy(j, 0);
                    lcd_putchar(str_1[i]);
                    delay_ms(100);
                }
                str2[m++] = str_1[i];
            }
            m = 0;
            delay_ms(200);
        }
        
        if(BT3 == 0) {
            delay_ms(250);
            lcd_clear();
        }
    }
}
