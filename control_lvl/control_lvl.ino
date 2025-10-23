/*
  Nombre del proyecto: Control de Nivel con Arduino
  Autor: Cristian Castro
  Fecha: 14/10/2025
  Descripción: Código para controlar el nivel de un tanque con sensor ultrasónico y bomba.
  Derechos de autor: (c) 2025 Cristian Castro
  Licencia: MIT License
*/
#define TRIG_PIN 9
 #define ECHO_PIN 8
 const int potPin = A0; // Entrada analógica del potenciómetro
 const int pwmPin = 3; // Salida PWM (D3, D5, D6, D9, D10 o D11 en UNO)
 const int pinSwitch = 7; // Pin donde conectas el interruptor
 float ALTURA_TANQUE = 30.0; // cm
 float a = 0.8282; // coeficiente IIR (0<α≤1 → más bajo = más filtrado)
 float nivel_a1 = 0.0;
 volatile float nivel_filt = 0.0;
 volatile float nivel_1 = 0.0;
 volatile bool flag_nuevo_dato = false;
 unsigned long duracion;
 float distancia;
 float nivel;
 int estado;
 int pot; 
 float ref=0;
 float y=0;
 float e=0,e1=0;
 float u=0,u1=0;
 float K0=22.2622;
 float K1=-22.0274;
 float tiempo=0;
 uint32_t LoopTimer;
 void setup() {
 Serial.begin(115200);
 pinMode(TRIG_PIN, OUTPUT);
 pinMode(ECHO_PIN, INPUT);
 pinMode(pinSwitch, INPUT_PULLUP);
 LoopTimer = micros();  
 }
 
 void loop() {
 estado = digitalRead(pinSwitch); 
 pot =1023- analogRead(potPin); 
 // --- Disparo ultrasónico ---
 digitalWrite(TRIG_PIN, LOW);
 delayMicroseconds(2);
 digitalWrite(TRIG_PIN, HIGH);
 delayMicroseconds(10);
 digitalWrite(TRIG_PIN, LOW);
 
 // Medición no bloqueante
 duracion = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30 ms
if (duracion == 0) {
  LoopTimer = micros(); 
  return;
}
 distancia = duracion / 58.2; // cm
 nivel = ALTURA_TANQUE - distancia;
 if (nivel < 0) nivel = 0;
 
 // --- Filtro IIR ---
 nivel_filt = (1.0-a)*nivel + a*nivel_1;
 nivel_1 = nivel_filt;
 flag_nuevo_dato = true;
 if (estado == LOW) { // automatico
 y= pot*20.0/1023.0;
 ref=round(y/4)*4;
 e=ref-nivel_filt;
 u=u1+K0*e+K1*e1;
 if (u >= 100.0){ //saturacion
 u = 100.0;
 }
 if (u <= 0.0 || ref==0.0){
 u = 0.0;
 }
 
 } else { // manual
 e1=0;
 u1=0;
 u = map(pot, 0, 1023, 0, 100); // manual de 0–100
 }
 analogWrite(pwmPin, map(u, 0, 100, 0, 255));
 e1=e;
 u1=u;
if (flag_nuevo_dato) {
  flag_nuevo_dato = false;
  if (Serial) {  // Solo imprime si el puerto sigue conectado
    Serial.print(ref);
    Serial.print(",");
    Serial.print(nivel_filt);
    Serial.print(",");
    Serial.println(u);
  }
}
 while ( micros() - LoopTimer< 100000); // el codigo se bloquea o no avanza hasta que se cumpla la condicion
 LoopTimer=micros();
 }
