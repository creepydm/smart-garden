#include <dht11.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LDRpin A1
#define SOILpin A0
#define DHT11PIN 4
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
dht11 DHT11;

int LDRvalue = 0;
int SOILvalue = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("test");
  display.display();

  pinMode(11,OUTPUT);

}

String ldr(){
  int data = analogRead(LDRpin);
  String light_level = "Dark";
  if(data >= 700){
    light_level = "Bright";
  }else if(data >= 500){
    light_level = "Dim";
  }
  return light_level;
}

String soil(){
  int data = analogRead(SOILpin);
  String moisture = "Dry";
  if (data <= 430){
    moisture = "Wet";
    digitalWrite(11, HIGH);
  }else{
    digitalWrite(11, LOW);
  }
  return moisture;
}

int hum(){
  int chk = DHT11.read(DHT11PIN);
  return (float)DHT11.humidity;
}

String temp(){
  int chk = DHT11.read(DHT11PIN);
  float t = (float)DHT11.temperature;
  return String(t) + "*C";
}

int ddisplay(String text){
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(text);
  display.display();
  return 0;
}

void loop() {
  int x;
  float h;
  String y;
  int time = 2000;

  y = ldr();
  ddisplay("LDR: \n" + String(y));
  delay(time);

  y = soil();
  ddisplay("Soil: \n" + String(y));
  delay(time);

  h = hum();
  if (h != -1) {
    ddisplay("Humidity: \n" + String(h, 2) + "%");
  } else {
    ddisplay("Humidity: Error");
  }
  delay(time);

  y = temp();
  ddisplay("Temp: \n" + y);
  delay(time);
}
