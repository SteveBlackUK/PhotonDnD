/*
 * Project PhotonDnD
 * Description:
 * Author:
 * Date:
 */

// EXAMPLE APP - use button to toggle LED light on and off

// global variables
int red = D4;  // red led on local board so I know what should be showing remotely
int green = D5;
int button = D2;  // red/green toggle button
int greenButton = D6; // green button
int switchPin = D0;  // switch used for on/off
int switchRed = D1;
String ledStatus = "red";
bool switchStatusChanged = true;  // needed to only run on/off loop on change event 
int switchStatus;
int currentSwitchVal;

// setup() runs once, when the device is first turned on.
void setup() {
    //for LEDs and Button
    pinMode(button, INPUT_PULLUP);
    pinMode(greenButton, INPUT_PULLUP);
    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);

    // set starting status
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    
    //for switch
    pinMode(switchPin, INPUT);
    pinMode(switchRed, OUTPUT);

    //publish red starting colour at launch
    Particle.publish("LedColor","red", PRIVATE); 
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    // check button
    int redButtonState = digitalRead(button);

    // LOW means button is being pushed

    //red path
    if(redButtonState == LOW) {
        ledStatus = "red";
        Particle.publish("LedColor","red", PRIVATE); //publish the new color so the listener can act
        digitalWrite(green, LOW);
        digitalWrite(red, HIGH);
    }

    // Wait 0.5 seconds before checking button again.  If you hold button, you get toggle every 0.5 seconds.

    delay(500);


    int greenButtonState = digitalRead(greenButton);
   
//green button path
    if(greenButtonState == LOW) {
        //publish the new color so the listener can act
        Particle.publish("LedColor","green", PRIVATE); 
        ledStatus = "green"; 
        digitalWrite(green, HIGH); 
        digitalWrite(red, LOW);
    }


    //Switch section for master on/off switch that overrides red/green toggle
    currentSwitchVal = digitalRead(switchPin);
    
    //because this is in loop() and we don't want to toggle on/off nonstop, we only want to toggle on/off when the switch changes position.
    if (currentSwitchVal != switchStatus) {
        switchStatusChanged = true;
    }
    
    if(switchStatusChanged == true) {
        switchStatus = currentSwitchVal;
        switchStatusChanged = false;
        
        if (currentSwitchVal == HIGH)
        {
            switchStatus = HIGH; 
            digitalWrite(switchRed, LOW);
            //publish power on event to listening devices
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