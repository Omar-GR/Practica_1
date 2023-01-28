#include <Adafruit_Sensor.h>  //Libreria de Sensor de Temperatura y Humedad
#include <DHT.h>              //Libreria de Sensor de Temperatura y Humedad
#include <DHT_U.h>            //Libreria de Sensor de Temperatura y Humedad
#include <ESP32Servo.h>       //Libreria del Servomotor

//DHT11
#define DHTTYPE 11            //El tipo de sensor que tenemos 
#define DHTPIN 15             //El pin que hagamos
#define servoPin 13           //Definimos el pin

//Servo Motor
Servo Servo1; //Una variable de tipo Servo
int data;     //Variable entera que ingresara el usuario;

//Fotoresistencia
const int potPin = 4;
int potValue = 0;

//Led
const int Led = 22;

//Sensor de Distancia
const int Trig = 2;  //Pin digita para el Trigger del sensor
const int PinEcho = 21;    //Pin digital para el Echo del sensor

//Varibles y contantes
int periodo = 10000;
unsigned long TiempoAhora = 0;
String opcion;
float T,H;
long t; //timepo que demora en llegar el eco
long d; //distancia en centimetros
DHT dht(DHTPIN,DHTTYPE);

void setup() {
 //Vamos a establecer la velocidad de datos en bits por seg.
  Serial.begin(115200);              
  //Led
  pinMode(Led, OUTPUT);
  //Servo
//Conectar la variable servo a el pin que definimos 
  Servo1.attach(servoPin);            
  //Sensor
  dht.begin();
  //Sensor distancia
  pinMode(Trig, OUTPUT); //pin como salida
  pinMode(PinEcho, INPUT);  //pin como entrada
  digitalWrite(Trig, LOW);//Inicializamos el pin con 0
}

void loop() {
  
  if(millis() > TiempoAhora + periodo){
 TiempoAhora = millis();
    H=dht.readHumidity();
    T=dht.readTemperature();
    Serial.println("Humedad");
    Serial.println(H);
    Serial.println("Temperatura");
    Serial.println(T);
    //Sensor de iluminacion
    Serial.println("Iluminacion");
    potValue = analogRead(potPin);
    Serial.println(potValue);
    //Sensor de distancia
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);          //Enviamos un pulso de 10us
    digitalWrite(Trig, LOW);
    t = pulseIn(PinEcho, HIGH); //obtenemos el ancho del pulso
    d = t/59;             //escalamos el tiempo a una distancia en cm
    Serial.print("Distancia: ");
    Serial.print(d);      //Enviamos serialmente el valor de la distancia
    Serial.print("cm");
    Serial.println();
    delay(100);          //Hacemos una pausa de 100ms
}

//Motor
if (Serial.available()){
  opcion = Serial.readStringUntil('\n');
  if (opcion == "p"){
      digitalWrite(Led, HIGH);
     }if ( opcion == "a" ){ 
        digitalWrite(Led, LOW); 
      }if (opcion.toInt() >0 and opcion.toInt()<=180){
          data=opcion.toInt(); 
          servo();
      }if (opcion == "0"){
          data=0; 
          servo();
      }
  }
}

void servo(){
  if(data<180){
//En caso de que sea mayor a 180, el servomotor se coloca a 180º
    Servo1.write(data);     
  }else if(data>=180){
//En caso de que sea mayor a 180, el servomotor se coloca a 180º
    Servo1.write(180);    
  }
  
}
