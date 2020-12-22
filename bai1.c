/*
 * bai1.c: Blinking Leg, 
 *
 * Created: 12/21/2020 1:03:38 PM
 * Author: LongChu
 */

#include <io.h> 
#include <delay.h>
#define bt1 PINB.2
#define bt2 PINB.3
#define bt3 PINB.0

unsigned char x=0;
int dem;
int sangmai = 0;

interrupt [TIM0_OVF] void timer0_ovf_isr(void) {
    // Reinitialize Timer 0 value
    TCNT0=0x06;
    if (x == 1) {
        dem = dem + 1;
         if(dem == 1000 && sangmai == 2) {
            x = 2;
            PORTD.6 = 1;
        }
        if(dem == 1000) {
            PORTD.6 = 1; 
        }              
        if (dem == 2000) {
            PORTD.6 = 0;
            sangmai = sangmai + 1; 
            dem= 0;
        }
    }
}

void main(void) {
    DDRB = 0x00; // pull up, khai bao cac nut bam la noi vao 
    PORTB = 0x0D; // vi tri: 023 -> 0000 1101
    
    DDRD = 0x10; // 0010 0000
    PORTD.6 = 0; // den toi
    
    ASSR=0<<AS0;
    TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (1<<CS01) | (1<<CS00);
    TCNT0=0x06;

    OCR0=0x00;
    TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);
    ETIMSK=(0<<TICIE3) | (0<<OCIE3A) | (0<<OCIE3B) | (0<<TOIE3) | (0<<OCIE3C) | (0<<OCIE1C);
    #asm("sei")

    
    while (1) {
            if(bt1 == 0) {
                delay_ms(250);
                x = 0;
                sangmai = 0;
                PORTD.6 = 1; 
            }
            if(bt2 == 0) {
                delay_ms(250);
                x = 0;
                sangmai = 0;
                PORTD.6 = 0; 
            }
            if(bt3 == 0) {
                delay_ms(250);
                x = 1;
                sangmai = 0;
            }    
    }
}
