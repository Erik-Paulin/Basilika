
#include <Wire.h>
#include <RtcDS3231.h>

RtcDS3231<TwoWire> Rtc(Wire);

int hour;                        
int minute;                     
int second;                      
int day;                         

float temp; 

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    Rtc.SetDateTime(compiled);
}
void loop()
{
    updateRtc();
}

void updateRtc()
{
    RtcDateTime now = Rtc.GetDateTime();
    hour = now.Hour();
    minute = now.Minute();
    second = now.Second();
    Serial.println(String(hour) + ":" + String(minute) + ":" + String(second));
    RtcTemperature rtcTemp = Rtc.GetTemperature();
    temp = rtcTemp.AsFloatDegC();
}