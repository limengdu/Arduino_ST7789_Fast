#include "bitmap.h"
#include <Adafruit_GFX.h>
#include <Arduino_ST7789_Fast.h>

#define SCK   24
#define SDA   23

Arduino_ST7789 lcd = Arduino_ST7789(SCK, SDA);

uint16_t colorBar[50];

void setup(void)
{
    Serial.begin(9600);
    lcd.init();
    lcd.fillScreen(BLACK);

    int i,j;
    for(j=0;j<7;j++)
    for(i=0;i<7;i++)
    lcd.drawImageF(i*34,j*34,32,32,mario);
    delay(4000);

    for(i=0;i<25;i++) {
        colorBar[i]    = RGBto565(i*256/25,0,i*256/25);
        colorBar[i+25] = RGBto565((24-i)*255/25,0,(24-i)*255/25);
    }
    for(i=0;i<240;i++) {
        lcd.drawImage(i,0,1,50,colorBar);
        lcd.drawImage(i,240-50,1,50,colorBar);
    }
    for(i=50;i<240-50;i++) {
        lcd.drawImage(0,i,50,1,colorBar);
        lcd.drawImage(240-50,i,50,1,colorBar);
    }
    delay(4000);
}

void loop()
{
    lcd.drawImageF(random(0,240-32),random(0,240-32),32,32,mario);
}

