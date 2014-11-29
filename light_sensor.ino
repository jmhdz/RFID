/*Control a relay in pin 10, with a LDR in pin 0
to connect the sensor:
one leg of ldr to 5v the other to pin 0
a 1k resistor 1 leg to ground the other to pin 0*/


int LDR = 0; //analog pin to which ldr is connected
int relay = 10; //name pin 10 as relay
  int LDRValue; //light detector value
  int threshold = 50; // sensitivity threshold


void setup ()
{
  Serial.begin(9600); //begin serial at 9600 bauds
  pinMode(relay, OUTPUT); // set pin as output  int threshold = 50; // sensitivity threshold
}
void loop()
{
  LDRValue = analogRead(LDR); //read value from sensor
  Serial.println(LDRValue); // print it
  delay(100); //delay .01 sec
  if (LDRValue < threshold) // if LDR value its smaller than thrsld
  {
    digitalWrite(10, HIGH); //get pin 10 high
  }
  else //if not
  {
    digitalWrite(10, LOW); // get pin 10 low 
  }
}
