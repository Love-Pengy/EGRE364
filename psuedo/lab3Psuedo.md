# Overall Goals 
+ Use polling to scan the keypad and display the keypad inputs via a serial terminal
    + When a key is pressed its value is displayed on the serial terminal
    + Software debouncing should be used to make sure no double presses accidentally happen
+ "Do Something Cool"
    + use the \# key to repeat the previous inputs

## Impotant Info
+ PB 8 is our SCL 
+ PB 9 is our SDA
+ PC 0 - 3 is our Row 1 - Row 4
+ PC 4, 10, 11, 12 are our Column 1 - 4
```C 
//Display a string
    char message[64] = "ABCDEFGHIJK";
    ...
    ssd1306_Fill(Black);
    ssd1306_SetCursor(2,0);
    ssd1306_WriteString(message, Font_16x26, White);
    ssd1306_UpdateScreen();
```
# Keypad Psuedo 

### Steps
+ create files keypad.c and .h 



# Part 1
```C
keypadPinInit(){
    //enable GPIOC clock 
    // Set GPIOC pins 0, 1, 2, 3 as output
    // set GPIOC pins 4, 10, 11, 12 as input 
}

keypadScan(){
    keypadColumnCheck();
}

keypadColumnCheck(){
    //set all of the rows to 0 
    // read the column input
    //return the raw data read 
    //if nothing is pressed return 0xFF
}



int main (void){
    keypadScan();
}
```


# Part 2
```C
keypadPinInit(){
    //enable GPIOC clock 
    // Set GPIOC pins 0, 1, 2, 3 as output
    // set GPIOC pins 4, 10, 11, 12 as input 
}

keypadScan(){
    //returns raw data for the check 
    keypadColumnCheck();
    //figure out which column it is happening in 
    keypadRowCheck();
    //given the output of the row you now have the row as well meaning you can use a LUT to display the output 
}

keypadColumnCheck(){
    //set all of the rows to 0 
    // read the column input
    //return the raw data read 
    //if nothing is pressed return 0xFF
}

keypadRowCheck(){
    //one by one set one row to 0 and the rest to 1
    // in between each delay for a little amount of time
    //if the output is not all 1's then you found the row 
    //return the row number
}



int main (void){
    keypadScan();
}
```




# Part 3 


```C
keypadPinInit(){
    //enable GPIOC clock 
    // Set GPIOC pins 0, 1, 2, 3 as output
    // set GPIOC pins 4, 10, 11, 12 as input 
}

keypadScan(){
    //returns raw data for the check 
    keypadColumnCheck();
    //figure out which column it is happening in 
    keypadRowCheck();
    //given the output of the row you now have the row as well meaning you can use a LUT to display the output 
}

keypadColumnCheck(){
    //set all of the rows to 0 
    // read the column input
    //return the raw data read 
    //if nothing is pressed return 0xFF
}

keypadRowCheck(){
    //one by one set one row to 0 and the rest to 1
    // in between each delay for a little amount of time
    //if the output is not all 1's then you found the row 
    //return the row number
}

char characterTable[4][4] = { {'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};

sendMessage(uint8_t rowIndex, uint8_t colIndex){
    char message[64] = characterTable[rowIndex, colIndex];    
    ssd1305_Fill(Black);
    ssd1306_SetCursor(2,0);
    ssd1306_WriteString(message, Font_16x26, White);
    ssd1306_UpdateScreen();
}

int main (void){
    while(1){
    keypadScan();
    }
}
```

