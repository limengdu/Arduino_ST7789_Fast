// ST7789 library example
// (c) 2019 Pawel A. Hernik

#include <Adafruit_GFX.h>
#include <Arduino_ST7789_Fast.h>
#include <SPI.h>
#include "mcp_can.h"

#define SCK   24
#define SDA   23


Arduino_ST7789 lcd = Arduino_ST7789(SCK, SDA);

#define SPI_CS_PIN  9 

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin


void setup(void)
{

    while (CAN_OK != CAN.begin(CAN_500KBPS))    // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS FAIL!");
        delay(100);
    }
    Serial.println("CAN BUS OK!");

    lcd.init();
    lcd.setRotation(1);
    lcd.fillScreen(BLACK);

    lcd.setCursor(0, 0);
    lcd.setTextColor(WHITE,BLACK);
    lcd.setTextSize(2);

    lcd.println("CAN CARD");
    delay(1000);
}

void loop()
{
    unsigned char len = 0;
    unsigned char buf[8];

    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        unsigned long canId = CAN.getCanId();
        
        Serial.println("-----------------------------");
        Serial.print("Get data from ID: ");
        Serial.println(canId, HEX);

        for(int i = 0; i<len; i++)    // print the data
        {
            Serial.print(buf[i], HEX);
            Serial.print("\t");
        }
        Serial.println();

        lcd.setCursor(0, 0);

        lcd.println("get can frame");
        lcd.print("id: 0x");
        lcd.println(canId, HEX);
        lcd.print("len = ");
        lcd.println(len);

        for(int i=0; i<len; i++)
        {
            lcd.print(buf[i], HEX);
            lcd.print(" ");
        }

    }
}

