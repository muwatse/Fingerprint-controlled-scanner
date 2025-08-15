//  Includes following functions:
//    getKeyInput()           *monitors keypad for user input, debounces, and returns first keypress detected as associated character*
//    get2DigitInput()        *stores first 2 keypad presses detected and translates characters into 2 digit integer, MAY CAUSE ISSUES IF NON-NUM KEY INPUTS*

char getKeyInput() {
    char input = 0;

    while(input = 0){
        for (int row = 0; row < ROWS; row++) {
            mcp.digitalWrite(rowPins[row], LOW); // Activate row
        
            for (int col = 0; col < COLS; col++) {
                // Check if button is pressed (active low)
                if (mcp.digitalRead(colPins[col]) == LOW) {
                    // Debounce
                    delay(20);
                    if (mcp.digitalRead(colPins[col]) == LOW) {
                        Serial.print("Button ");
                        Serial.print(keys[row][col]);
                        Serial.println(" pressed");
                        input = keys[row][col];
                        // Wait for button release
                        while (mcp.digitalRead(colPins[col]) == LOW) {
                            delay(10); // Simple debounce
                        }
                        delay(20); // More debounce
                    }
                }
            }
            mcp.digitalWrite(rowPins[row], HIGH); // Deactivate row
        }
    }
    
    return input;
}

int get2DigitInput() {
    char input1 = getKeyInput();
    char input2 = getKeyInput();
    int input1AsInt = input1 - '0';
    int input2AsInt = input1 - '0';
    return (input1AsInt * 10) + input2AsInt;
}
