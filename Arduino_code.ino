#include <SoftwareSerial.h>
SoftwareSerial mySerial(5, 4);
char temp = '0';
// Variable initialization
int xpin = A5;
int xadc = 0;
int ypin = A6;
int yad = 0;
// Flex sensor pins
int FLEX_PIN1 = A0;
int flexADC1 = 0;
int sensorMin1 = 1023;
int sensorMax1 = 0;
int FLEX_PIN2 = A1;
int flexADC2 = 0;
int sensorMin2 = 1023;
int sensorMax2 = 0;
void setup()
{
mySerial.begin(9600);
while (!Serial)
{
; // Wait for serial port to connect. Needed for native USB port only
}
// Calibrating the sensors for adaptivity with different bends
while (millis() < 15000)
{
if (digitalRead(7) == HIGH)
{
flexADC1 = analogRead(FLEX_PIN1);
flexADC2 = analogRead(FLEX_PIN2);
if (flexADC1 < sensorMin1) sensorMin1 = flexADC1;
if (flexADC1 > sensorMax1) sensorMax1 = flexADC1;
if (flexADC2 < sensorMin2) sensorMin2 = flexADC2;
if (flexADC2 > sensorMax2) sensorMax2 = flexADC2;
}
}
}
void printfun(char cp) // To avoid printing repeating symbols
{
if (cp != temp)
{
mySerial.print(cp);
temp = cp;
}
}
void loop()
{
// Reading sensor values
flexADC1 = analogRead(FLEX_PIN1);
flexADC2 = analogRead(FLEX_PIN2);
flexADC1 = constrain(flexADC1, sensorMin1, sensorMax1);
flexADC2 = constrain(flexADC2, sensorMin2, sensorMax2);
float angle1 = map(flexADC1, sensorMin1, sensorMax1, 0, 90);
float angle2 = map(flexADC2, sensorMin2, sensorMax2, 0, 90);
xadc = analogRead(xpin);
yad = analogRead(ypin);
// Conditions for printing characters based on sensor angles
if ((angle1 >= 70) && (angle1 <= 82) && (angle2 >= 77) && (angle2 <= 95))
printfun('A');
if ((angle1 >= 0) && (angle1 <= 10) && (angle2 >= 0) && (angle2 <= 10))
printfun('B');
// Add more conditions as needed for the new setup...
delay(200);
}
