// DDR la thanh ghi chi huong du lieu, neu DDR = 1; du lieu la loi ra
// Neu thanh ghi DDR = 0 => du lieu la loi vao, thanh ghi nay tac dong duoc den tung bit
// Thanh ghi PORT la thanh ghi du lieu (cho ca loi ra va loi vao); Neu PORT = 1, du lieu duoc dua len VCC - nguon
// Neu PORT = 0 => ghi du lieu xuong GND (Ground)
#include <io.h>
#include <alcd.h>
#include <delay.h>
#include <stdio.h>
#include <stdlib.h>

#define servo_1 PORTC.7
#define BT1 PINB.2
#define BT2 PINB.3
int dem;
int vi_tri = 150;
int goc = 0;
char buffer[32];
void updateLCD(int c) {
	itoa(c, buffer);
	lcd_clear();
    lcd_puts(buffer);
}

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
  TCNT0=0xB0;
  dem++; // moi lan bien dem tang, thoi gian se troi di 0.01ms
  if (dem == 2000){
    dem = 0;
  }
  if (dem < vi_tri){
    servo_1 = 1;
  } else servo_1 = 0;
}

void main(void) {
  DDRC = 0x80; // servo là output nên DDR phai là 1
  DDRB = 0x00; // BT là input nên ph?i DDR phai là 0
  PORTB = 0x0C; // vì du lieu cua BT duoc dua lên vcc
  DDRD = 0x80;
  PORTD.7 = 1;
  lcd_init(16); // lcd_int(8);
  lcd_clear();  // Xoa man hinh
  lcd_gotoxy(0,0);  // dua con tro ra vi tri xy
  updateLCD(goc);
  
  ASSR=0<<AS0;
  TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (0<<CS01) | (1<<CS00);
  TCNT0=0xB0;
  OCR0=0x00;
  TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);
  ETIMSK=(0<<TICIE3) | (0<<OCIE3A) | (0<<OCIE3B) | (0<<TOIE3) | (0<<OCIE3C) | (0<<OCIE1C);
  #asm("sei")
  while (1) {
      if (BT1 == 0) {
        delay_ms(100);
        vi_tri += 10;
        goc += 18;
        updateLCD(goc);
        if (vi_tri == 200) {
          vi_tri = 150;
          goc = 0;
          updateLCD(goc);
        }
      }

      if (BT2 == 0) {
        delay_ms(100);
        vi_tri -= 10;
        goc -= 18;
        updateLCD(goc);
        if (vi_tri == 100) {
          vi_tri = 150;
          goc = 0;
          updateLCD(goc);
        }
      }
    }
}
