#include <io.h>
#include <alcd.h>
#include <delay.h>
#include <stdlib.h>
#include <stdio.h>
unsigned int gia_tri_adc;
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR)) // chú ý ADLAR=0 dùng cho 10bit và ADLAR=1 dùng cho 8bit.

char buffer[32];
void updateLCD(int c) {
	itoa(c, buffer);
	lcd_clear();
    lcd_puts(buffer);
}

unsigned int read_adc(unsigned char adc_input) {
    ADMUX=adc_input | ADC_VREF_TYPE;  // Chọn kênh ADC và điện áp so sánh, or bit 
	//	A	B	A OR B
	//	0	0	0
	//	0	1	1
	//	1	0	1
	//	1	1	1
    delay_us(10);
    ADCSRA|=(1<<ADSC); // cho phép chuyển đổi ADC, khi chuyển đổi xong nó tự về 0, muốn chuyển đổi tiếp ta lại phải set là 1
    while ((ADCSRA & (1<<ADIF))==0); // Trong khi cờ ngắt vẫn là 0 thì vẫn chuyển đổi adc
    ADCSRA|=(1<<ADIF); // Khi quá trình chuyển đổi hoàn tất thì cờ ngắt là 1
    return ADCW; //Giá trị ADC 10bit nếu muốn 8 bit thì return ADCH;
}
void main(void) {
    ADMUX=ADC_VREF_TYPE; // Đặt áp tham chiếu ban đầu
    ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADFR) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // khởi tạo  thanh ghi điểu khiển ADC ban đầu
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
