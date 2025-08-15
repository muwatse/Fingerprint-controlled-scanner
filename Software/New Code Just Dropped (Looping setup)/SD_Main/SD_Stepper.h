//  Includes following functions:
//    motorHalfSteps()    *Rotates stepper motor through a given number of halfsteps, starting at activeCoil input*
//    dispenseMeds()      *Rotate stepper enough to dispense next med slot, return number of filled slots remaining in cylinder*


int motorHalfSteps(int numHalfSteps) {
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
    return activeCoil;
}

int dispenseMeds() {
    lastDisp = rn.unixtime();
    motorHalfSteps(halfStepsToDispense);
    slotsRemaining--;
    screenPrint("Slots Remaining: ");
    screenPrint(slotsRemaining);
}
