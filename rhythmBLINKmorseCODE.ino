const int ledPin = LED_BUILTIN;
const int buttonPin = 2;
const int dotDuration = 250;
const int dashDuration = 1250;
const int letterPause = 1000;
const int wordPause = 1500;

bool isBlinking = false;
volatile bool resetFlag = false; 

void blinkDot() {
  digitalWrite(ledPin, HIGH);
  delay(dotDuration);
  digitalWrite(ledPin, LOW);
  delay(dotDuration);
  Serial.print(".");
}

void blinkDash() {
  digitalWrite(ledPin, HIGH);
  delay(dashDuration);
  digitalWrite(ledPin, LOW);
  delay(dotDuration);
  Serial.print("-");
}

void blinkCharacter(char c) {
  if (c == 'R') {
  blinkDot(); blinkDash(); blinkDot();
} else if (c == 'H') {
  blinkDot(); blinkDot(); blinkDot(); blinkDot();
} else if (c == 'Y') {
  blinkDash(); blinkDot(); blinkDash(); blinkDash();
} else if (c == 'T') {
  blinkDash();
} else if (c == 'H') {
  blinkDot(); blinkDot(); blinkDot(); blinkDot();
} else if (c == 'M') {
  blinkDash(); blinkDash();
}

  delay(letterPause);
  Serial.print(" ");
}

void blinkName(char name[], int length) {
  for (int i = 0; i < length; i++) {
    blinkCharacter(name[i]);
    if (resetFlag) break; 
  }
  delay(wordPause);
  Serial.println();
}

void handleButtonPress() {
  resetFlag = true;
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  // for interrupting the morse code
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonPress, FALLING);
}

void loop() {
  if (resetFlag) {
    resetFlag = false; // Clear the reset flag
    isBlinking = true;
  }

  if (isBlinking) {
    Serial.println("RHYTHM : Morse code");
    char name[] = {'R', 'H', 'Y', 'T', 'H', 'M'};
    int length = sizeof(name) / sizeof(name[0]);
    blinkName(name, length);
    isBlinking = false;
  }
}