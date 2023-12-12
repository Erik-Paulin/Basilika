

#include <U8glib.h>
#include <Wire.h>
#include <Servo.h>

Servo myServo;

#include <DHT.h>

#define DHTPIN 4

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

#include <RtcDS3231.h>

RtcDS3231<TwoWire> Rtc(Wire);

int hot = 0;

int dry = 0;

int hour;
int minute;
int second;
int day;

float temp;

float t = dht.readTemperature();
float h = dht.readHumidity();

int moisture = 0;

U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_NO_ACK);

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    myServo.attach(9);
    oled.setFont(u8g_font_helvB10);
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    Rtc.SetDateTime(compiled);
    pinMode(A0, OUTPUT);
    pinMode(A1, INPUT);
}

void loop()
{
    updateOled(String(hour) + ":" + String(minute) + ":" + String(second), String(moisture), String(dht.readTemperature()), String(dht.readHumidity()));
    updateRtc();
    if (minute % 30 == 0)
    {
        updateGndSen();
        if (moisture < 50)
        {
            dry = 1;
        }
        else
        {
            dry = 0;
        }
    }
    updateDHT();
    //if (second % 2 == 0)
    {
        
        if (dht.readTemperature() > 25)
        {
            hot = 1;
        }
        else
        {
            hot = 0;
        }
    }
    updateServo(hot);
    pumpWater(dry);
}

void updateOled(String text, String text2, String text3, String text4)
{
    oled.firstPage();
    do
    {
        oled.drawStr(5, 20, text.c_str());
        oled.drawStr(5, 40, text2.c_str());
        oled.drawStr(70, 20, text3.c_str());
        oled.drawStr(70, 40, text4.c_str());
    } while (oled.nextPage());
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

void updateGndSen()
{
    // Apply power to the soil moisture sensor
    digitalWrite(A0, HIGH);
    moisture = analogRead(A1);
    // Turn off the sensor to reduce metal corrosion over time
    digitalWrite(A0, LOW);
    Serial.println(moisture);
}

void updateDHT()
{
    // Wait a few seconds between measurements.
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }

    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.println(F("%"));
    Serial.print(F("Temperature: "));
    Serial.println(t);
}

void updateServo(int hot)
{
    myServo.write(map(hot, 0, 1, 0, 180));
}

void pumpWater(int dry)
{
    if (dry > 0)
    {
        digitalWrite(A3, HIGH);
    }
    else
    {
        digitalWrite(A3, LOW);
    }
}