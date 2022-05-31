
/*
 * This code will configure ESP8266 in station mode and it will then act as a web server after connecting to a WiFi Router. 
 * It will then turn On/Off 4 antenna relays as per user input from the browser connected client
 * 
 * Derived from code written by Awais Naeem
 * see https://www.embedded-robotics.com/esp8266-web-server/
 */

#include <Arduino.h>

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <WiFiClient.h>
  #include <ESP8266WebServer.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <WiFiClient.h>
  #include <WebServer.h>
#endif

#include <ElegantOTA.h>

// private definitions
#include "private.h"               // <<<<<<<  COMMENT THIS OUT FOR YOUR INSTANCE - this contains stuff for my network, not yours

#if defined(ESP8266)
  ESP8266WebServer server(80);
#elif defined(ESP32)
  WebServer server(80);
#endif

#define VERSION "Ver 1.1 build 2022.05.31"

// Specify the SSID and Password of the WiFi

#ifndef WIFI_SSID
#define WIFI_SSID "your_ssid"            //  <<<<<<<  REPLACE WITH YOUR CREDENTIALS
#endif
#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "your_password"    //  <<<<<<<  REPLACE WITH YOUR CREDENTIALS
#endif

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;
const char *hostname = "antennasw";

// Specify button labels
String button_label_1 = "End Fed Half Wave (1.2KW)";
String button_label_2 = "Flag Pole w/Tuner (120W)";
String button_label_3 = "- UNUSED -";
String button_label_4 = "Dummy Load (300W)";


//Specifying the Pins
uint8_t ant1_pin=D1;   // GPIO5
uint8_t ant2_pin=D5;   // GPIO14
uint8_t ant3_pin=D6;   // GPIO12
uint8_t ant4_pin=D7;   // GPIO13


//Specifying the boolean variables indicating status
bool ant1_status=false, ant2_status=false, ant3_status=false, ant4_status=false;

//function protoypes
void handle_OnConnect();
void handle_ant1on();
void handle_ant1off();
void handle_ant2on();
void handle_ant2off();
void handle_ant3on();
void handle_ant3off();
void handle_ant4on();
void handle_ant4off();
void handle_antalloff();
void handle_NotFound();
String HTML();
void sync_IOpins();

void setup() {
 

  //Starting the serial communication channel
  Serial.begin(115200);
  Serial.print("\n\nVersion: ");
  Serial.println(VERSION);
  Serial.print("\nConnecting to ");
  Serial.print(ssid);

 //Output mode for the Pins
  pinMode(ant1_pin,OUTPUT);
  pinMode(ant2_pin,OUTPUT);
  pinMode(ant3_pin,OUTPUT);
  pinMode(ant4_pin,OUTPUT);

  digitalWrite(ant1_pin,LOW);
  digitalWrite(ant2_pin,LOW);
  digitalWrite(ant3_pin,LOW);
  digitalWrite(ant4_pin,LOW);

  
  //Connecting to the local WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostname);
  WiFi.begin(ssid,password);

  //Keep checking the WiFi status until it is connected to the wifi network

  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi Connected with IP Address: ");
  Serial.println(WiFi.localIP());

  //Specifying the functions which will be executed upon corresponding GET request from the client
  server.on("/",handle_OnConnect);
  server.on("/ant1on",handle_ant1on);
  server.on("/ant1off",handle_ant1off);
  server.on("/ant2on",handle_ant2on);
  server.on("/ant2off",handle_ant2off);
  server.on("/ant3on",handle_ant3on);
  server.on("/ant3off",handle_ant3off);
  server.on("/ant4on",handle_ant4on);
  server.on("/ant4off",handle_ant4off);
  server.on("/antalloff", handle_antalloff);
  server.onNotFound(handle_NotFound);
  
  //Starting the Server
  ElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP Server Started");

  sync_IOpins();

}

