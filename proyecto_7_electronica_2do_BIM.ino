
/*
 * 
 Fundacion Kinal
 Centro Educativo Tecnico Laboral KINAL
 Electronica
 Grado:5to A
 Nombre:Roberto Monterroso
 Carne :2019507
 */
#include <Servo.h>
#include <OneWire.h>                
#include <DallasTemperature.h>
#include <Wire.h>    
#include <LiquidCrystal_I2C.h> 
#include <Adafruit_NeoPixel.h>
#include <Servo.h>

#define Push_1 12
#define Push_2 11
#define Push_3 10
#define Foco_1  14
#define Foco_2 15
#define LEDS 7
#define NEO_PIXEL 4
#define SENSOR 13
#define SERVO 5
#define buzzer 6
#define R 9
#define G 8
#define B 7
float Si = 494.883;
int persona_cerca = 0;
int value;
int estado1 = 0;
int estado2 = 0;

Adafruit_NeoPixel rueda(LEDS,NEO_PIXEL, NEO_GRB + NEO_KHZ800);// Constructor

//Caracteres
byte puerta_cerrada[] = {
  B11111,
  B11111,
  B11111,
  B11101,
  B11111,
  B11111,
  B11111,
  B11111
};
byte puerta_semiabierta[] = {
  B11000,
  B11100,
  B11110,
  B11010,
  B11110,
  B11110,
  B11100,
  B11000
};
byte puerta_mitad[] = {
  B11000,
  B11100,
  B11110,
  B11010,
  B11110,
  B11110,
  B11100,
  B11000
};
byte puerta_abierta[] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000
};
byte luz_off[] = {
  B01110,
  B10001,
  B10001,
  B10001,
  B01010,
  B01010,
  B01110,
  B01110
};
byte luz_on[] = {
  B01110,
  B11111,
  B11111,
  B11111,
  B01110,
  B01110,
  B01110,
  B01110
};
byte Grados_C[] = {
  B01000,
  B10100,
  B01000,
  B00011,
  B00100,
  B00100,
  B00100,
  B00011
};
byte hay_persona[] = {
  B01110,
  B01110,
  B01110,
  B10101,
  B01110,
  B00100,
  B00100,
  B01010
};
byte sin_persona[] = {
  B01110,
  B01110,
  B01110,
  B00100,
  B01110,
  B10101,
  B00100,
  B01010  
};
float medicion();
//Constructores
OneWire ourWire(2);//Se establece el pin 2 para usar OneWire
DallasTemperature sensor(&ourWire);
LiquidCrystal_I2C LCD_ROBERTO(0x27, 16, 2);
Servo Servo_ROB; 
float temperatura;


