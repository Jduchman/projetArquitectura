//librerias necesarias
#include <LiquidCrystal.h> 
#include <Servo.h>
#define MQpin A0

//Definimos las variables de los servomotores
Servo servoGas;
int servo = 0;
Servo servoAgua;

//Definimos los pines de uso para el LCD/
LiquidCrystal lcd(8,9,10,11,12,13);

//Asignamos pins para los componentes
int LedAgua = 3;
int LedGas = 2;
int LED1 = 5;
int LED2 = 6;
int BUZZER = 4;
int Flama;
int Valor_Gas;

void setup() {
  
  Serial.begin(9600);
  //Definimos pines para el servomotor/
  servoAgua.attach(1);
  servoGas.attach(0);
  lcd.begin(16,2);//inicializamos el LCD/
  analogWrite(A4,50);//establece el contraste de la pantalla
  //Definimos tipos de salida de los pines/
  pinMode(MQpin, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LedAgua, OUTPUT);
  pinMode(LedGas, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}
//funcion que enciende la bocina y su frecuencia
void bocinaOnn(){
  for(int x = 0;x < 180; x++){
    float sinVal = (sin(x*(3.1412/180)));
    int toneVal = 2000+(int(sinVal*1000));
    tone(BUZZER, toneVal);
    delay(2);
  }
}
//apaga la bocina
void bocinaOff(){
  tone(BUZZER,0);
}
void cerrarServo(Servo servoX){
  //el servo gira de 180 a 0 grados
  for(servo = 180;servo >=0; servo--){
    servoX.write(servo);
  }
}
void abrirServo(Servo servoX){
  //el servo gira de 0 a 180 grados
  for(servo = 0;servo <= 180; servo++){
    servoX.write(servo);
  }
}

void avisoFuego(){
  lcd.setCursor(0,0);//primera linea del LCD
  lcd.print("¡¡FUEGO!!");
  lcd.setCursor(0,1);//segunda linea del LCD
  lcd.print("¡¡FUEGO!!");
  delay(100);
  lcd.clear(); //limpia la pantalla
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
  lcd.print("¡¡TODO CORRECTO!!");
  lcd.setCursor(0,1);
  lcd.print("¡¡TODO CORRECTO!!");
  delay(100);
  lcd.clear();
}


void loop() {
  //captura de datos
  Flama = analogRead(A1);
  Valor_Gas = analogRead(MQpin);
  
  if (Valor_Gas > 500){ //Si detecta fuga de gas
    if(Flama <= 100){ //Si detecta fuego
      //se manda dos señales altas
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,HIGH);
              
      digitalWrite(LedAgua,HIGH);//led encendida
      digitalWrite(LedGas,LOW);//led apagada
                
      bocinaOnn();
      avisoFuego();
      cerrarServo(servoGas);
      abrirServo(servoAgua);
      delay(100);
    }
    else{ //no detecta Fuego
      //se manda una sañal baja y una alta
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,LOW);
              
      digitalWrite(LedAgua,LOW);
      digitalWrite(LedGas,LOW);
      bocinaOnn();
      avisoGas();
      cerrarServo(servoGas);
      cerrarServo(servoAgua);
      delay(100);
    }
  }           
  else {  //No detecta fuga de gas
    if(Flama <= 100){ //SE DETECTA FUEGO
      //se manda una sañal baja y una alta
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,LOW);
              
      digitalWrite(LedAgua,HIGH);
      digitalWrite(LedGas,LOW);
      bocinaOnn();
      avisoFuego();
      abrirServo(servoAgua);
      cerrarServo(servoGas);
      delay(100);
        
    }else{  //todo en orden
      bocinaOff();
      avisoNormal();
      //se manda dos sañales bajas
      digitalWrite(LED1,LOW);
      digitalWrite(LED2,LOW); 
      digitalWrite(LedAgua,LOW);
      digitalWrite(LedGas,HIGH);
      cerrarServo(servoAgua);
      abrirServo(servoGas);
    }
  }
}
