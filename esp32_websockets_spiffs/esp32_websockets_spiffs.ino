#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>

// Replace with your network credentials
const char* ssid = "ESP32_SERVER";
const char* password = "server2018";
const char *msg_robot = "";
const int dns_port = 53;
const int http_port = 80;
const int ws_port = 1337;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(1337);
char msg_buf[10];

void onWebSocketEvent(uint8_t client_num, WStype_t type, uint8_t * payload, size_t length){
  switch(type){
    //client has disconnected
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", client_num);
      break; 

    // new client has connected
    case WStype_CONNECTED:
    {
      IPAddress ip = webSocket.remoteIP(client_num);
      Serial.printf("[%u] Connection from", client_num);
      Serial.println(ip.toString());
    }
    break;
    // handle text messages from client
    case WStype_TEXT:
//      Serial.printf("[%u] Received text: %s\n", client_num, payload);

      //print message received
      if (strcmp((char *)payload, "robotic") == 0){
        Serial.printf("[%u] Received text: %s\n", client_num, payload);
      }else if ( strcmp((char *)payload, "getLEDState") == 0 ) {
        Serial.println("Client requested for message");
      }else{
        Serial.println("Message not recognized");
        }
    break;
        // For everything else: do nothing
    case WStype_BIN:
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
    default:
      break;
  }
}

// Callback: send homepage
void handle_homepage(AsyncWebServerRequest *request) {
  IPAddress remote_ip = request->client()->remoteIP();
  Serial.println("[" + remote_ip.toString() +
                  "] HTTP GET request of " + request->url());
  request->send(SPIFFS, "/index.html", "text/html");
}


// Callback: send 404 if requested file does not exist
void handle_notFound(AsyncWebServerRequest *request) {
  IPAddress remote_ip = request->client()->remoteIP();
  Serial.println("[" + remote_ip.toString() +
                  "] HTTP GET request of " + request->url());
  request->send(404, "text/plain", "Not found");
}

void setup(){
  Serial.begin(115200);
  // begin spiffs and print error if spiffs failed to begin
  if (!SPIFFS.begin()){
    Serial.println("Error mounting SPIFFS");
    while(1);
  }

  //Start Access Point
  WiFi.softAP(ssid,password);

  // print ip information
  Serial.println();
  Serial.println("AP running");
  Serial.print("My IP address: ");
  Serial.println(WiFi.softAPIP());

  // home page request
  server.on("/", HTTP_GET, handle_homepage);

  // handle invalid requests
  server.onNotFound(handle_notFound);
  //begin server
  server.begin();
  //begin websocket server and assign callback function
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);
}

void loop(){
  //look for and handle websocket data
  webSocket.loop();
}
