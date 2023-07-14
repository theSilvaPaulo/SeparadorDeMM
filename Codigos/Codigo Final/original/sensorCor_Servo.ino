/*
Sensor de Cor com RGB e LDR + Move Servo
*/
#include <Servo.h>
Servo motor360;
Servo motorContinuo;

const int r = 8;
const int g = 9;
const int b = 10;
const int ldr = A0;
const int botao = 2;

int valorRed = 0;
int valorGreen = 0;
int valorBlue = 0;

int redCalibrado = 0;
int greenCalibrado = 0;
int blueCalibrado = 0;

int corLida;

int sensor = A5;
int valor;

/***********************************SETUP*********************************/
void setup() {
    Serial.begin(9600);
    motor360.attach(3);
    motorContinuo.attach(6);

    pinMode(botao, INPUT);
    pinMode(r, OUTPUT);
    pinMode(g, OUTPUT);
    pinMode(b, OUTPUT);
    pinMode (sensor, INPUT);

    //Seta os servos
    motorContinuo.write(92);
    motor360.write(0);
}


/******************************FUNCAO DE CALIBRAR***************************/
void calibrar(){
  redCalibrado = 0;
  greenCalibrado = 0;
  blueCalibrado = 0;
  
  //Le vermelho
  for(int i = 0; i < 5; i++){
    analogWrite(r, 255);
    delay(500);
    redCalibrado += analogRead(ldr);
    digitalWrite(r, LOW);
    delay(100);
  }
  redCalibrado /= 5;
  
  //Le verde
  for(int i = 0; i < 5; i++){
    analogWrite(g, 255);
    delay(500);
    greenCalibrado += analogRead(ldr);
    digitalWrite(g, LOW);
    delay(100);
  }
  greenCalibrado /= 5;
  
  //Le azul
  for(int i = 0; i < 5; i++){
    analogWrite(b, 255);
    delay(500);
    blueCalibrado += analogRead(ldr);
    digitalWrite(b, LOW);
    delay(100);
  }
  blueCalibrado /= 5;
}


/******************************MOVE SERVO******************************/
void moveServo360(){
  if(corLida == 1) motor360.write(3);       //Servo 360 no ângulo 0°
  else if(corLida == 2) motor360.write(18);      //Servo 360 no ângulo 90°
  else if(corLida == 3) motor360.write(32);      //Servo 360 no ângulo 180°
  else if(corLida == 4) motor360.write(46);      //Servo 360 no ângulo 240°
  else if(corLida == 5) motor360.write(60);      //Servo 360 no ângulo 240°
  else if(corLida == 6) motor360.write(75);      //Servo 360 no ângulo 240°
  delay(2500);
}


/****************************MOVE SERVO CONTINUO**************************/
void moveServoContinuo(){
  valor = analogRead (sensor);
  Serial.println (valor);

  //Comeca com um delayzinho
  motorContinuo.write(80);   //Servo Continuo no sentido horário;
  delay(500);
    
  while (valor <= 400){
    valor = analogRead (sensor);
    Serial.println (valor);
    motorContinuo.write(80);   //Servo Continuo no sentido horário;
  } 
     
  motorContinuo.write(92);  //Servo Continuo parado
  delay(700);
}


/*********************************LOOP*********************************/
void loop() {    
  //Move o Servo Continuo
  //moveServoContinuo();
  
  //Verifica botao
  if(digitalRead(botao) == HIGH){
    delay(250);
    if(digitalRead(botao) == HIGH) calibrar();
  }

  //Le vermelho
  analogWrite(r, 255);
  delay(500);
  valorRed = (analogRead(ldr) - redCalibrado);
  digitalWrite(r, LOW);
  
  //Le verde
  analogWrite(g, 255);
  delay(500);
  valorGreen = (analogRead(ldr) - greenCalibrado);
  digitalWrite(g, LOW);

  //Le azul
  analogWrite(b, 255);
  delay(500);
  valorBlue = (analogRead(ldr) - blueCalibrado);
  digitalWrite(b, LOW);

  
  //ANALISE
  if((valorRed <= 50 && valorRed >= -50) && (valorGreen <= 50 && valorGreen >= -50) && (valorBlue <= 50 && valorBlue >= -50)){
    Serial.println("***INCONCLUSIVO***");
    corLida = 0; //INCONCLUSIVO
  }
  else if(valorBlue > valorGreen && valorBlue > valorRed){
    Serial.println("***AZUL***");
    corLida = 1; //AZUL
  }
  else if(valorGreen > valorBlue && (valorRed - valorGreen <= 30 || valorGreen > valorRed)){
    Serial.println("***VERDE***");
    corLida = 2; //VERDE
  }
  else if(valorRed > 400 && valorGreen > 300){
    Serial.println("***AMARELO***");
    corLida = 3; //AMARELO
  }
  else if(valorGreen > 90 && valorGreen < 200 && valorBlue > 50 && valorBlue < 200 && valorRed > 100 && valorRed < 300){
    Serial.println("***MARROM***");
    corLida = 4; //MARROM
  }
  else if(valorRed > valorBlue + valorGreen && valorRed < 450){
    Serial.println("***VERMELHO***");
    corLida = 5; //VERMELHO
  }
  else{
    Serial.println("***LARANJA***");
    corLida = 6; //LARANJA
  }

/*
  Serial.print("CALIBRADO RED: ");
  Serial.println(redCalibrado);
  Serial.print("CALIBRADO GREEN: ");
  Serial.println(greenCalibrado);
  Serial.print("CALIBRADO BLUE: ");
  Serial.println(blueCalibrado);
*/

  //Imprime os valores lidos
  Serial.print("Vermelho: ");
  Serial.println(valorRed);
  Serial.print("Verde: ");
  Serial.println(valorGreen);
  Serial.print("Azul: ");
  Serial.println(valorBlue);
  Serial.println();

  //Move o Servo 360
  moveServo360();
  
  //Move o Servo Continuo
  moveServoContinuo();
  
  delay(500);
}
