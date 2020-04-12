/*
 * Project PhotonDnD
 * Description:
 * Author:
 * Date:
 */

// global variables
int red = D1;       // red led 
int green = D5;     // green led
int button = D2;    // red button 
int greenButton = D6; // green button
int switchPin = D0;  // toggle switch used for on/off
// String ledStatus = "red";
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

    //set starting status with both lights on
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    
    //initiate switch
    pinMode(switchPin, INPUT_PULLUP);

    //publish blue starting colour at launch
    Particle.publish("LedColor","blue", PRIVATE); 
}

void loop() {
    int redButtonState = digitalRead(button);

//only change colours when master power is on
if(currentSwitchVal == HIGH) {
    if(redButtonState == LOW) {
        // ledStatus = "red";
        Particle.publish("LedColor","red", PRIVATE); //publish the new color so the listener can act
        digitalWrite(green, LOW);
        digitalWrite(red, HIGH);
    }
    // Wait 0.5 seconds before checking button again.  If you hold button, you get toggle every 0.5 seconds.

    delay(500);


    int greenButtonState = digitalRead(greenButton);
    if(greenButtonState == LOW) {
        //publish the new color so the listener can act
        Particle.publish("LedColor","green", PRIVATE); 
        // ledStatus = "green"; 
        digitalWrite(green, HIGH); 
        digitalWrite(red, LOW);
    }
}

    //Switch section for master on/off switch that overrides red/green toggle
    currentSwitchVal = digitalRead(switchPin);
    
    // //because this is in loop() and we don't want to toggle on/off nonstop, we only want to toggle on/off when the switch changes position.
    if (currentSwitchVal != switchStatus) {
        switchStatusChanged = true;
        Particle.publish("Changed to Switch Val of",String(currentSwitchVal),PRIVATE);
    }
    
    if(switchStatusChanged == true) {
        switchStatus = currentSwitchVal;
        switchStatusChanged = false;
        
        if (currentSwitchVal == HIGH)
        {
            // switchStatus = HIGH; 
            // digitalWrite(switchRed, LOW);
            //publish power on event to listening devices
            Particle.publish("MasterPower","MasterOn",PRIVATE);    
            delay(200);
            Particle.publish("LedColor","blue", PRIVATE); 
            digitalWrite(red, HIGH);
            digitalWrite(green, HIGH);
        }
        else
        {
            //turn off
            Particle.publish("MasterPower","MasterOff",PRIVATE);
            digitalWrite(red, LOW);
            digitalWrite(green, LOW);
        }
    }
}