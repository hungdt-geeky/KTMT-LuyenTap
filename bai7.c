#include <io.h>
#include <alcd.h>
#include <delay.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define DHT_ER 0
#define DHT_OK 1

#define BL PORTD.7
#define DHT_DATA_IN PINB.7
#define DHT_DATA_OUT PORTB.7
#define DHT_DDR_DATA DDRB.7

char data[16];         
unsigned char dht_nhiet_do,dht_do_am;

unsigned char DHT_GETTenHumi(unsigned char *tem, unsigned char *humi){
    unsigned char buffer[5]={0,0,0,0};
    unsigned char ii,i,checksum;
    
    DHT_DDR_DATA = 1;
    DHT_DATA_OUT  = 1;
    delay_us(40);   
    DHT_DATA_OUT  = 0;
    delay_ms(30);
    DHT_DATA_OUT = 1;
    DHT_DDR_DATA = 0;
    delay_us(40);
    if(DHT_DATA_IN){
        return DHT_ER;
    }
    else while (!(DHT_DATA_IN));
    delay_us(40);
    if(!DHT_DATA_IN){
        return DHT_ER;
    }                 
    else while ((DHT_DATA_IN));
    //BAT DAU DOC DU LIEU
    for(i=0;i<5;i++)
    {
        for(ii=0;ii<8;ii++) //moi lan do 1 byte
        {
            while((!DHT_DATA_IN)); //DOI DATA LEN 1
            delay_us(30);
            if(DHT_DATA_IN)
            {
                buffer[i] = (1<<(7-ii)); //lay 7 bit du lieu gui ve
                while ((DHT_DATA_IN)); //doi data xuong 0
                
            }
        }
    }   
    //Tinh toan checksum
    checksum = buffer[0] + buffer[1] + buffer[2] + buffer[3];
    //kiem tra checksum
    if((checksum)!= buffer[4]){ //CKECKSUM LA BYTE 5
        return DHT_ER;
    }                                              
    //lay du lieu
    *tem = buffer[2];
    *humi = buffer[0];
    return   DHT_OK;
}

void main(void) {
    DDRD = 0x80;
    PORTD = 0x80;
    lcd_init(16);
    while (1)  {
        if(DHT_GETTenHumi(&dht_nhiet_do,&dht_do_am)){
            lcd_clear();
            lcd_gotoxy(0,0);
            sprintf(data, "do am &%u", (uint8_t)dht_do_am);
            lcd_puts(data);
            lcd_gotoxy(0,1);
            sprintf(data,"Nhiet do %u",(uint8_t)dht_nhiet_do);
            lcd_puts(data);
            delay_ms(300);   
        }
    }
}

