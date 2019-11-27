/*
* Test Code - 1
*
* The code here is just to show the working principle of the input of driver circuit
*/

void setup()
{
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop()
{
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  delayMicroseconds(100); // Approximately 10% duty cycle @ 1KHz
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delayMicroseconds(1000 - 100);
}
