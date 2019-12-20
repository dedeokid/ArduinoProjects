//Inclui Biblioteca do Receptor de Rádio
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//Define os Pinos do Rádio
#define CE_PIN   9
#define CSN_PIN 10

//Define os Pinos das Luzes e buzina
#define light_Red A4     //LED RED  A4 
#define light_Green   A3  //LED Green 10 
#define horn_Buzz    A5     

//Define os Pinos dos Motores
#define  IN_11 A2         // L298N #1 in 1 motor Tras Dir 
#define  IN_12 2          // L298N #1 in 2 motor Tras Dir
#define  IN_13 3          // L298N #1 in 3 motor Frente Dir 
#define  IN_14 4          // L298N #1 in 4 motor Frente Dir

#define  IN_21 5         // L298N #2 in 1 motor Tras Esq
#define  IN_22 6         // L298N #2 in 2 motor Tras Esq
#define  IN_23 7         // L298N #2 in 3 motor Frente Esq
#define  IN_24 8         // L298N #2 in 4 motor FrenteEsq

//Usado pelo Radio
const uint64_t pipe = 0xE8E8F0F0E1LL;

RF24 radio(CE_PIN, CSN_PIN); 

//Coleção de dados recebidos do Joystick
int data[9]; 
//Convertendo os dados do Joystick Para o carrinho entender 
int  xAxis, yAxis;
int buttonUp;
int buttonRight;
int buttonDown;
int buttonLeft;

//Configurações Gerais
void setup()   
{
  Serial.begin(9600);//frequência das comunicações    
  radio.begin();//Liga as comunicações
  radio.setRetries(15,15);//Tentativas de comunicação
  radio.openReadingPipe(1,pipe);
  radio.startListening();

//Declarando os tipos de Pinos
  pinMode(light_Red, OUTPUT);
  pinMode(light_Green, OUTPUT);
  pinMode(horn_Buzz, OUTPUT);

  pinMode(IN_11, OUTPUT);
  pinMode(IN_12, OUTPUT);
  pinMode(IN_13, OUTPUT);
  pinMode(IN_14, OUTPUT);
  
  pinMode(IN_21, OUTPUT);
  pinMode(IN_22, OUTPUT);
  pinMode(IN_23, OUTPUT);
  pinMode(IN_24, OUTPUT);
  }

void loop() {
   //Se tem sinal de Rádio pega o que vem nele
  if ( radio.available() )
  {
    radio.read( data, sizeof(data) );  //lê o sinal 
// Descomentar se quiser ver os dados 
//Serial.print("data[0]=");
//Serial.println(data[0]);
//Serial.print("data[1]=");
//Serial.println(data[1]);
//Serial.print("data[2]=");
//Serial.println(data[2]);
//Serial.print("data[3]=");
//Serial.println(data[3]);
//Serial.print("data[4]=");
//Serial.println(data[4]);
//Serial.print("data[5]=");
//Serial.println(data[5]);
//Serial.print("data[6]=");
//Serial.println(data[6]);
//Serial.print("data[7]=");
//Serial.println(data[7]);
//Serial.print("data[8]=");
//Serial.println(data[8]);

//Convertendo os valores dos dados do Joystick para o Carrinho ler
      xAxis = data[0];
      yAxis = data[1];
     
      int buttonUp    = data[2];
      int buttonRight = data[3];
      int buttonDown  = data[4];
      int buttonLeft  = data[5];

//Lógica de COntrole do CArrinho
if (buttonLeft==0){digitalWrite(horn_Buzz, HIGH);}
    else{digitalWrite(horn_Buzz, LOW);}
if (buttonDown==0){digitalWrite(light_Red, HIGH); }
    else{digitalWrite(light_Red, LOW);}
if (buttonRight==0){digitalWrite(light_Green, HIGH);}
    else{digitalWrite(light_Green, LOW);}
    
if (buttonUp==0)
    {
  Pare();
    } 
else if (yAxis>600)
    {  //Luz Verde
 digitalWrite(light_Green, HIGH);
 
     if (xAxis<448)//Esquerda
       {
        FrenteEsq(); 
       }
     else if (xAxis>600)//Direita
       {
        FrenteDir();
       }
     else
       {
        Frente();
       }
    }

else if (yAxis<448)
    {
       //Luz Vermelha
 digitalWrite(light_Red, HIGH);
 
     if (xAxis<448)//Esquerda
       {
        ReDir(); 
       }
     else if (xAxis>600)//Direita
       {
        ReEsq();
       }
     else
       {
        Re();
       }
    }
else
  {
    Morto();
  }
}
 
}//fecha loop

