/*
  This a simple example of the aREST Library for Arduino (Uno/Mega/Due/Teensy)
  using the WiFi library (for example to be used with the Arduino WiFi shield).
  See the README file for more details.

  Written in 2014 by Marco Schwartz under a GPL license.
*/

#include <SPI.h>
#include <WiFi.h>
#include <aREST.h>

char ssid[] = "Net-Virtua-4475"; //  your network SSID (name)
char pass[] = "56644750";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

// Create aREST instance
aREST rest = aREST();

// Initialize the WiFi server library
WiFiServer server(80);

// Variables to be exposed to the API
int total;
int vermelho;
int amarelo;
int azul;
int verde;
int laranja;
int marrom;

void setup() {

  // Start Serial
  Serial.begin(9600);

  // Init variables and expose them to REST API
  total = 24;
  vermelho = 40;
  amarelo = 0;
  azul = 0;
  verde = 0;
  laranja = 0;
  marrom = 0;
  
  //rest.variable("total",&total);
  rest.variable("vermelho",&vermelho);
  rest.variable("amarelo",&amarelo);
  rest.variable("azul",&azul);
  rest.variable("verde",&verde);
  rest.variable("laranja",&laranja);
  rest.variable("marrom",&marrom);/**/

  // Give name and ID to device (ID should be 6 characters long)
  rest.set_id("Arduin");
  rest.set_name("Eduardo_Teste");

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if ( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware");

  // Attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // Wait 10 seconds for connection
    delay(10000);
  }

  // Start the server
  server.begin();

  // Print out the status
  printWifiStatus();
}


void loop() {

  // listen for incoming clients
  WiFiClient client = server.available();

  total++;
  vermelho++;

  delay(3000);
  
  rest.handle(client);

}

void printWifiStatus() {
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
