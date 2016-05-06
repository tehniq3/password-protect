/*
||  Simple Password Entry Using Matrix Keypad
||  4/5/2012 Updates Nathan Sobieck: Nathan@Sobisource.com
||  changed by niq_ro (Nicu FLORICA) - http://www.tehnic.go.ro 
||  & http://www.arduinotehniq.com
||  version 3.0.a - alarm style - 06.05.2016, Craiova
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

byte redPin = 2;          // pin alocar pentru led-ul rosu
byte greenPin = 3;         // pin alocat pentru led-ul verde
byte yellowPin = 5;       // pin alocat pentru led-ul galben
byte whitePin = 6;         // pin alocat led-ului alb

byte alarma = 1;   // stare initiala alarma (1 = activa, 0 = asteptare)

void setup(){

Serial.begin(9600);   // se porneste monitorizarea seriala cu 9600bps
keypad.addEventListener(keypadEvent); //add an event listener for this keypad

pinMode(redPin, OUTPUT);      // pinul digital este definit ca iesire
pinMode(greenPin, OUTPUT);
pinMode(yellowPin, OUTPUT);
pinMode(whitePin, OUTPUT);

digitalWrite(redPin, LOW);    // pinul definit ca iesire este in 0 logic
digitalWrite(greenPin, LOW);
digitalWrite(yellowPin, LOW);
digitalWrite(whitePin, HIGH);
}

void loop(){
  keypad.getKey();
  
if (alarma == 2*(alarma/2)) {    // daca numarul e par
digitalWrite(whitePin, HIGH);
}
else {                           // daca numarul este impar
digitalWrite(whitePin, LOW);    
}
  
}

//take care of some special events
void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
    case PRESSED:
	Serial.print("Pressed: ");
	Serial.println(eKey);
	switch (eKey){
	  case '*': checkPassword(); digitalWrite(yellowPin, HIGH); delay(10); digitalWrite(yellowPin, LOW); break;
	  case '#': password.reset(); digitalWrite(yellowPin, HIGH); digitalWrite(redPin, HIGH); digitalWrite(greenPin, HIGH); delay(10); digitalWrite(yellowPin, LOW); digitalWrite(redPin, LOW); digitalWrite(greenPin, LOW); Serial.println("clear buffer"); break;
	  default: digitalWrite(yellowPin, HIGH); delay(10); digitalWrite(yellowPin, LOW); password.append(eKey);
     }
  }
}

void checkPassword(){
  if (password.evaluate()){
    Serial.println("Succes");
digitalWrite(redPin, LOW);
digitalWrite(greenPin, HIGH);
digitalWrite(yellowPin, LOW);  
//Add code to run if it works
 alarma = alarma + 1;
delay(1000);
password.reset();
digitalWrite(yellowPin, HIGH);
digitalWrite(redPin, HIGH);
digitalWrite(greenPin, HIGH);
delay(10);
digitalWrite(yellowPin, LOW);
digitalWrite(redPin, LOW);
digitalWrite(greenPin, LOW);
Serial.println("clear buffer");

  }else{
    Serial.println("Wrong code");
//add code to run if it did not work
digitalWrite(redPin, HIGH);
digitalWrite(greenPin, LOW);
digitalWrite(yellowPin, LOW);
delay(1000);
password.reset();
digitalWrite(yellowPin, HIGH);
digitalWrite(redPin, HIGH);
digitalWrite(greenPin, HIGH);
delay(10);
digitalWrite(yellowPin, LOW);
digitalWrite(redPin, LOW);
digitalWrite(greenPin, LOW);
Serial.println("clear buffer");

  } 
digitalWrite(redPin, LOW);
digitalWrite(greenPin, LOW);
digitalWrite(yellowPin, LOW);

}
