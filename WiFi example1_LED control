#include <WiFiNINA.h>

// Please use our own WiFi network information
char ssid[] = ""; // Network SSID (name)
char pass[] = ""; // Network Password

int status = WL_IDLE_STATUS; // Initial WiFi status uses the idle state
WiFiServer server(80); // Create a server that listens on port 80

void setup() {
  Serial.begin(9600); // Start serial communication
  while (!Serial); // Wait for the serial port to connect. Necessary only for boards with a native serial port.

  pinMode(LED_BUILTIN, OUTPUT); // Set the built-in LED to output mode

  // Attempt to connect to the WiFi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass); // Connect to a WPA/WPA2 network

    // Wait 10 seconds for the connection to establish
    delay(10000);
  }

  // Once connected, print the IP address
  Serial.print("Successfully connected to ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin(); // Start the server
}

void loop() {
  WiFiClient client = server.available(); // Listen for client connections

  if (client) { // If a client is connected
    Serial.println("New Client."); // Print a message that a new client is connected
    String currentLine = ""; // Used to store characters received from the client
    while (client.connected()) { // While the client stays connected
      if (client.available()) { // If there's data available from the client
        char c = client.read(); // Read the data
        Serial.write(c); // Write the data to the serial monitor
        if (c == '\n') { // If the character is a newline

          // If the current line is empty, i.e., the end of the client's request
          if (currentLine.length() == 0) {
            // Send a standard HTTP response header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // Control the LED
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
            client.println("<body><h2>LED Control</h2>");
            client.println("<p><a href=\"/LED=ON\">Turn On LED</a></p>");
            client.println("<p><a href=\"/LED=OFF\">Turn Off LED</a></p>");
            client.println("</body></html>");

            // Disconnect
            break;
          } else { // If a new line is received, clear the current line
            currentLine = "";
          }
        } else if (c != '\r') { // If the character is a carriage return, ignore it
          currentLine += c; // Add other characters to the current line
        }

        // Check if the current line contains a command to control the LED
        if (currentLine.endsWith("GET /LED=ON")) {
          digitalWrite(LED_BUILTIN, HIGH); // Turn on the LED
        }
        if (currentLine.endsWith("GET /LED=OFF")) {
          digitalWrite(LED_BUILTIN, LOW); // Turn off the LED
        }
      }
    }
    // When the client disconnects
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
