/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/steve_black_spare/Dropbox/PhotonDnD/src/PhotonDnD.ino"
/*
 * Project PhotonDnD
 * Description:
 * Author:
 * Date:
 */



// EXAMPLE APP - use button to toggle LED light on and off

// global variables
void setup();
void loop();
#line 13 "/Users/steve_black_spare/Dropbox/PhotonDnD/src/PhotonDnD.ino"
int led = D7;
int red = D4;
int green = D5;
int button = D2;
int switchPin = D0;
int switchRed = D1;
String ledStatus = "off";
String switchStatusChanged = "true";
int switchStatus;
int currentSwitchVal;

// setup() runs once, when the device is first turned on.
void setup() {
    //for LETs and Button
    pinMode(button, INPUT_PULLUP);
    pinMode(led, OUTPUT);
    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);

    // turn off light at start to match ledStatus
    digitalWrite(led, LOW);
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    
    //for switch
    pinMode(switchPin, INPUT);
    pinMode(switchRed, OUTPUT);

    
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    // check button
    int buttonState = digitalRead(button);

    // LOW means button is being pushed
    if(buttonState == LOW) {

        // if light is currently off, switch to on
        if(ledStatus == "off") {
            // Particle.publish("LightOn", PRIVATE);
            Particle.publish("LedOn","on", PRIVATE);
            ledStatus = "on";
            digitalWrite(led, HIGH);
            digitalWrite(green, HIGH);
            digitalWrite(red, LOW);


        }
        // else light must be on, so switch to off
        else {
            ledStatus = "off";
            // Particle.publish("LightOff", PRIVATE);
            Particle.publish("LedOff","off", PRIVATE);
            digitalWrite(led, LOW);
            digitalWrite(green, LOW);
            digitalWrite(red, HIGH);
        }
    }

    // wait 0.5 seconds before checking button again
    delay(500);
    
   
    currentSwitchVal = digitalRead(switchPin);
       
    
    if (currentSwitchVal != switchStatus) {
        switchStatusChanged = "true";
    }
    
    if(switchStatusChanged == "true") {
        switchStatus = currentSwitchVal;
        switchStatusChanged = "false";
        
        if (currentSwitchVal == HIGH)
        {
            switchStatus = HIGH; 
            digitalWrite(switchRed, LOW);
            Particle.publish("MasterPower","MasterOn",PRIVATE);
        }
        else
        {
            switchStatus = LOW; 
            digitalWrite(switchRed, HIGH);
            Particle.publish("MasterPower","MasterOff",PRIVATE);
        }
    }
}