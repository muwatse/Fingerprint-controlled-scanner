#define MOTOR1 5
#define MOTOR2 6
#define MOTOR3 7
#define MOTOR4 8
int activeCoil;   //Indicates what coil(s) (MOTORs 1, 2, 3, and 4) are currently active in the stepper motor
int numUsers;     //Indicates whether there is a separate caregiver (2) or not (1)
int PPU;          //Indicates number of Prints Per User that are stored



void setup() {
    // put your setup code here, to run once:
    pinMode(MOTOR1, OUTPUT);
    pinMode(MOTOR2, OUTPUT);
    pinMode(MOTOR3, OUTPUT);
    pinMode(MOTOR4, OUTPUT);
    activeCoil = 1;
    
}

void loop() {
    // put your main code here, to run repeatedly:
    while(true) {
      motorHalfSteps(516);
      delay(1000);
    }
}

void motorHalfSteps(int numHalfSteps) {
    for(int i = 1; i <= numHalfSteps; i++) {
        switch(activeCoil) {
            case 1:
                activeCoil = 13;
                digitalWrite(MOTOR3, HIGH);
                break;
            case 13:
                activeCoil = 3;
                digitalWrite(MOTOR1, LOW);
                break;
            case 3:
                activeCoil = 32;
                digitalWrite(MOTOR2, HIGH);
                break;
            case 32:
                activeCoil = 2;
                digitalWrite(MOTOR3, LOW);
                break;
            case 2:
                activeCoil = 24;
                digitalWrite(MOTOR4, HIGH);
                break;
            case 24:
                activeCoil = 4;
                digitalWrite(MOTOR2, LOW);
                break;
            case 4:
                activeCoil = 41;
                digitalWrite(MOTOR1, HIGH);
                break;
            case 41:
                activeCoil = 1;
                digitalWrite(MOTOR4, LOW);
                break;
        }
    }
}
