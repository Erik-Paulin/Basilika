// C++ code
//

#include <U8glib.h>
#include <Wire.h>

int moisture = 0;

U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_NO_ACK);


void setup()
{
  pinMode(A0, OUTPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
  oled.setFont(u8g_font_helvB10);
  Wire.begin();

}

void loop()
{
  updateGndSen()
  updateOled(String(moisture));
}
   
void updateOled(String text)
{
    oled.firstPage();
    do
    {
        oled.drawStr(5, 15, text.c_str());
    } while (oled.nextPage());
}

void updateGndSen 
{
  // Apply power to the soil moisture sensor
  digitalWrite(A0, HIGH);
  moisture = analogRead(A1);
  // Turn off the sensor to reduce metal corrosion over time
  digitalWrite(A0, LOW);
  Serial.println(moisture);
}