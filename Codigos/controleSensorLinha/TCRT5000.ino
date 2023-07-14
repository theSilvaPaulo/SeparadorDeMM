#include <Servo.h>
Servo motor360;
Servo motorContinuo;

int sensor = A5;
int valor;

void setup() 
{
    Serial.begin(9600);
    motor360.attach(3);
    motorContinuo.attach(6);
  
    pinMode (sensor, INPUT);
}

void loop() 
{
  valor = analogRead (sensor);
  Serial.println (valor);
    
  while (valor <= 400)
  {
    valor = analogRead (sensor);
    Serial.println (valor);
    moveServoContinuo();

  } 
     
  motorContinuo.write(92);  //Servo Continuo parado
  delay(700);
}

void moveServoContinuo(){
  motorContinuo.write(80);   //Servo Continuo no sentido horário
  //delay(475);
  //motorContinuo.write(92);  //Servo Continuo parado
  //delay(700);
}
