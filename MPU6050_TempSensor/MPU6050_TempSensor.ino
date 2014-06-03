
#include <Wire.h>
#include <MPU6050.h>

#include <Nokia5110.h>


#define PIN_LED 3
int t = 1500;


Nokia5110 *nok;
MPU6050 * mpu;

void setup(void)
{
  pinMode(PIN_LED, OUTPUT);

  nok = new Nokia5110(8, 7, 6, 5, 4, 5);
  nok->begin();
  nok->Clear();
  nok->WriteString("Hello World!");

    mpu = new MPU6050();
    mpu->begin();



}

int i = 0;

void loop(void)
{

  t--;
  nok->ClearGoToBegin();
//  nok->WriteString(String(t));
//  nok->WriteString(" "); 
  nok->WriteString(String(mpu->Temperature,4));
  
  i = 1 - i;

  digitalWrite(PIN_LED, i);
  delay(1000);
  mpu->read();
  delay(100);

}

