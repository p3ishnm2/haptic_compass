#include <Wire.h>
#include <LSM303.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN            12
#define NUMPIXELS      12

LSM303 compass;
float head;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// もうPololu LSM303Dは廃盤なので他のセンサを探す
void setup() {
    Serial.begin(9600);
    Wire.begin();
    compass.init();
    compass.enableDefault();
    compass.m_min = (LSM303::vector<int16_t>){-32767, -32767, -32767};
    compass.m_max = (LSM303::vector<int16_t>){+32767, +32767, +32767};

    pixels.begin();

    for(int i=2;i<=10;i++){
        pinMode(i, OUTPUT);
    }
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);

    for(int h = 0; h < 2; h++){
        for(int i = 0; i < NUMPIXELS; i++){
            pixels.setPixelColor(i, pixels.Color(150, 50, 10)); // Moderately bright green color.
            pixels.show(); // This sends the updated pixel color to the hardware.
            delay(100); // Delay for a period of time (in milliseconds).
        }
        for(int i = 0; i < NUMPIXELS; i++){
            pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
            pixels.show(); // This sends the updated pixel color to the hardware.
            delay(100); // Delay for a period of time (in milliseconds).
        }
    }
}

void loop(){
    compass.read();
    head = compass.heading() + 90;
    if(head > 360){
        head = head - 360;
    }

    Serial.println(head);
    if (head > 350 | head <= 10){
        north();
        // for(int i = 0; i < NUMPIXELS; i++){
        //         pixels.setPixelColor(i, pixels.Color(150, 50, 10)); // Moderately bright green color.
        // }
        // pixels.show(); // This sends the updated pixel color to the hardware.
        // delay(150);
    }else if(head > 10 && head <= 30){
        vibe(10, 11);
    }else if(head > 30 && head <= 60){
        vibe(9, 10);
    }else if(head > 60 && head <= 90){
        vibe(A3, 9);
    }else if(head > 90 && head <= 120){
        vibe(A2, 8);
    }else if(head > 120 && head <= 150){
        vibe(A1, 7);
    }else if(head > 150 && head <= 170){
        vibe(A0, 6);
    }

    else if(head > 170 && head <= 190){
        // vibe(A0, 6);
        // vibe(7, 5);
        digitalWrite(A0, HIGH);
        digitalWrite(7, HIGH);
        pixels.setPixelColor(5, pixels.Color(150, 50, 10)); // Moderately bright green color.
        pixels.setPixelColor(6, pixels.Color(150, 50, 10)); // Moderately bright green color.
        pixels.show(); // This sends the updated pixel color to the hardware.
        delay(200);
        digitalWrite(A0, LOW);
        digitalWrite(7, LOW);
        delay(300);

    }

    else if(head > 190 && head <= 210){
        vibe(7, 5);
    }else if(head > 210 && head <= 240){
        vibe(6, 4);
    }else if(head > 240 && head <= 270){
        vibe(5, 3);
    }else if(head > 270 && head <= 300){
        vibe(4, 2);
    }else if(head > 300 && head <= 330){
        vibe(3, 1);
    }else{
        vibe(2, 0);
    }
    pixels.clear();
    pixels.show();

}
void vibe(int pin, int Lnum){
    digitalWrite(pin, HIGH);
    pixels.setPixelColor(Lnum, pixels.Color(150, 50, 10)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(200);
    digitalWrite(pin, LOW);
    delay(300);
}

void north(){
    pixels.setPixelColor(0, pixels.Color(150, 50, 10));
    pixels.setPixelColor(11, pixels.Color(150, 50, 10));
    pixels.show();
    digitalWrite(A0, HIGH);
    digitalWrite(7, HIGH);
    delay(200);
    digitalWrite(A0, LOW);
    digitalWrite(7, LOW);
}
