#include <SPI.h>
#include <WiFi.h>

// EDIT: Change the 'ssid' and 'password' to match your network
char ssid[] = "Net-Virtua-4475";  // wireless network name
char password[] = "56644750"; // wireless password
//char ssid[] = "WiFi-Ti";  // wireless network name
//char password[] = "TeMb0b0@i?";
int status = WL_IDLE_STATUS;
WiFiClient client;

// EDIT: 'Server' address to match your domain
char server[] = "192.168.0.13"; // This could also be 192.168.1.18/~me if you are running a server on your computer on a local network.
//char server[] = "10.0.0.30";

// This is the data that will be passed into your POST and matches your mysql column
String numeroTotal;

void setup() {
  Serial.begin(9600);
  
  connectWifi();

  // You're connected now, so print out the status
  printWifiStatus();
}

void loop() {
  postData();
  delay(10000);
}

void connectWifi() {
  // Attempt to connect to wifi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, password);
    // Wait 10 seconds for connection
    delay(5000);
  }
}

void printWifiStatus() {
  // Print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // Print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // Print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

// This method makes a HTTP connection to the server and POSTs data
void postData() {
  numeroTotal = "3423";

  // If there's a successful connection, send the HTTP POST request
  if (client.connect(server, 80)) {
    Serial.println("Connected!");

    // EDIT: The POST 'URL' to the location of your insert_mysql.php on your web-host
    client.println("POST /www/var/html/index.php HTTP/1.1");

    // EDIT: 'Host' to match your domain
    client.println("Host: 192.168.0.13");
    //client.println("Host: 10.0.0.30");
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded;");
    client.print("Content-Length: ");
    client.println(numeroTotal.length());
    client.println();
    client.println(numeroTotal);

    Serial.println("Enviei POST");
  } 
  else {
    // If you couldn't make a connection:
    Serial.println("Connection failed");
    Serial.println("Disconnecting.");
    client.stop();
  }
}