//Funções de estado para controle do Carrinho
void Frente(){
//Gira o Motor motor Tras Dir  no sentido horario
 digitalWrite(IN_11, HIGH);
 digitalWrite(IN_12, LOW);
 //Gira o Motor motor Frente Dir  no sentido horario
 digitalWrite(IN_13, HIGH);
 digitalWrite(IN_14, LOW);
 //Gira o motor Tras Esq no sentido horario
 digitalWrite(IN_21, HIGH);
 digitalWrite(IN_22, LOW);
 //Gira o motor Frente Esq no sentido horario
 digitalWrite(IN_23, HIGH);
 digitalWrite(IN_24, LOW);

}
void FrenteDir(){
//Gira o Motor motor Tras Dir  no sentido horario
 digitalWrite(IN_11, LOW);
 digitalWrite(IN_12, LOW);
 //Gira o Motor motor Frente Dir  no sentido horario
 digitalWrite(IN_13, LOW);
 digitalWrite(IN_14, LOW);
 //Gira o motor Tras Esq no sentido horario
 digitalWrite(IN_21, HIGH);
 digitalWrite(IN_22, LOW);
 //Gira o motor Frente Esq no sentido horario
 digitalWrite(IN_23, HIGH);
 digitalWrite(IN_24, LOW);
 
}
void FrenteEsq(){
//Gira o Motor motor Tras Dir  no sentido horario
 digitalWrite(IN_11, HIGH);
 digitalWrite(IN_12, LOW);
 //Gira o Motor motor Frente Dir  no sentido horario
 digitalWrite(IN_13, HIGH);
 digitalWrite(IN_14, LOW);
 //Gira o motor Tras Esq no sentido horario
 digitalWrite(IN_21, LOW);
 digitalWrite(IN_22, LOW);
 //Gira o motor Frente Esq no sentido horario
 digitalWrite(IN_23, LOW);
 digitalWrite(IN_24, LOW);
 
}
void Re(){
 //Gira o Motor motor Tras Dir  no sentido horario
 digitalWrite(IN_11, LOW);
 digitalWrite(IN_12, HIGH);
 //Gira o Motor motor Frente Dir  no sentido horario
 digitalWrite(IN_13, LOW);
 digitalWrite(IN_14, HIGH);
 //Gira o motor Tras Esq no sentido horario
 digitalWrite(IN_21, LOW);
 digitalWrite(IN_22, HIGH);
 //Gira o motor Frente Esq no sentido horario
 digitalWrite(IN_23, LOW);
 digitalWrite(IN_24, HIGH);
}
void ReEsq(){
 //Gira o Motor motor Tras Dir  no sentido horario
 digitalWrite(IN_11, LOW);
 digitalWrite(IN_12, HIGH);
 //Gira o Motor motor Frente Dir  no sentido horario
 digitalWrite(IN_13, LOW);
 digitalWrite(IN_14, HIGH);
 //Gira o motor Tras Esq no sentido horario
 digitalWrite(IN_21, LOW);
 digitalWrite(IN_22, LOW);
 //Gira o motor Frente Esq no sentido horario
 digitalWrite(IN_23, LOW);
 digitalWrite(IN_24, LOW);
}
void ReDir(){
//Gira o Motor motor Tras Dir  no sentido horario
 digitalWrite(IN_11, LOW);
 digitalWrite(IN_12, LOW);
 //Gira o Motor motor Frente Dir  no sentido horario
 digitalWrite(IN_13, LOW);
 digitalWrite(IN_14, LOW);
 //Gira o motor Tras Esq no sentido horario
 digitalWrite(IN_21, LOW);
 digitalWrite(IN_22, HIGH);
 //Gira o motor Frente Esq no sentido horario
 digitalWrite(IN_23, LOW);
 digitalWrite(IN_24, HIGH);
}
void Pare(){
 //Gira o Motor TrasDir no sentido horario
 digitalWrite(IN_11, HIGH);
 digitalWrite(IN_12, HIGH);
 //Gira o Motor FrenteDir no sentido horario
 digitalWrite(IN_21, HIGH);
 digitalWrite(IN_22, HIGH);
 //Gira o Motor FrenteEsq no sentido horario
 digitalWrite(IN_13, HIGH);
 digitalWrite(IN_14, HIGH);
 //Gira o Motor TrasDir no sentido horario
 digitalWrite(IN_23, HIGH);
 digitalWrite(IN_24, HIGH);
}
void Morto(){
 //Gira o Motor TrasDir no  Ponto Morto
 digitalWrite(IN_11, LOW);
 digitalWrite(IN_12, LOW);
 //Gira o Motor FrenteDir  Ponto Morto
 digitalWrite(IN_21, LOW);
 digitalWrite(IN_22, LOW);
 //Gira o Motor FrenteEsq  Ponto Morto
 digitalWrite(IN_13, LOW);
 digitalWrite(IN_14, LOW);
 //Gira o Motor TrasDir  Ponto Morto
 digitalWrite(IN_23, LOW);
 digitalWrite(IN_24, LOW);
}

