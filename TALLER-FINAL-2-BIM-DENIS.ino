/* FUNDACIÓN KINAL 
   DENIS ESTUARDO DE JESÚS RAMÍREZ PADILLA 
   TALLER DE ELECTRONICA DIGITAL 
   EB5AM 
   2020288
   ALEJANDRO NAVAS
   PROYECTO FINAL BIM II
*/

//Librerias
#include <Keypad.h>             //Libreria que me permite usar el teclado matricial
#include <Wire.h>    //Liberias para usar el protocolo i2c
#include <LiquidCrystal_I2C.h>  //Libreria que controla la LCD por medio de I2C
#include <Servo.h> //libreria que me permite usar el servo

//Directivas de preprocesador Servo
#define pin_Servo 12

//Directivas de preprocesador LCD
#define direccion_lcd 0x20
#define filas 2
#define columnas 16

//Definicion de los Pines 
const int leds[] = {A0 , A1 , A2 , A3};

//Macros o directivas de preprocesador
#define filas_teclado 4   //cantidad de filas que posee el teclado matricial.
#define columnas_teclado 4 //cantidad de columnas que posee el teclado matricial.
#define f1_teclado 6  //pin2 conectado a la fila 1
#define f2_teclado 5  //pin3 conectado a la fila 2
#define f3_teclado 0  //pin4 conectado a la fila 3
#define f4_teclado 0  //pin5 conectado a la fila 4
#define c1_teclado 4  //pin6 conectado a la columna 1
#define c2_teclado 3  //pin7 conectado a la columna 2
#define c3_teclado 2  //pin8 conectado a la columna 3
#define c4_teclado 0  //pin9 conectado a la columna 4


const int a = 7;
const int b = 8;
const int c = 9;
const int d = 0;
const int e = 0;
const int f = 10;
const int g = 11;

const int E = 7;
const int segmentos[E] = {a, b, c, d, e, f, g};

const int numeros[10][E] = {
  /*9*/ {0, 1, 0, 0, 0, 0, 0},
  /*9*/ {1, 0, 0, 0, 0, 0, 0},
  /*9*/ {0, 0, 0, 0, 0, 1, 0},
  /*9*/ {0, 0, 0, 0, 0, 0, 1},
  /*9*/ {0, 0, 1, 0, 0, 0, 0},
  /*9*/ {1, 1, 1, 0, 0, 1, 1},

};
const int APAGADO = LOW;


//Creo una matriz led con la disposicion fisica de las teclas
char keys[filas_teclado][columnas_teclado] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pines_filas[filas_teclado] = {f1_teclado,f2_teclado,f3_teclado,f4_teclado};
byte pines_columnas[columnas_teclado] = {c1_teclado,c2_teclado,c3_teclado,c4_teclado};

Keypad teclado_Denis = Keypad( makeKeymap(keys), pines_filas, pines_columnas, filas_teclado,columnas_teclado);   //teclado matricial 4x4 conectado al arduino por diversos pines

//Constructor
LiquidCrystal_I2C lcdDenis(direccion_lcd, columnas, filas); //LCD con direccion 0x20 y tamanio 16x2

//Constructor
Servo Servo_Denis;  //mi servo


void setup(){
Serial.begin(9600); 
//-----------------LCD------------------
//Configuraciones
  lcdDenis.init(); //inicio la comunicacion serial con el modulo i2c
  lcdDenis.backlight(); //Enciendo la luz de fondo para poder ver el texto
  lcdDenis.print("     DENIS     ");  //Muestro el texto en la LCD
  lcdDenis.setCursor(0,1);
  lcdDenis.print(" PROYECTO FINAL ");  
//-----------------servo------------------

    Servo_Denis.attach(pin_Servo);   // servo 
    //Especifico que en el pin12 voy a usar un servomotor.

//-----------------Autofantastico------------------
  for (int S=0; S<sizeof(leds); S++){
    pinMode(leds[S], OUTPUT);}
  
for (int q=0; q<E; q++){
    pinMode(segmentos[q], OUTPUT);
    digitalWrite(segmentos[q], APAGADO);
    }
}
//-----------------Animacion------------------
void print(int z){
  for (int q=0; q<E; q++){
    digitalWrite(segmentos[q], numeros [z][q]);
  }


}

void loop(){   
  char tecla = teclado_Denis.getKey();  //Obtengo la tecla que presione
  if(tecla){
    Serial.print("La tecla presionada es: ");   
    Serial.println(tecla);    
  }
//contador de 99-0 esto esta 
  if(tecla == '1'){ // if de tecla 1
    Serial.println("contador 99 a 0"); // inicia cotador de 0 a 99
    for(int i=0; i<100;i++){
    Serial.println(i);
    delay(200);}
   }    
//contador de 0-99 al reves
  if(tecla == '2'){ // if de tecla 2
    Serial.println("contador 0 a 99"); // inicia cotador de 0 a 99
    for(int i=90; i>=0;i--){
    Serial.println(i);
    delay(200);}
   }    
// Autofantastico 
if(tecla == '3'){
   for (int S=0; S<sizeof(leds); S++){
    digitalWrite(leds[S], HIGH);
     delay(200);
    digitalWrite(leds[S], LOW); 
  }
    for (int S=sizeof(leds)-1; S>0; S--){
    digitalWrite(leds[S], HIGH);
     delay(200);
    digitalWrite(leds[S], LOW);} 
  }

// Animacion
  if(tecla == '4'){
Serial.println("Animacion iniciada"); 
    for (int q=0; q<10; q++){
    print(q);
    delay(500);
  } 
}
 
// servomotor
  if(tecla == '5'){ 
    Serial.println("inicia servo"); 
    Servo_Denis.write(0);
    delay(100);
    Servo_Denis.write(180); 
    delay(100);
     Servo_Denis.write(0);} 
  } 