void loop() {

  if(WiFi.status()==WL_CONNECTED)//Check if ESP8266 is still connected to the internet
  {
    //Assign the server to handle the clients
    server.handleClient();

    //Turn the pins ON/OFF as per their status set by the connected client
  
    //ANT1
    if(ant1_status==false)
    {
      digitalWrite(ant1_pin,LOW);
    }
    else
    {
      digitalWrite(ant1_pin,HIGH);
    }
  
    //ANT2
    if(ant2_status==false)
    {
      digitalWrite(ant2_pin,LOW);
    }
    else
    {
      digitalWrite(ant2_pin,HIGH);
    }
  
    //ANT3
    if(ant3_status==false)
    {
      digitalWrite(ant3_pin,LOW);
    }
    else
    {
      digitalWrite(ant3_pin,HIGH);
    }
  
    //ANT4
    if(ant4_status==false)
    {
      digitalWrite(ant4_pin,LOW);
    }
    else
    {
      digitalWrite(ant4_pin,HIGH);
    }
  }
  else
  {
    Serial.println("WiFi Disconnected!!!");
    Serial.print("Trying to establish the connection...");
    
    //Keep checking the WiFi status until it is connected to the wifi network
    while(WiFi.status()!=WL_CONNECTED)
    {
      delay(1000);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("WiFi Connected with IP Address: ");
    Serial.println(WiFi.localIP());
  }
}

void handle_OnConnect()
{
  sync_IOpins();
  Serial.println("Client Connected");
  server.send(200, "text/html", HTML());
}

void handle_ant1on()
{
  Serial.println("ANT1 ON");
  ant1_status=true;
  ant2_status=false;
  ant3_status=false;
  ant4_status=false;
  server.send(200, "text/html", HTML());
}

void handle_ant1off()
{
  Serial.println("ANT1 OFF");
  ant1_status=false;
  server.send(200, "text/html", HTML());
}

void handle_ant2on()
{
  Serial.println("ANT2 ON");
  ant2_status=true;
  ant1_status=false;
  ant3_status=false;
  ant4_status=false;
  server.send(200, "text/html", HTML());
}

void handle_ant2off()
{
  Serial.println("ANT2 OFF");
  ant2_status=false;
  server.send(200, "text/html", HTML());
}

void handle_ant3on()
{
  Serial.println("ANT3 ON");
  ant3_status=true;
  ant1_status=false;
  ant2_status=false;
  ant4_status=false;
  server.send(200, "text/html", HTML());
}

void handle_ant3off()
{
  Serial.println("ANT3 OFF");
  ant3_status=false;
  server.send(200, "text/html", HTML());
}

void handle_ant4on()
{
  Serial.println("ANT4 ON");
  ant4_status=true;
  ant1_status=false;
  ant2_status=false;
  ant3_status=false;
  server.send(200, "text/html", HTML());
}

void handle_ant4off()
{
  Serial.println("ANT4 OFF");
  ant4_status=false;
  server.send(200, "text/html", HTML());
}

void handle_antalloff()
{
  Serial.println("ALL OFF");
  ant4_status=false;
  ant1_status=false;
  ant2_status=false;
  ant3_status=false;
  server.send(200, "text/html", HTML());
}

void handle_NotFound()
{
  server.send(404, "text/plain", "Not found");
}

String HTML()
{
  String msg="<!DOCTYPE html> <html>\n";
  msg+="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  msg+="<title>Antenna Selector</title>\n";
  msg+="<style>html{font-family:Helvetica; display:inline-block; margin:0px auto; text-align:center;}\n";
  msg+="body{margin-top: 50px;} h1{color: #444444; margin: 50px auto 30px;} h3{color:#444444; margin-bottom: 50px;}\n";
  msg+=".button{display:block; width:240px; background-color:#f48100; border:none; color:white; padding: 13px 30px; text-decoration:none; font-size:18px; margin: 0px auto 35px; cursor:pointer; border-radius:4px;}\n";
  msg+=".button-off{background-color:#f48100;}\n";
  msg+=".button-off:active{background-color:#f48100;}\n";
  msg+=".button-on{background-color:#26282d;}\n";
  msg+=".button-on:active{background-color:#26282d;}\n";
  msg+="</style>\n";
  msg+="</head>\n";
  msg+="<body>\n";
  msg+="<h1>Antenna Selector</h1>\n";
  //msg+="<h3>(Single User Only)</h3>\n";
  
  if(ant1_status==false)
  {
    msg+="<a class=\"button button-on\" href=\"/ant1on\">" + button_label_1 + "</a>\n";
  //  msg+="<p>ANT1 Status: OFF</p><a class=\"button button-on\" href=\"/ant1on\">OFF</a>\n";    
  }
  else
  {
    msg+="<a class=\"button button-off\" href=\"/ant1off\">" + button_label_1 + "</a>\n";
  //  msg+="<p>ANT1 Status: ON</p><a class=\"button button-off\" href=\"/ant1off\">ON</a>\n";
  }

  if(ant2_status==false)
  {
    msg+="<a class=\"button button-on\" href=\"/ant2on\">" + button_label_2 + "</a>\n";
  }
  else
  {
    msg+="<a class=\"button button-off\" href=\"/ant2off\">" + button_label_2 + "</a>\n";
  }

  if(ant3_status==false)
  {
    msg+="<a class=\"button button-on\" href=\"/ant3on\">" + button_label_3 + "</a>\n";
  }
  else
  {
    msg+="<a class=\"button button-off\" href=\"/ant3off\">" + button_label_3 + "</a>\n";
  }

  if(ant4_status==false)
  {
    msg+="<a class=\"button button-on\" href=\"/ant4on\">" + button_label_4 + "</a>\n";
  }
  else
  {
     msg+="<a class=\"button button-off\" href=\"/ant4off\">" + button_label_4 + "</a>\n";
  }
  
  msg+="</body>\n";
  msg+="</html>\n";
  return msg;
}

void sync_IOpins()
{
  if (digitalRead(ant1_pin) == 1)
    ant1_status = true;
  else
    ant1_status = false;
  if (digitalRead(ant2_pin) == 1)
    ant2_status = true;
  else
    ant2_status = false;
  if (digitalRead(ant3_pin) == 1)
    ant3_status = true;
  else
    ant3_status = false;
  if (digitalRead(ant4_pin) == 1)
    ant4_status = true;
  else
    ant4_status = false;
}
