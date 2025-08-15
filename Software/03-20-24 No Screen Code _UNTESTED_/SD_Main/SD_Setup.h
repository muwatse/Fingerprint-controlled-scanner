//  Includes following functions:
//    setupSequence()   *Takes user inputs to set up med time schedule and store all fingerprints, can be rerun to overwrite/reset schedule and stored prints*
//    getNumUsers()     *Prompts user for the number of users, A for independent user, B for caretaker, returns 1 for A and 2 for B*
//    getPPU()          *Prompts user for prints per user, returns integer prints per user*
//    getPPD()          *Prompts user for medpasses per day, returns integer keypad input (1, 2, or 3)*
//    setMedTimes()     *Constructs and returns med pass schedule array times[3][2] based on user inputs, of form [[hr, min], [hr, min], [hr, min]]*

//  Depends on following functions (not included):
//    storePrints()     *Located in: SD_Scanner*
//    screenPrint()     *Located in: *
//    getKeyInput()     *Located in: SD_Keypad*
//    get2DigitInput()  *Located in: SD_Keypad*


void setupSequence() {
    int numUsers;     //Indicates whether there is a separate caregiver (2) or not (1)
    int PPU;          //Indicates number of Prints Per User that are stored
    int numPrints;    //Indicates total number of prints stored
    char scanFor;     //Indicates whether current fingerprints being scanned are for an Admin ('A') or User ('U')
    int PPD;          //Indicates number of med Passes Per Day

    finger.emptyDatabase();         //Clears any currently stored fingerprints from database if setup is being rerun
    for(int i = 0; i < 20; i++) {   //Clears fingerprints array of previously stored roles
        fingerprints[i] = '';
    }

    while (numUsers == 0 || PPU == 0) {
        numUsers = getNumUsers();
        PPU = getPPU();
        if (numUsers > 2 || numUsers < 1 || PPU > 10 || PPU < 1) {
            screenPrint("INVALID INPUT(S)");
            numUsers = 0;
            PPU = 0;
        }
    }

    storePrints(numUsers, PPU); 

    PPD = 0;
    
    while (PPD == 0) {
        PPD = getPPD();
        if (PPD < 1 || PPD > 3) {
            //screenPrint("INVALID INPUT");
            PPD = 0;
        }
    }
    medTimes = setMedTimes(PPD);

    screenPrint("Setup Process Complete");
}

int getNumUsers() {
    char input;
    screenPrint("A) Indep. User or B) User and Caregiver?");
    while(input != 'A' && input != 'B') {
        input = getKeyInput();
    }
    if(input == 'A') {
        return 1;
    } else {
        return 2;
    }
}

int getPPU() {
    int input = 0;
    while(input > 10 || input < 1) {
        screenPrint("Enter #prints per user (2 digits: 01...10)");
        input = get2DigitInput();
        if(input > 10 || input < 1) {
            screenPrint("Invalid Input");
            delay(1000);
        }
    }
    return input;
}

int getPPD() {
    char input;
    int inputAsInt
    screenPrint("Input number of med passes per day (1-3)");
    while(input != '1' && input != '2' && input != '3') {
        input = getKeyInput();
    }
    inputAsInt = input - '0';
    return inputAsInt;
}

int setMedTimes(PPD) {
    int times[3][2] = {{-1, -1}, {-1, -1}, {-1, -1}};
    int hrs = 25;
    int mins = 70;
    for(int i = 0; i < PPD; i++) {
        screenPrint("Med pass time in 24 hour format (2pm -> 1400)");
        while((hrs > 24 || hrs < 0) || (mins > 59 || mins < 0)) {
            hrs = get2DigitInput();
            mins = get2DigitInput();
            if((hrs > 24 || hrs < 0) || (mins > 59 || mins < 0)) {
                screenPrint("Invalid Input");
            }
        }
        times[i][0] = hrs;
        times[i][1] = mins;
    }
    return times; 
}
