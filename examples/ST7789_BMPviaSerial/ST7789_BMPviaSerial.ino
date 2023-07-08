// Photo slideshow via serial port
// ST7789 & RRE library example
// (c) 2019 Pawel A. Hernik
// YT video: https://youtu.be/vQY5ILjSZBc

#include <Adafruit_GFX.h>
#include <Arduino_ST7789_Fast.h>

#define SCK   24
#define SDA   23

Arduino_ST7789 lcd = Arduino_ST7789(SCK, SDA);

void setup() 
{
  Serial.begin(115200);
  lcd.init();
  lcd.fillScreen(BLACK);
  lcd.drawRect(0,0,240,240,RED);
  lcd.setTextColor(WHITE);
  lcd.setTextSize(2);
  lcd.setCursor(24,110);
  lcd.println("WAITING FOR DATA");
  lcd.setTextColor(BLACK,WHITE);
}

int cnt=0;
int i=0,j=239;
uint8_t r,g,b,c;
int header=54;
unsigned long ms;
char buf[30];

void loop()
{
  while(Serial.available())  {
    c = Serial.read();
    if(header>0) { 
      header--; 
      if(header==0) ms=millis();
      continue; 
    }
    if(cnt==0)
      b = c;
    else if(cnt==1)
      g = c;
    else if(cnt==2) {
      r = c;
      cnt=-1;
      lcd.drawPixel(i,j,RGBto565(r,g,b));
      i++;
      if(i>=240) {
        i=0; j--;
        if(j<0) {
          j=239; 
          header=54; 
          snprintf(buf,30," Time: %d s ",(millis()-ms)/1000);
          lcd.setCursor(50,200);
          lcd.println(buf);
        }
      }
    }
    cnt++;
  }
}

