// #define LED_BUILTIN 2
#include <WiFi.h>        // Include the Wi-Fi library
#include <WebServer.h>
#include <Servo.h>

#define SERVO 32
Servo myservo;

#define FTR1 22
#define FTR2 23
#define FTR_VEL 33

#define FTL1 18
#define FTL2 19
#define FTL_VEL 21

#define BACK1 16
#define BACK2 17
#define BACK_VEL 5

const char *ssid = "OmniRobo";
const char *password = "314159265";

WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "Pagina principal");
}

void handleNotFound() {
  server.send(404, "text/plain", "Não encontrado");
}

void servo() {
  // Movimenta a cabeça
  static bool nextPos = false;

  if(nextPos){
    for (int pos = 90; pos <= 180; pos += 1) {
      myservo.write(pos);
      delay(15);
    }
    nextPos=false;
  }else{
    for (int pos = 180; pos >= 90; pos -= 1) {
      myservo.write(pos);
      delay(15);
    }
    nextPos=true;
  }
  server.send(200, "text/html", "Movendo cabeça");
}

void stop() {
  // Para
  digitalWrite(FTR1, LOW);
  digitalWrite(FTR2, LOW);
  digitalWrite(FTR_VEL, LOW);

  digitalWrite(FTL1, LOW);
  digitalWrite(FTL2, LOW);
  digitalWrite(FTL_VEL, LOW);

  digitalWrite(BACK1, LOW);
  digitalWrite(BACK2, LOW);
  digitalWrite(BACK_VEL, LOW);

  server.send(200, "text/html", "Ok!");
}
void move1() {
  // Move para frente
  digitalWrite(FTR1, HIGH);
  digitalWrite(FTR2, LOW);
  digitalWrite(FTR_VEL, HIGH);

  digitalWrite(FTL1, HIGH);
  digitalWrite(FTL2, LOW);
  digitalWrite(FTL_VEL, HIGH);

  digitalWrite(BACK1, LOW);
  digitalWrite(BACK2, LOW);
  digitalWrite(BACK_VEL, LOW);

  server.send(200, "text/html", "Ok!");
}
void move2() {
  // Gira para direita
  // O ideal seria andar na diagonal
  digitalWrite(FTR1, LOW);
  digitalWrite(FTR2, HIGH);
  digitalWrite(FTR_VEL, HIGH);

  digitalWrite(FTL1, HIGH);
  digitalWrite(FTL2, LOW);
  digitalWrite(FTL_VEL, HIGH);

  digitalWrite(BACK1, LOW);
  digitalWrite(BACK2, HIGH);
  digitalWrite(BACK_VEL, HIGH);

  server.send(200, "text/html", "Ok!");
}

void move3() {
  // Gira para direita
  // O ideal seria andar na diagonal
  digitalWrite(FTR1, LOW);
  digitalWrite(FTR2, HIGH);
  digitalWrite(FTR_VEL, HIGH);

  digitalWrite(FTL1, HIGH);
  digitalWrite(FTL2, LOW);
  digitalWrite(FTL_VEL, HIGH);

  digitalWrite(BACK1, LOW);
  digitalWrite(BACK2, HIGH);
  digitalWrite(BACK_VEL, HIGH);

  server.send(200, "text/html", "Ok!");
}
void move4() {
  // Ré
  digitalWrite(FTR1, LOW);
  digitalWrite(FTR2, HIGH);
  digitalWrite(FTR_VEL, HIGH);

  digitalWrite(FTL1, LOW);
  digitalWrite(FTL2, HIGH);
  digitalWrite(FTL_VEL, HIGH);

  digitalWrite(BACK1, LOW);
  digitalWrite(BACK2, LOW);
  digitalWrite(BACK_VEL, LOW);

  server.send(200, "text/html", "Ok!");
}
void move5() {
  // Gira para esquerda
  // O ideal seria andar na diagonal
  digitalWrite(FTR1, HIGH);
  digitalWrite(FTR2, LOW);
  digitalWrite(FTR_VEL, HIGH);

  digitalWrite(FTL1, LOW);
  digitalWrite(FTL2, HIGH);
  digitalWrite(FTL_VEL, HIGH);

  digitalWrite(BACK1, HIGH);
  digitalWrite(BACK2, LOW);
  digitalWrite(BACK_VEL, HIGH);

  server.send(200, "text/html", "Ok!");
}

void move6() {
  // Gira para esquerda
  // O ideal seria andar na diagonal
  digitalWrite(FTR1, HIGH);
  digitalWrite(FTR2, LOW);
  digitalWrite(FTR_VEL, HIGH);

  digitalWrite(FTL1, LOW);
  digitalWrite(FTL2, HIGH);
  digitalWrite(FTL_VEL, HIGH);

  digitalWrite(BACK1, HIGH);
  digitalWrite(BACK2, LOW);
  digitalWrite(BACK_VEL, HIGH);

  server.send(200, "text/html", "Ok!");
}

void setup() {
  // LED
  pinMode(LED_BUILTIN, OUTPUT);

  // MOTORS
  pinMode(FTR1, OUTPUT);
  pinMode(FTR2, OUTPUT);
  pinMode(FTR_VEL, OUTPUT);
  pinMode(FTL1, OUTPUT);
  pinMode(FTL2, OUTPUT);
  pinMode(FTL_VEL, OUTPUT);
  pinMode(BACK1, OUTPUT);
  pinMode(BACK2, OUTPUT);
  pinMode(BACK_VEL, OUTPUT);
  myservo.attach(SERVO);

  // Serial Begin
  Serial.begin(115200);
  Serial.println("Booting");

  WiFi.softAP(ssid, password);             // Start the access point
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");

  delay(100);

  WiFi.softAPConfig(IPAddress(192,168,4,2), IPAddress(192,168,4,2), IPAddress(255,255,255,0));

  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());         // Send the IP address of the ESP32 to the computer

  server.on("/", handleRoot);
  server.on("/servo", servo);
  server.on("/stop", stop);
  server.on("/move1", move1);
  server.on("/move2", move2);
  server.on("/move3", move3);
  server.on("/move4", move4);
  server.on("/move5", move5);
  server.on("/move6", move6);

  server.onNotFound(handleNotFound);

  // Liga o led
  server.on("/ligaled", []() {
    server.send(200, "text/plain", "ligou");
    digitalWrite(LED_BUILTIN, HIGH);
  });

  // Desliga o led
  server.on("/desligaled", []() {
    server.send(200, "text/plain", "apagou");
    digitalWrite(LED_BUILTIN, LOW);
  });

  server.begin();
  Serial.println("HTTP server started");
  //END OF WIFI Server AP

  Serial.println("Ready");
}


void loop() {
  server.handleClient();

  delay(10);
}
