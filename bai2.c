#include <io.h>
#include <alcd.h>
#include <delay.h>
#define bt1 PINB.2
#define bt2 PINB.3
#define bt3 PINB.0

int mode = 0;
flash char *word = "hello-world";
void main(void) {
    DDRB = 0x00; // pull up
    PORTB = 0x0D; // 0000 1101
  
    DDRD = 0x80;
    PORTD.7 = 1;
    // PORTD = 0x2c; // 0011 1100
    lcd_init(16); // lcd_int(8);
    lcd_clear();  // Xoa man hinh
    lcd_gotoxy(0,0);  // dua con tro ra vi tri xy
    lcd_putsf(word);
    while (1) {
        if(bt1 == 0 || (mode == 1 && bt2 != 0  && bt3 != 0)) { //bt1
            delay_ms(200); 
            mode = 1;
            _lcd_write_data(0x1C); // 00011100
            //lcd_putsf("bt1");
        } else if(bt2 == 0 || (mode == 2 && bt1 != 0  && bt3 != 0 )) { // bt2
            delay_ms(200);
            mode = 2;
            _lcd_write_data(0x18); // 00011000
            //lcd_putsf("bt2");
        } else if(bt3 == 0) { // bt3
            mode = 3;
            lcd_clear();
        }
    }
}
