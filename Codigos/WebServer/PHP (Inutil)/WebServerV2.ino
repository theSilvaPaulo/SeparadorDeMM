/*
  WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 9.

 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * WiFi shield attached
 * LED attached to pin 9

 created 25 Nov 2012
 by Tom Igoe
 */
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "WIFI-ISL";      //  your network SSID (name)
char pass[] = "TeMB0b0@i?";   // your network password0
int keyIndex = 0;                 // your network key Index number (needed only for WEP)
int numTotal;
int numVermelho;
int numAmarelo;
int numAzul;
int numMarrom;
int numVerde;
int numLaranja;

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);      // initialize serial communication
  pinMode(9, OUTPUT);      // set the LED pin mode

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);       // don't continue
  }

  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status

  randomSeed(analogRead(0));
}

void numeroRand(){
  numTotal = random(300);
  numVermelho = random(300);
  numAmarelo = random(300);
  numAzul = random(300);
  numVerde = random(300);
  numMarrom = random(300);
  numLaranja = random(300);
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("<!DOCTYPE html>");
            client.print("<html>");
            client.print("<head>");
            client.print("<title>M&M Sorting Machine</title>");
            client.print("<script>");
            client.print("function recarregar(){");
            numeroRand();
            client.print("alert('Voce clicou em recarregar!');");
            client.print("document.getElementById('totalSeparado').innerHTML = ");
            client.print(numTotal);
            client.print(";");
            client.print("document.getElementById('totalVermelho').innerHTML = ");
            client.print(numVermelho);
            client.print(";");
            client.print("document.getElementById('totalAmarelo').innerHTML = ");
            client.print(numAmarelo);
            client.print(";");
            client.print("document.getElementById('totalVerde').innerHTML = ");
            client.print(numVerde);
            client.print(";");
            client.print("document.getElementById('totalMarrom').innerHTML = ");
            client.print(numMarrom);
            client.print(";");
            client.print("document.getElementById('totalAzul').innerHTML = ");
            client.print(numAzul);
            client.print(";");
            client.print("document.getElementById('totalLaranja').innerHTML = ");
            client.print(numLaranja);
            client.print(";");
            client.print("}");
            client.print("</script>");
            client.print("<style>");
            client.print("p{");
            client.print("display: inline-block;");
            client.print("}");
            client.print("</style>");
            client.print("</head>");
            client.print("<body>");
            client.print("<div>");
            client.print("<p>Numero de M&Ms separados: </p><p id='totalSeparado'>0</p>");
            client.print("<br>");
            client.print("<p>Numero de M&Ms vermelhos: </p><p id='totalVermelho'>0</p>");
            client.print("<br>");
            client.print("<p>Numero de M&Ms amarelos: </p><p id='totalAmarelo'>0</p>");
            client.print("<br>");
            client.print("<p>Numero de M&Ms verdes: </p><p id='totalVerde'>0</p>");
            client.print("<br>");
            client.print("<p>Numero de M&Ms marrons: </p><p id='totalMarrom'>0</p>");
            client.print("<br>");
            client.print("<p>Numero de M&Ms azuis: </p><p id='totalAzul'>0</p>");
            client.print("<br>");
            client.print("<p>Numero de M&Ms laranjas: </p><p id='totalLaranja'>0</p>");
            client.print("<br>");
            client.print("<button type = 'button' onclick='recarregar()'>Recarregar</button>");
            client.print("<img src='https://s10.postimg.org/ylfw5u7u1/backgroung_MM_Texted_min.png'>");
            client.print("</div>");
            client.print("</body>");
            client.print("</html>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(9, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(9, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
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
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
