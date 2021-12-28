/*librerias*/
#include <LiquidCrystal.h> 
#include <Servo.h>
#define MQpin A0

/*Definimos la posicion de inicio del servomotor*/
Servo servoGas;
int servo = 0;
Servo servoAgua;

/*Definimos los pines de uso para el LCD*/
LiquidCrystal lcd(8,9,10,11,12,13);

/*Declaramos las variables*/
float TEMPERATURA;
int SENSORFlame;
int Valor_Gas;
int LED1PIN5 = 5;
int LED2PIN6 = 6;
int BUZZER = 4;

void setup() {
  
  Serial.begin(9600);
  /*Definimos pines para el servomotor*/
  servoAgua.attach(3);
  servoGas.attach(2);
  analogWrite(A4,50);
  /*
  servoAgua.write(0);
  servoGas.write(0);
  */
  /*inicializamos el LCD*/
  lcd.begin(16,2);
  /*Definimos tipos de salida de los pines*/
  pinMode(LED1PIN5, OUTPUT);
  pinMode(LED2PIN6, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void bocinaOnn(){
  digitalWrite(BUZZER,HIGH);
}

void bocinaOff(){
  digitalWrite(BUZZER,LOW);
}
void cerrarServo(Servo servoX){
//  for(servo = 180;servo >=0; servo--){
//    servoX.write(servo);
//  }
 for(servo = 0;servo <= 180; servo++){
    servoX.write(servo);
  }
}
void abrirServo(Servo servoX){
//  for(servo = 0;servo <= 180; servo++){
//    servoX.write(servo);
//  }
  for(servo = 180;servo >=0; servo--){
    servoX.write(servo);
  }
}
void avisoFuego(){
  lcd.setCursor(0,0);
  lcd.print("¡¡FUEGO!!");
  lcd.setCursor(0,1);
  lcd.print("¡¡FUEGO!!");
  delay(100);
  lcd.clear();
}
void avisoAmbos(){
  lcd.setCursor(0,0);
  lcd.print("¡¡FUGA DE GAS!!");
  lcd.setCursor(0,1);
  lcd.print("¡¡CON FUEGO!!");
  delay(100);
  lcd.clear();
}
void avisoGas(){
  lcd.setCursor(0,0);
  lcd.print("¡¡FUGA DE GAS!!");
  lcd.setCursor(0,1);
  lcd.print("¡¡FUGA DE GAS!!");
  delay(100);
  lcd.clear();
}
void avisoNormal(){
  lcd.setCursor(0,0);
  lcd.print("TODO CORRECTO!!");
  lcd.setCursor(0,1);
  lcd.print("TODO CORRECTO!!");
  delay(100);
  lcd.clear();
}


void loop() {
  
  Valor_Gas = analogRead(MQpin);//tomara el valor_gas ya sea 0v(LOW) o 5V(HIGH)
  SENSORFlame = analogRead(A1);
  Serial.println("Valor_Gas: ");
  Serial.println(Valor_Gas);
  avisoNormal();
  Serial.println("SENSORFlame: ");
  Serial.println(SENSORFlame);
  /*
  if (Valor_Gas == HIGH){ //Si detecta fuga de gas
         if(SENSORFlame == HIGH){ //Si detecta fuego
              digitalWrite(LED2PIN6,LOW);
              digitalWrite(LED1PIN5,LOW);
              bocinaOnn();
              avisoAmbos();
              cerrarServo(servoGas);
              abrirServo(servoAgua);
        }
        else{ //no detecta Fuego
              digitalWrite(LED2PIN6,HIGH);
              digitalWrite(LED1PIN5,LOW);
              bocinaOnn();
              avisoGas();
              cerrarServo(servoAgua );
              cerrarServo(servoGas);
        }
  }           
  else {  //No detecta fuga de gas
    if(SENSORFlame == HIGH){ //SE DETECTA FUEGO
              digitalWrite(LED2PIN6,HIGH);
              digitalWrite(LED1PIN5,LOW);
              bocinaOnn();
              avisoFuego();
              abrirServo(servoAgua);
              cerrarServo(servoGas);
      
        }else{  //todo en orden
                bocinaOff();
                avisoNormal();
                digitalWrite(LED2PIN6,LOW);
                digitalWrite(LED1PIN5,HIGH); 
                cerrarServo(servoAgua);
                abrirServo(servoGas);
          }
  }*/
}
