#include <Servo.h>

Servo motor360;
Servo motorContinuo;

void setup() {
  Serial.begin(9600);
  motor360.attach(6);
  motorContinuo.attach(5);
}

void loop() {
  Serial.println("FUNFANDO");
  
  motorContinuo.write(10);   //Servo Continuo no sentido horário
  delay(500);
  motorContinuo.write(92);  //Servo Continuo parado
  delay(1000);

  
  motor360.write(3);       //Servo 360 no ângulo 0°
  delay(3000);
  motor360.write(20);      //Servo 360 no ângulo 90°
  delay(3000);
/*  motor360.write(40);      //Servo 360 no ângulo 180°
  delay(3000);
  motor360.write(60);      //Servo 360 no ângulo 240°
  delay(3000);*/
}
