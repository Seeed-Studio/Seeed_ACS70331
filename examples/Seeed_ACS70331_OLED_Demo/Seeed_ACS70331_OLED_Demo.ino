/*
    Seeed_ACS70331_OLED_Demo.ino
    Driver for 2.5A DC Current Sensor (ACS70331)

    Copyright (c) 2018 Seeed Technology Co., Ltd.
    Website    : www.seeed.cc
    Author     : Jenkin
    Create Time: August 2018
    Change Log :

    The MIT License (MIT)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/


#include <Wire.h>
#include <SeeedOLED.h>

#ifdef SEEED_XIAO_M0
    #define RefVal 5.0
    #define SERIAL Serial
#elif defined(ARDUINO_SAMD_VARIANT_COMPLIANCE)
    #define RefVal 3.3
    #define SERIAL SerialUSB
#else
    #define RefVal 5.0
    #define SERIAL Serial
#endif
//An OLED Display is required here
//use pin A0
#define Pin A0

// Take the average of 10 times

const int averageValue = 10;

int sensorValue = 0;

float sensitivity = 1000.0 / 800.0; //1000mA per 800mV

/******************************************************************************
 ***************************    Notice   **************************************
 ******************************************************************************
     Output voltage with no current: 250mV , but there are errors because of
    the different boards.When we use UNO/Seeeduino v4, the approximate value is
    244mV; When we use the M0 series, the approximate value is 265mV;If you use
    other boards, follow these steps.
    1. The value of the sensorValue is read when there is no current load.
    2. Print out the initial voltage and assign it to the Vref.
 ******************************************************************************/

//float Vref = 244;
float Vref = 265;  //Firstly,change this!!!

void setup() {

    SERIAL.begin(9600);

    Wire.begin();
    SeeedOled.init();  //initialze SEEED OLED display

    SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
    SeeedOled.setNormalDisplay();      //Set display to normal mode (i.e non-inverse mode)
    SeeedOled.setPageMode();           //Set addressing mode to Page Mode
    SeeedOled.setTextXY(0, 0);         //Set the cursor to Xth Page, Yth Column
    SeeedOled.putString("Hello");

}

void loop() {
    // Read the value 10 times:
    for (int i = 0; i < averageValue; i++) {
        sensorValue += analogRead(Pin);

        // wait 2 milliseconds before the next loop
        delay(2);

    }

    sensorValue = sensorValue / averageValue;


    // The on-board ADC is 10-bits
    // Different power supply will lead to different reference sources
    // example: 2^10 = 1024 -> 5V / 1024 ~= 4.88mV
    //          unitValue= 5.0 / 1024.0*1000 ;
    float unitValue = RefVal / 1024.0 * 1000 ;
    float voltage = unitValue * sensorValue;

    //You need to read the value when there is no load and uncomment it
    SeeedOled.clearDisplay();

    ////When no load,Vref=initialValue
    SERIAL.print("initialValue: ");
    SERIAL.print(voltage);
    SERIAL.println("mV");
    SeeedOled.putNumber(voltage);    //initialValue
    SeeedOled.putString("mV ");
    SeeedOled.putNumber(sensorValue);

    // Calculate the corresponding current
    float current = (voltage - Vref) * sensitivity;

    // Print display voltage (mV)
    // This voltage is the pin voltage corresponding to the current
    /*  voltage = unitValue * sensorValue-Vref;
        SERIAL.print(voltage);
        SERIAL.println("mV");
        SeeedOled.setTextXY(1,0);
        SeeedOled.putString("voltage: ");
        SeeedOled.putNumber(voltage);
        SeeedOled.putString("mV");*/

    // Print display current (mA)
    SERIAL.print(current);
    SERIAL.println("mA");
    SeeedOled.setTextXY(2, 0);
    SeeedOled.putString("Current: ");
    SeeedOled.putNumber(current);
    SeeedOled.putString("mA");

    SERIAL.print("\n");

    // Reset the sensorValue for the next reading
    sensorValue = 0;
    // Read it once per second
    delay(1000);
}
