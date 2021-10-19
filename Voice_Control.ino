#include <SoftwareSerial.h>

SoftwareSerial BT(0, 1); //TX, RX respetively
//String readvoice;
//String voice;

void setup() {
BT.begin(9600);
Serial.begin(9600);
pinMode(4, OUTPUT);
pinMode(3, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(8, OUTPUT);
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);
pinMode(12, OUTPUT);
pinMode(13, OUTPUT);

}
//-----------------------------------------------------------------------//
void loop() {
//while (BT.available()){ //Check if there is an available byte to read
//delay(10); //Delay added to make thing stable
//char c = BT.read(); //Conduct a serial read
//readvoice += c; //build the string- "forward", "reverse", "left" and "right"
//}
String readvoice;
if (BT.available())
{
  readvoice = BT.readString();
  analogWrite(10, 50);
  analogWrite(11, 50);
}
if (readvoice.length() > 0) {
Serial.print(readvoice);

if(readvoice == "reverse")
{
    digitalWrite(3, LOW);
    digitalWrite (4, HIGH);
    digitalWrite(5,LOW);
    digitalWrite(6,HIGH);
}

if(readvoice == "forward")
{
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
}

if (readvoice == "right")
{
   digitalWrite(12,HIGH);
  delay(700);
  digitalWrite(12,LOW);
  delay(700);
  digitalWrite (3,HIGH);
  digitalWrite (4,LOW);
  digitalWrite(12,HIGH);
  delay(800);
  digitalWrite(12,LOW);
  delay(800);
  digitalWrite (5,LOW);
  digitalWrite (6,HIGH);
  delay (1000);
  digitalWrite(3, HIGH);
  digitalWrite (4, HIGH);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
/*for(int i = 0; i <=2; i++)
{
  digitalWrite(12,HIGH);
  delay(800);
  digitalWrite(12,LOW);
  delay(800);
} */                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
//delay(100);
}

if ( readvoice == "left")
{
  digitalWrite(13,HIGH);
  delay(700);
  digitalWrite(13,LOW);
  delay(700);
  digitalWrite (3, LOW);
  digitalWrite (4, HIGH);
  digitalWrite(13,HIGH);
  delay(800);
  digitalWrite(13,LOW);
  delay(800);
  digitalWrite (5, HIGH);
  digitalWrite (6, LOW);
  delay (1000);
  digitalWrite(3, HIGH);
  digitalWrite (4, HIGH);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
/*for(int j = 0; j <=2; j++)
{
  digitalWrite(13,HIGH);
  delay(800);
  digitalWrite(13,LOW);
  delay(800);
} */             
//delay(100);
}

if (readvoice == "break")
{
digitalWrite(8, HIGH);
delay(300);
digitalWrite (3, LOW);
digitalWrite (4, LOW);
digitalWrite (5, LOW);
digitalWrite (6, LOW);
digitalWrite(8,LOW);
//digitalWrite(8, HIGH);
//delay(500);
//delay(100);
}

//voice = "";
}} //Reset the variable
