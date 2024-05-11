#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myServo;

int pos = 0;


const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; // Connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x3F, 16, 2); // Address 0x27, 16 columns and 2 rows

char inputBuffer[4]; // Buffer to store the input (maximum 4 digits)
int inputIndex = 0; // Index for the buffer

const int vibrationMotorPin = 13;

void setup() {
  lcd.init(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight
  lcd.print("Enter delay(ms):");
  //pinMode(vibrationMotorPin, OUTPUT);


  myServo.attach(10);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);

}

void loop() {
  char key = keypad.getKey();
  if (key != NO_KEY && inputIndex < 4) {
    inputBuffer[inputIndex++] = key; // Store key in the buffer
    lcd.setCursor(inputIndex, 1); // Set cursor position
    lcd.print(key); // Print the pressed key on LCD
  }

  if (inputIndex == 4) { // If 4 digits are entered
    lcd.clear();
    lcd.print("Delay :");
    int delayTime = atoi(inputBuffer); // Convert inputBuffer to integer
    lcd.print(delayTime); // Print the entered delay time
    delay(delayTime); // Use entered delay as delay parameter
    lcd.clear();
    lcd.print("Vibrating");
   // digitalWrite(vibrationMotorPin, HIGH); // Start the vibration motor
    //delay(delayTime); // Vibrate for 1 second
    //digitalWrite(vibrationMotorPin, LOW);
    //delay(1000); // Stop the vibration motor
    //while (true); // Stop further execution

    for (pos = 0; pos <= 180; pos++){
    myServo.write(pos);
    delay(2);

  }
  for(pos = 180; pos >= 0; pos-=1){
    myServo.write(pos);
    delay(2);
  }

  
   digitalWrite(11,HIGH);
   delay(delayTime);
   digitalWrite(11,LOW);
   delay(200);

      digitalWrite(12,HIGH);
   delay(delayTime);
   digitalWrite(12,LOW);
   delay(200);


   digitalWrite(13,HIGH);
   delay(delayTime);
   digitalWrite(13,LOW);
   //delay(200);


  }
}
