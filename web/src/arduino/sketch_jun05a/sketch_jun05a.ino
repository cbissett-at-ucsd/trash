
/*
 http://arduino.cc/en/Tutorial/WiFiWebClientRepeating

 This code is in the public domain.

 */

#include <SPI.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "Wuhan Bat Laboratory";        // your network SSID (name)
char pass[] = "***********";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

// Initialize the WiFi client library

WiFiClient client;

// server address:
//char server[] = "143.110.231.221:6543";
IPAddress server(143,110,231,221);

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds

const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds

void setup() {

  //Initialize serial and wait for port to open:

  Serial.begin(9600);
  pinMode(2, OUTPUT);

  while (!Serial) {;}

  // check for the presence of the shield:

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:

  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the status:
  printWiFiStatus();
}

String HTTP_str;
int n_enters=0;
void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
 
  while (client.available()) {
    char c = client.read();
    HTTP_str+=c;
    if(c=='\n' && ++n_enters>5){
      n_enters=0;
      HTTP_str="";
      }
  }
  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {
    Serial.print("\nLast Result:\n");
    Serial.print(HTTP_str.toInt());
    
     HTTP_str="";
    Serial.print("\n\n\nExtracted Value:\n");
    httpRequest();
  }
}
int isActivate(int i){
  if(i==1){
    digitalWrite(2, HIGH);
  }else{
    digitalWrite(2, LOW);
  }
  return 0;
}



String postData;
String postVariable = "id=";
int id=2;

// this method makes a HTTP connection to the server:
void httpRequest() {
  
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  postData = postVariable + id;
  if (client.connect(server, 6543)) {
    Serial.println("connecting...");

    // send the HTTP PUT request:
    client.println("GET /double?id=80085 HTTP/1.1");//manually put in id
    client.println("Host: 143.110.231.221:6543");
    client.println("Connection: close");
    client.println();
    // note the time that the connection was made:
    lastConnectionTime = millis();
  }

  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
