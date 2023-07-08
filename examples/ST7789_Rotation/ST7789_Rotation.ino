// ST7789 library example
// (c) 2019-20 Pawel A. Hernik

#include <Adafruit_GFX.h>
#include <Arduino_ST7789_Fast.h>

#define SCK   24
#define SDA   23

Arduino_ST7789 lcd = Arduino_ST7789(SCK, SDA);

void setup() 
{
  Serial.begin(9600);
  lcd.init();
}

void loop(void) 
{
  for(uint8_t rot = 0; rot < 4; rot++) {
    testText(rot);
    delay(2000);
  }
}

unsigned long testText(int rot)
{
  lcd.setRotation(rot);
  lcd.fillScreen(BLACK);
  lcd.setCursor(0, 0);
  lcd.setTextColor(BLUE);
  lcd.setTextSize(1);
  lcd.println("Hello World!");
  lcd.setTextColor(WHITE);
  lcd.print("Rotation = ");
  lcd.println(rot);
  lcd.setTextColor(YELLOW);
  lcd.setTextSize(2);
  lcd.println(1234.56);
  lcd.setTextColor(RED);
  lcd.setTextSize(3);
  lcd.println(0xDEAD, HEX);
  lcd.println();
  lcd.setTextColor(GREEN);
  lcd.setTextSize(4);
  lcd.println("Hello");
}


