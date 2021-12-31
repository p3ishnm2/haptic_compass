#include <Wire.h>
#include <LSM303.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 10
#define NUMPIXELS 8

LSM303 compass;
float head;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, A0, NEO_GRB + NEO_KHZ800);

void setup()
{
    //D2 is only LED.
    for (int i = 2; i <= 9; i++)
    {
        pinMode(i, OUTPUT);
    }
    Serial.begin(9600);
    Wire.begin();
    compass.init();
    compass.enableDefault();
    compass.m_min = (LSM303::vector<int16_t>){-32767, -32767, -32767};
    compass.m_max = (LSM303::vector<int16_t>){+32767, +32767, +32767};

    pixels.begin();
    for (int h = 0; h < 2; h++)
    {
        for (int i = 0; i < NUMPIXELS; i++)
        {
            pixels.setPixelColor(i, pixels.Color(150, 50, 10)); // Moderately bright green color.
            pixels.show();                                      // This sends the updated pixel color to the hardware.
            delay(100);                                         // Delay for a period of time (in milliseconds).
        }
        for (int i = 0; i < NUMPIXELS; i++)
        {
            pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Moderately bright green color.
            pixels.show();                                  // This sends the updated pixel color to the hardware.
            delay(100);                                     // Delay for a period of time (in milliseconds).
        }
    }
}

void loop()
{
    compass.read();
    head = compass.heading() + 90;
    if (head > 360)
    {
        head = head - 360;
    }

    Serial.println(head);
    //delay(100);
    //Wiringではn<x<mみたいな書き方ができない
    //nanoのA6, A7ピンはアナログ専用
    if (337.5 < head | head < 22.5)
    {
        //vibe(2, 0);    //LED
        north(0);
        Serial.println("2"); //debug
    }
    else if (head > 22.5 && head < 67.5)
    {
        vibe(2, 7); //void vibe(int pin, int Lnum)
    }
    else if (head > 67.5 && head < 112.5)
    {
        vibe(3, 6);
    }
    else if (head > 112.5 && head < 157.5)
    {
        vibe(4, 5);
    }
    else if (head > 157.5 && head < 202.5)
    {
        vibe(6, 4);
    }
    else if (head > 202.5 && head < 247.5)
    {
        vibe(7, 3);
    }
    else if (head > 247.5 && head < 292.5)
    {
        vibe(8, 2);
    }
    else if (head > 292.5 && head < 337.5)
    {
        vibe(9, 1);
    }
    else
    {
        for (int i = 0; i < NUMPIXELS; i++)
        {
            pixels.setPixelColor(i, pixels.Color(150, 50, 10)); // Moderately bright green color.
            pixels.show();                                      // This sends the updated pixel color to the hardware.
            delay(100);                                         // Delay for a period of time (in milliseconds).
        }
        for (int i = 0; i < NUMPIXELS; i++)
        {
            pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Moderately bright green color.
            pixels.show();                                  // This sends the updated pixel color to the hardware.
            delay(100);                                     // Delay for a period of time (in milliseconds).
        }
    }
    pixels.clear();
    pixels.show();
}

void vibe(int pin, int Lnum)
{
    digitalWrite(pin, HIGH);
    for (int i = 0; i < NUMPIXELS; i++)
    {
        if (i != Lnum)
            pixels.setPixelColor(i, pixels.Color(6, 4, 2)); // Moderately bright green color.
        else
            pixels.setPixelColor(Lnum, pixels.Color(150, 50, 10)); // Moderately bright green color.
    }
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(200);
    digitalWrite(pin, LOW);
    delay(300);
//    digitalWrite(pin, LOW);
//    delay(50);
//    digitalWrite(pin, HIGH);
//    delay(150);
//    digitalWrite(pin, LOW);
//    delay(250);
}
void north(int Lnum)
{
    digitalWrite(4, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    for (int i = 0; i < NUMPIXELS; i++)
    {
        if (i != Lnum)
            pixels.setPixelColor(i, pixels.Color(6, 4, 2)); // Moderately bright green color.
        else
            pixels.setPixelColor(Lnum, pixels.Color(150, 50, 10)); // Moderately bright green color.
    }
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(100);
    digitalWrite(4, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
}
