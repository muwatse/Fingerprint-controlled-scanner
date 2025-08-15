//  Includes following functions:
//    checkMedTimes()         *Returns true if the current time indicates that it is time to dispense medication based on the stored medtimes*
//    buttonPress()           *interrupt triggers this function when the button is pressed, effectively raises flag to exit passive loop*

#include <SD_Setup.h>
#include <SD_Stepper.h>
#include <SD_Keypad.h>
#include <SD_Scanner.h>
#include<RTClib.h>
#include <Wire.h>
#include <Adafruit_MCP23X17.h>
#include <Adafruit_Fingerprint.h>

#define BUTTON 2
#define DLATCH 3
#define BUZZER 4
#define MOTOR1 5
#define MOTOR2 6
#define MOTOR3 7
#define MOTOR4 8

//Fingerprint Scanner Serial
#define mySerial Serial1

//Keypad number of rows and columns
#define ROWS 4
#define COLS 4

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);    //Fingerprint Scanner
RTC_DS3231 RTC;                                                   //Real Time Clock
Adafruit_MCP23X17 mcp;                                            //Keypad I2C adapter

char keys[ROWS][COLS] = { //Keypad map
  {'D', '#', '0', '*'},
  {'C', '9', '8', '7'},
  {'B', '6', '5', '4'},
  {'A', '3', '2', '1'}
};
uint8_t rowPins[ROWS] = {0, 1, 2, 3}; // Connect to the row pinouts of the keypad
uint8_t colPins[COLS] = {4, 5, 6, 7}; // Connect to the column pinouts of the keypad
int activeCoil;                       //Indicates what coil(s) (MOTORs 1, 2, 3, and 4) are currently active in the stepper motor
int medTimes[3][2];                   //Stores up to 3 unique times that medicine must be dispensed
int lastDisp;                         //Unixtime for the last time medicine was dispensed
bool scan;                            //Set to true on activation of standby button, triggers fingerprint scan process
bool timeForMeds;                     //Indicates whether it is an appropriate time to dispense a medication
uint8_t id;                           //Fingerprint ID number currently being used by scanner
char fingerprints[20];                //All stored fingerprints (max of 20) with role (U or A) stored at index ID - 1
char lastScannedRole;                 //Role associated with the most recently scanned user
int halfStepsToDispense;              //Number of half steps the motor goes through to dispense the next slot of meds
int slotsRemaining;                   //Keeps track of how many slots in the cylinder still contain meds

void setup() {
    // put your setup code here, to run once:

        //Start Keypad Setup
    Serial.begin(9600);
    Wire.begin();

    if (!mcp.begin_I2C()) { // Default address is 0x20
        Serial.println("Error finding MCP23017. Check wiring!");
        while (1);
    }
  
    // Set up the row pins as outputs
    for (int i = 0; i < ROWS; i++) {
        mcp.pinMode(rowPins[i], OUTPUT);
        mcp.digitalWrite(rowPins[i], HIGH); // deactivate row
    }
  
    // Set up the column pins as inputs with pull-up resistors
    for (int i = 0; i < COLS; i++) {
        mcp.pinMode(colPins[i], INPUT_PULLUP);
    }
  
    Serial.println("Keypad initialized.");
        //End Keypad Setup

        //Start Scanner Setup
    while (!Serial);  // For Yun/Leo/Micro/Zero/...
    delay(100);
    Serial.println("\n\nAdafruit Fingerprint sensor enrollment");
  
    // set the data rate for the sensor serial port
    finger.begin(57600);
  
    if (finger.verifyPassword()) {
        Serial.println("Found fingerprint sensor!");
    } else {
        Serial.println("Did not find fingerprint sensor :(");
        while (1) { delay(1); }
    }
        //End Scanner Setup
        
    pinMode(MOTOR1, OUTPUT);
    pinMode(MOTOR2, OUTPUT);
    pinMode(MOTOR3, OUTPUT);
    pinMode(MOTOR4, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(BUTTON, INPUT);
    attachInterrupt(digitalPinToInterrupt(2), buttonPress, CHANGE);
    
    activeCoil = 1;
    setupSequence();
}

void loop() {
    // put your main code here, to run repeatedly:
    timeForMeds = checkMedTimes();
    if(scan) {
        digitalWrite(BUZZER, LOW);
        lastScannedRole = checkPrint();
        
        if(lastScannedRole != 'N' && timeForMeds) {
            DispenseMeds();
        } 
        else if(lastScannedRole == 'A') {
            //Admin options
            screenPrint("Select Admin Action: ");
            screenPrint("A - Rerun Setup Sequence");
            screenPrint("B - Open Access Hatch");
            screenPrint("Other - Cancel");
            switch(getKeyInput()) {
                case 'A':
                    setupSequence();
                    break;
                case 'B':
                    //openDoor();
                    digitalWrite(DLATCH, LOW);
                    screenPrint("Press any key when door is closed to lock");
                    getKeyInput();
                    digitalWrite(DLATCH, HIGH);
                    break;
                default:
                    break;
            }
        }
        else {
            screenPrint("Invalid Print or Not Time for Med Pass");
        }
        scan = false;
    } else if (timeForMeds) {
        digitalWrite(BUZZER, HIGH);
    }
}

bool checkMedTimes() {
    //return true if the current time is within a certain margin of error of any medTimes AND the medicine hasn't already been dispensed
    DateTime rn = RTC.now();
    int i = 0;
    while(i < 3) {
        if( rn.hour()==medTimes[i][0] && (abs(rn.minute() - medTimes[i][1]) <= 5) && abs(rn.unixtime() - lastDisp) > 600 ) {
            return true;
        }
    }
    return false;
}

void buttonPress() {
    scan = true;
}