void setup() {
  
  Servo_ROB.attach(SERVO);
  pinMode(SENSOR, INPUT);
  rueda.begin();
  pinMode(Foco_1 , OUTPUT);
  pinMode(Foco_2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(Push_1, INPUT);
  pinMode(Push_2, INPUT);
  pinMode(Push_3, INPUT);
  Serial.begin(9600);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
sensor.begin(); 
LCD_ROBERTO.init(); 
LCD_ROBERTO.backlight(); 
 LCD_ROBERTO.createChar(1, puerta_abierta);
 LCD_ROBERTO.createChar(2, puerta_mitad);
 LCD_ROBERTO.createChar(3, puerta_cerrada);
 LCD_ROBERTO.createChar(4, luz_off);
 LCD_ROBERTO.createChar(5, luz_on);
 LCD_ROBERTO.createChar(6, Grados_C);
 LCD_ROBERTO.createChar(7, hay_persona);
 LCD_ROBERTO.createChar(8, sin_persona);
 LCD_ROBERTO.setCursor(0,1);
  LCD_ROBERTO.print("Puerta:");
  LCD_ROBERTO.setCursor(9,1);
    LCD_ROBERTO.print("Luz 2");
    LCD_ROBERTO.write(5);
    LCD_ROBERTO.setCursor(9,0);
    LCD_ROBERTO.print("Luz 1");
    LCD_ROBERTO.write(4);
    Servo_ROB.write(0);
 }
 
void loop() {
  value = digitalRead(SENSOR);
  luminarias();
  puerta();
  temperatura = medicion();
  luminarias();
  puerta();
  LCD_ROBERTO.setCursor(0,0);
  LCD_ROBERTO.print(temperatura);
  LCD_ROBERTO.write(6);
  luminarias();
  puerta();
  proximidad();
  luminarias();
  puerta();
  condicion_temp();
  luminarias();
puerta();
}

float medicion(){
  sensor.requestTemperatures();//Se envia señal para leer la temperatura
  float temp = sensor.getTempCByIndex(0); //Se obtiene la temperatura en grados centigrados
  Serial.print("Temperatura= ");
  Serial.print(temp);
  Serial.println(" C");
  delay(100);  
  return temp;
  }
void proximidad(){  
  if( value == LOW){
   LCD_ROBERTO.setCursor(7,0);
   LCD_ROBERTO.write(8);
    for(int i = 0; i < 8; i++){
    rueda.setPixelColor(i,rueda.Color(0,200,0));
    rueda.show();
    delay(50);
    rueda.setPixelColor(i,rueda.Color(0,50,20));
    rueda.show();
    delay(50);
      }
    }   
  if(value == HIGH){
    LCD_ROBERTO.setCursor(7,0);
    LCD_ROBERTO.write(7);
    tone(buzzer, 256);
    delay(500);
    for(int i = 0; i < 8; i++){
    rueda.setPixelColor(i,rueda.Color(255,0,0));
    rueda.show();
    delay(50);
    rueda.setPixelColor(i,rueda.Color(40,10,0));
    rueda.show();
    delay(50); 
    }
   noTone(buzzer);
    }
if(persona_cerca == 0){     
}
}
void luminarias(){
if(digitalRead(Push_1)==HIGH && estado1==0){  // si pulsador presionado el led estara apagado
    digitalWrite(Foco_1 , HIGH);// se enciende el led    
    LCD_ROBERTO.setCursor(9,0);
    LCD_ROBERTO.print("Luz 1");
    LCD_ROBERTO.write(4);
    delay(500);// guardamos el estado encendido
    estado1=1;  
  } 
  if(digitalRead(Push_1)==HIGH && estado1==1){  // si pulsador presionado el led estara encendido
    digitalWrite(Foco_1 , LOW);// se apaga el led    
    LCD_ROBERTO.setCursor(9,0);
    LCD_ROBERTO.print("Luz 1");
    LCD_ROBERTO.write(5);
    delay(500); 
    estado1=0;// guardamos el estado apagado   
  }
  if(digitalRead(Push_2)==HIGH && estado2==0){// si pulsador presionado el led estara apagado
    digitalWrite(Foco_2, HIGH);// se enciende el led     
    LCD_ROBERTO.setCursor(9,1);
    LCD_ROBERTO.print("Luz 2");
    LCD_ROBERTO.write(4); 
    delay(500);
    estado2=1;// guardamos el estado encendido   
  } 
  if(digitalRead(Push_2)==HIGH && estado2==1){ // si pulsador presionado el led estara encendido
    digitalWrite(Foco_2, LOW);// se apaga el led  
    LCD_ROBERTO.setCursor(9,1);
    LCD_ROBERTO.print("Luz 2");
    LCD_ROBERTO.write(5); 
    delay(500);
    estado2=0; // guardamos el estado apagado   
  }
}
void puerta(){
  if(digitalRead(Push_3)==LOW){
  Servo_ROB.write(90);
    LCD_ROBERTO.setCursor(0,1);
    LCD_ROBERTO.print("Puerta:");
    LCD_ROBERTO.write(3);
    delay(100);
    LCD_ROBERTO.setCursor(0,1);
    LCD_ROBERTO.print("Puerta:");
    LCD_ROBERTO.write(2);
    delay(100);
    LCD_ROBERTO.setCursor(0,1);
    LCD_ROBERTO.print("Puerta:");
    LCD_ROBERTO.write(1); 
    delay(2000);
    Servo_ROB.write(0);
    LCD_ROBERTO.setCursor(0,1);
    LCD_ROBERTO.print("Puerta:");
    LCD_ROBERTO.write(1);
    delay(100);
    LCD_ROBERTO.setCursor(0,1);
    LCD_ROBERTO.print("Puerta:");
    LCD_ROBERTO.write(2);
    delay(100);
    LCD_ROBERTO.setCursor(0,1);
    LCD_ROBERTO.print("Puerta:");
    LCD_ROBERTO.write(3);
    delay(1000); 
    Servo_ROB.write(0);
  } else{
    Servo_ROB.write(0);
    }
}
void condicion_temp(){
  if(temperatura > 25 && temperatura < 45){
  digitalWrite(R, HIGH);
  digitalWrite(G, LOW);
  digitalWrite(B, LOW);
}
if(temperatura > 21 && temperatura <= 25){
  digitalWrite(R, LOW);
  digitalWrite(G, HIGH);
  digitalWrite(B, LOW);
}
if(temperatura > 15 && temperatura <= 21){
  digitalWrite(R, HIGH);
  digitalWrite(G, LOW);
  digitalWrite(B, HIGH);
}
}
