String readString;
String label;
int count = 0;
void setup() {
  Serial.begin(9600); // Starts the serial communication
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop() {
  while (Serial.available()) {
    delay(2);  //delay to allow byte to arrive in input buffer
    char c = Serial.read();
    readString += c;
    if (readString.length() > 0 && c == '\n') {
      readString.replace("\n","");
      switch (count) {
        case 0:
          label = "= handshake succes";
          readString += label;
          break;
        case 1:
          label = " = endingFpmLevel";
          readString += label;
          break;
        case 2:
          label = " = masteryLevelChange";
          readString += label;
          break;
        case 3:
          label = " = numAttempted";
          readString += label;
          break;
        case 4:
          label = " = numCorrect";
          readString += label;
          break;
        case 5:
          label = " = pointsEarned";
          readString += label;
          break;
        case 6:
          label = " = startingFpmLevel";
          readString += label;
          break;
      }
      Serial.println(readString);
      Serial.println(count);
      readString = "";
      count++;
      if (count > 6) count = 1;
    }
  }
}
