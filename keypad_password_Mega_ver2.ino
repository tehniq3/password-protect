/*
||  Simple Password Entry Using Matrix Keypad
||  4/5/2012 Updates Nathan Sobieck: Nathan@Sobisource.com
||  changed by niq_ro (Nicu FLORICA) - http://www.tehnic.go.ro & http://www.arduinotehniq.com
*/


//* is to validate password   
//# is to reset password attempt

/////////////////////////////////////////////////////////////////

#include <Password.h> //http://www.arduino.cc/playground/uploads/Code/Password.zip
#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip

Password password = Password( "1234" );

/*
const byte ROWS = 4; // Four rows
const byte COLS = 4; //  columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = { 9,8,7,6 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 5,4,3,2, };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
*/

const byte rows = 4;
const byte cols = 3;
char keys[rows][cols] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
//byte rowPins[rows] = {2, 7, 6, 4};
//byte colPins[cols] = {3, 1, 5};
byte rowPins[rows] = {33, 23, 25, 29};
byte colPins[cols] = {31, 35, 27};


// Create the Keypad
//Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

int redPin = 11;
int greenPin = 9;
int yellowPin = 10;



void setup(){

  Serial.begin(9600);
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(yellowPin, OUTPUT);

digitalWrite(redPin, LOW);
digitalWrite(greenPin, LOW);
digitalWrite(yellowPin, LOW);
}

void loop(){
  keypad.getKey();
}

//take care of some special events
void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
    case PRESSED:
	Serial.print("Pressed: ");
	Serial.println(eKey);
	switch (eKey){
	  case '*': checkPassword(); digitalWrite(yellowPin, HIGH); delay(10); digitalWrite(yellowPin, LOW); break;
	  case '#': password.reset(); digitalWrite(yellowPin, HIGH); delay(10); digitalWrite(yellowPin, LOW); Serial.println("clear buffer"); break;
	  default: digitalWrite(yellowPin, HIGH); delay(10); digitalWrite(yellowPin, LOW); password.append(eKey);
     }
  }
}

void checkPassword(){
  if (password.evaluate()){
    Serial.println("Success");
//Add code to run if it works
digitalWrite(redPin, LOW);
digitalWrite(greenPin, HIGH);
digitalWrite(yellowPin, LOW);
delay(3000);
password.reset();
  }else{
    Serial.println("Wrong");
//add code to run if it did not work
digitalWrite(redPin, HIGH);
digitalWrite(greenPin, LOW);
digitalWrite(yellowPin, LOW);
delay(3000);
password.reset();
  }
digitalWrite(redPin, LOW);
digitalWrite(greenPin, LOW);
digitalWrite(yellowPin, LOW);

}
