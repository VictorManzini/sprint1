#include <Wire.h> 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define rele 26
#define A 34
#define V 35
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
void setup() {
  Serial.begin(115200);
  pinMode(rele, OUTPUT);
  Wire.begin(21,22);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Display não encontrado");
    while(1);
}
  display.clearDisplay();
}

void loop(){
  int valor_corr = analogRead(A);
  float corrente = (valor_corr / 4095.0) * 30.0;
  int valor_tens = analogRead(V);
  float tensao = (valor_tens / 4095.0) * 220.0;
  float potencia = tensao * corrente;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Corrente:");
  display.print(corrente);
  display.println("A");
  display.print("Tensao:");
  display.print(tensao);
  display.println("V");
  display.print("Potencia:");
  display.print(potencia);
  display.println("W");
  display.display();
  Serial.print("Corrente:");
  Serial.print(corrente);
  Serial.println("A");
  Serial.print("Tensão:");
  Serial.print(tensao);
  Serial.println("V");
  Serial.print("Potência atual:");
  Serial.print(potencia);
  Serial.println("W");
  delay(750);
  if (corrente > 25){
    digitalWrite(rele, LOW);
    Serial.println("RELÉ FECHADO");
  }
  else{
    digitalWrite(rele, HIGH);
    Serial.println("RELÉ ABERTO");
  }
}
