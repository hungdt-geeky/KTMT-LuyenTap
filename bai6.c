#include <io.h>
#include <alcd.h>
#include <delay.h>
#include <stdlib.h>
#include <stdio.h>
unsigned int gia_tri_adc;
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))

char buffer[32];
void updateLCD(int c) {
	itoa(c, buffer);
	lcd_clear();
    lcd_puts(buffer);
}

unsigned int read_adc(unsigned char adc_input) {
    ADMUX=adc_input | ADC_VREF_TYPE;
    delay_us(10);
    ADCSRA|=(1<<ADSC);
    while ((ADCSRA & (1<<ADIF))==0);
    ADCSRA|=(1<<ADIF);
    return ADCW;
}
void main(void) {
    ADMUX=ADC_VREF_TYPE;
    ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADFR) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
    SFIOR=(0<<ACME);
    DDRD =0x90;
    PORTD.4 = 0;
    PORTD.7 = 1;
    lcd_init(16); // lcd_int(8);
    lcd_clear();  // Xoa man hinh
    lcd_gotoxy(0,0);  // dua con tro ra vi tri xy
    
    while (1) {   
        gia_tri_adc = read_adc(0);
        delay_ms(250);
        updateLCD(gia_tri_adc);
        if(gia_tri_adc <= 600){
            PORTD.4 = 1;
        } else {
            PORTD.4=0;
        }
    }
}
