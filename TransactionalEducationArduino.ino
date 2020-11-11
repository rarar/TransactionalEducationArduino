#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#include "kalogo_bw3.h"
#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

String readString;
String startFPM, endFPM, masteryLevelChange, numAttempted, numCorrect, pointsEarned;
String label;
int count = 0;
void setup() {
  Serial.begin(9600); // Starts the serial communication
  mySerial.begin(19200);
  pinMode(7, OUTPUT); digitalWrite(7, LOW);
  printer.begin();
}
void loop() {
  while (Serial.available()) {
    delay(2);  //delay to allow byte to arrive in input buffer
    char c = Serial.read();
    readString += c;
    if (readString.length() > 0 && c == '\n') {
      readString.replace("\n", "");
      switch (count) {
        case 0:
          //            label = "= handshake succes";
          //            readString += label;
          break;
        case 1:
          // ending FPM
          endFPM = readString;
          break;
        case 2:
          // mastery level change
          masteryLevelChange = readString;
          break;
        case 3:
          // number attempted
          numAttempted = readString;
          break;
        case 4:
          // number correct
          numCorrect = readString;
          break;
        case 5:
          // points earned
          pointsEarned = readString;
          break;
        case 6:
          // starting FPM
          startFPM = readString;
          break;
      }
      //        Serial.println(readString);
      //        Serial.println(count);
      //printer.println(readString);
      readString = "";
      count++;
      if (count > 6) {
        printer.printBitmap(kalogo_bw3_width, kalogo_bw3_height, kalogo_bw3_data);
        printer.println("");

        printer.justify('L');
        printer.setSize('S');
        printer.boldOn();
        printer.println(F("Ending Mastery Level"));
        printer.boldOff();
        printer.setSize('M');
        printer.println(endFPM);
        printer.println();
        printer.boldOn();
        printer.setSize('S');
        printer.println(F("Mastery Level Change"));
        printer.boldOff();
        printer.setSize('M');
        printer.println(masteryLevelChange);
        printer.println();
        printer.boldOn();
        printer.setSize('S');
        printer.println(F("Number of Questions Correct"));
        printer.boldOff();
        printer.setSize('M');
        printer.print(numCorrect);
        printer.print("/");
        printer.println(numAttempted);
        printer.println();
        printer.boldOn();
        printer.setSize('S');
        printer.println(F("Points Earned"));
        printer.boldOff();
        printer.setSize('M');
        printer.println(pointsEarned);
        printer.println();
        printer.boldOn();
        printer.setSize('S');
        printer.println(F("Starting Mastery Level"));
        printer.boldOff();
        printer.setSize('M');
        printer.println(startFPM);
        printer.println();
        printer.feed(2);
        count = 1;
      }
    }
  }
}
