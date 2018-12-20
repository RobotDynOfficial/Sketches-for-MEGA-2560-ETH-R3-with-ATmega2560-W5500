/*
  Initialize code for MEGA ETH, Ethernet module W5500
 */
#include <SPI.h>
#include<Ethernet.h>
#include <SD.h>
#define SS     10    //W5500 CS
#define RST    7    //W5500 RST For mega RST 11
#define CS  4     //SD CS pin
// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
#if defined(WIZ550io_WITH_MACADDRESS) // Use assigned MAC address of WIZ550io
;
#else
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
#endif

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;
File myFile;

boolean state=true;
void setup() 
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
  pinMode(SS, OUTPUT);
  pinMode(RST, OUTPUT);
  pinMode(CS, OUTPUT);
  digitalWrite(SS, LOW);
  digitalWrite(CS, HIGH);

  /* If you want to control Reset function of W5500 Ethernet controller */
  digitalWrite(RST,HIGH);

    // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("Start!");
  // this check is only needed on the Leonardo:
   while (!Serial) {
     ; // wait for serial port to connect. Needed for Leonardo only
   }

  // start the Ethernet connection:
  #if defined(WIZ550io_WITH_MACADDRESS) // Use assigned MAC address of WIZ550io
    if (Ethernet.begin() == 0) {
  #else
    if (Ethernet.begin(mac) == 0) {
  #endif  
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for (;;)
      ;
  }
  // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
  Serial.println();
  digitalWrite(SS, HIGH);
  digitalWrite(CS,LOW);
  delay(10);
  if (!SD.begin(CS)) 
  {
    Serial.println("No SD card!");
    return;
  }

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  SD.remove("test.txt");
  delay(50);

}

void loop() 
{
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); 
    Serial.print("IP address = ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  
  }
  Serial.println();
  Serial.println();
  delay(5000);
}
