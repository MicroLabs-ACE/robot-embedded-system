#include <SoftwareSerial.h>

SoftwareSerial Serial_1(D6, D5); //Rx and Tx

void setup()  
{
  Serial_1.begin(9600);
} 

void loop()  
{ 
  Serial_1.write("hello arduino");
  delay(2000);
}