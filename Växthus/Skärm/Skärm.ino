

#include <U8glib.h>
#include <Wire.h>

void setup()
{
    oled.setFont(u8g_font_helvB10);
    Wire.begin(); 
}
void loop()
{
    updateOled(String(hour) + ":" + String(minute) + ":" + String(second), String(temp));

}    
void updateOled(String text, String text2)
{
    oled.firstPage();
    do
    {
        oled.drawStr(5, 15, text.c_str());
        oled.drawStr(5, 30, text2.c_str());
    } while (oled.nextPage());
}