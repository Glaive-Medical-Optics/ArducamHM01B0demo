/* 
 *    This demo program shows how to stream bytes from an Arducam HM01B0 camera over the Serial line.
 *    Author: Glaive Software Group
 *    Revised: 6/14/2024.
 *    Based on the GIGA R1 Camera Guide tutorial at
 *    https://docs.arduino.cc/tutorials/giga-r1-wifi/giga-camera/.
 *    
 *    To run this sketch, you will need to specify that you are using the Arduino Giga R1 board
 *    in the IDE's board manager (under Arduino Mbed OS Giga boards).
 *    You also need to install the arducam_dvp library in the library manager.
 *    Don't forget to set the correct serial port that you want to use.
 *  
 *    You will also need the Processing app on your computer, as well as the
 *    CameraRawBytesVisualizer sketch which can be found in the GIGA R1 Camera Guide.
 *    The baud rate in that sketch must match the BAUD_RATE in this sketch.
 *    The serial port name must also be set correctly, for example "/dev/cu.usbmodem14601".
 *    
 *    This sketch was tested with version 1.0.0 of the arducam_dvr library.
 *    This sketch was test with an Arducam HM01B0 QVGA monochrome camera, model B0460.
 *    The camera must be plugged into the J6 connector on the Arduino Giga R1 board.
 *    
 *    If the camera fails to initialize, the red LED on the Arduino will begin blinking rapidly.
 *    
 *    When the camera is ready to send a picture, it will blink the blue LED 4 times.
 *    You should then start up the CameraRawBytesVisualizer on your computer
 *    to display the output from the camera in a window.
 *    
 *    Your computer and the Arduino board should be connected via a USB cable.
 *    
 *    This program is Free Software and has ABSOLUTELY NO WARRANTY.
 */

#include "arducam_dvp.h"

#include "Himax_HM01B0/himax.h"
HM01B0 himax;
Camera cam(himax);

FrameBuffer fb;

void blinkLED(uint32_t count = 0xFFFFFFFF,uint32_t t_delay = 500);
void blinkRed(uint32_t count = 0xFFFFFFFF,uint32_t t_delay = 500);
void blinkBlue(uint32_t count = 0xFFFFFFFF,uint32_t t_delay = 500);

enum
{
  WALKING_ONES  = true,
  COLOR_BAR     = false
};

/*
 *    Set USE_TEST_PATTERN to true if you want to display a test pattern.
 *    Then set TEST_PATTERN_MODE to either WALKING_ONES or COLOR_BAR.
 *    Set USE_TEST_PATTERN to false if you want to display what the camera sees.
 */

#define IMAGE_MODE        CAMERA_GRAYSCALE
#define USE_TEST_PATTERN  true
#define TEST_PATTERN_MODE COLOR_BAR     // specify WALKING_ONES or COLOR_BAR
#define BAUD_RATE         921600

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    // Init the camera for QVGA (which means a resolution of 320x320 pixels) running at 30FPS.
    if (!cam.begin(CAMERA_R320x320, IMAGE_MODE, 30))
    {
        blinkRed();
    }
    blinkBlue(4);

    #if USE_TEST_PATTERN
    himax.setTestPattern(true,TEST_PATTERN_MODE);
    #endif

    Serial.begin(BAUD_RATE);
}

void loop()
{
    if(Serial.read() != 0x01)
    {
        return;
    }
    // Grab frame and write to serial
    if (cam.grabFrame(fb, 3000) == 0)
    {
        Serial.write(fb.getBuffer(), cam.frameSize());
    }
    else
    {
        blinkLED(20,100);
        delay(1000);
    }
}
