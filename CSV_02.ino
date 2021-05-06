/*  Arduino - CSVfile
  Components needed
    1: SD module
    2: Arduino NANO
  Ciucuitry
    SD module 5V   to Arduino 5V
    SD module GND  to Arduino GND
    SD module MISO to Arduino 12
    SD module MOSI to Arduino 11
    SD module SCK  to arduino 13
    SD module CS   to arduino 10
    Arduino connected to computer through USB
*/
#include <SPI.h>
#include <SD.h>

#define SD_CS 10
#define analog_pin A0 //Anolog output from the amplifier circuits
#define time_save 50  //interval time to save data once, units: ms

File csvFile;

void setup() {
  // Arduino default setting
  Serial.begin(9600);
  Serial.print("Start Initializing");
  //Set CS to OUTPUT mode
  pinMode(SD_CS, OUTPUT);

  if (!SD.begin()) { 
    Serial.println("Initialization Success");
    return;
  }                 
  Serial.println("Initialization Failure");
}

void loop() {
  //millis()is to record how much time from beginning to the end of running the program
  if (millis() % time_save == 0) { 
    SD_Save(analogRead(analog_pin));  //Save the information from A0 in SD card
  }
}

void SD_Save(unsigned int val) {
  //File name:Data.csv, which is stored in SD card
  csvFile = SD.open("Data.csv", FILE_WRITE);
  if (csvFile) {
    Serial.println("Start to Save File");
    csvFile.println(val); 
    csvFile.close();                 // Close the file
    Serial.println("Completed!");
  }
  else {
    Serial.println("Error Opening File");
  }
}
