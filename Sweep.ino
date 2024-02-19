/*
#include "ESP32_Servo.h"

// init servos
Servo mycontservo;
Servo mynormalservo;

// init servo pins and speed
int contServoPin = 32;
int normalServoPin = 12;
int speed = 1700; // rotating speed

// init motor A and B pins
int IN1 = 14;
int IN2 = 27;
int IN3 = 26;
int IN4 = 25;

void open() {
  mynormalservo.write(170);
  sleep(1000);
}

void close() {
  mynormalservo.write(0);
  sleep(1000);
}

void turn() {
  mycontservo.writeMicroseconds(speed);
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void setup() {
  Serial.begin(115200);
  
  mycontservo.attach(contServoPin);
  mynormalservo.attach(normalServoPin);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // write code here
}
*/
/*
#include "ESP32_Servo.h"
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// init servos
Servo mycontservo;
Servo mynormalservo;

// init servo pins and speed
int contServoPin = 32;
int normalServoPin = 12;
int speed = 2000; // rotating speed

// init motor A and B pins
int IN1 = 14;
int IN2 = 27;
int IN3 = 26;
int IN4 = 25;

void open() {
  mynormalservo.write(0);
  //delay(1000);
}

void close() {
  mynormalservo.write(170);
  //delay(1000);
}

void turn() {
  mycontservo.writeMicroseconds(speed);
}

void stopTurn() {
  mycontservo.writeMicroseconds(1500);
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

const char* ssid = "Galaxy A50sA717";
const char* password = "silisili";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  
  mycontservo.attach(contServoPin);
  mynormalservo.attach(normalServoPin);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(115200);
    
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("WiFi Failed!\n");
    return;
  }
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  server.begin();
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  while (client) {
    // Wait until the client sends some data
    //Serial.println("new client");
    while (!client.available()) {
      delay(1);
    }

    // Read the first line of the request
    String request = client.readStringUntil('!');
    Serial.println(request);
    
    parsemessage(request);
    
  }
    client.flush();
    client = server.available();
  //client.stop();
  //Serial.println("Client disconnected");
}

void parsemessage(String cmd) {
  if (cmd == "X") {
    stop();
  } else if (cmd == "S") {

    stopTurn();
  } else if (cmd == "O") {
    stop();
    open();
  } else if (cmd == "C") {
    stop();
    close();
  } else if (cmd == "T") {
    turn();
  } else if (cmd == "F") {
    forward();
  } else if (cmd == "B") {
    backward();
  } else if (cmd == "L") {
    left();
  } else if (cmd == "R") {
    right();
  } else {
    stop();
    stopTurn();
  }
}
*/

#include "ESP32_Servo.h"
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// init servos
Servo mycontservo;
Servo mynormalservo;

// init servo pins and speed
int contServoPin = 32;
int normalServoPin = 12;
int speed = 2000; // rotating speed

// init motor A and B pins
int IN1 = 33;
int IN2 = 27;
int IN3 = 26;
int IN4 = 25;

// init enA and enB
int enA = 13;
int enB = 14;

int motorAStrength = 235;
int motorBStrength = 255;

void open() {
  mynormalservo.write(0);
  //delay(1000);
}

void close() {
  mynormalservo.write(170);
  //delay(1000);
}

void turn() {
  mycontservo.writeMicroseconds(speed);
}

void stopTurn() {
  mycontservo.writeMicroseconds(1500);
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void forward() {
  analogWrite(enA, 235);
	analogWrite(enB, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  analogWrite(enA, 250);
	analogWrite(enB, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  analogWrite(enA, 255);
	analogWrite(enB, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  analogWrite(enA, 255);
	analogWrite(enB, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// JP PASSWORD 1972

const char* ssid = "ANTOINE";
const char* password = "123456789";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  
  mycontservo.attach(contServoPin);
  mynormalservo.attach(normalServoPin);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);

  Serial.begin(115200);
    
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  // WiFi.begin(ssid);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("WiFi Failed!\n");
    return;
  }
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  server.begin();
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  while (client) {
    // Wait until the client sends some data
    //Serial.println("new client");
    while (!client.available()) {
      delay(1);
    }

    // Read the first line of the request
    String request = client.readStringUntil('!');
    Serial.println(request);
    
    parsemessage(request);
    
  }
    client.flush();
    client = server.available();
  //client.stop();
  //Serial.println("Client disconnected");
}

void parsemessage(String cmd) {
  if (cmd == "X") {
    stop();
  } else if (cmd == "S") {

    stopTurn();
  } else if (cmd == "O") {
    stop();
    open();
  } else if (cmd == "C") {
    stop();
    close();
  } else if (cmd == "T") {
    turn();
  } else if (cmd == "F") {
    forward();
  } else if (cmd == "B") {
    backward();
  } else if (cmd == "L") {
    left();
  } else if (cmd == "R") {
    right();
  } else {
    stop();
    stopTurn();
  }
}
