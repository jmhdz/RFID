
/* Garage Timer
This sketch is meant to continuously monitor the status of the 
garage door. If it is opened, the sketch will wait 5 minutes to 
see if the garage door is still open. If it is still open, the relay 
will be activated in order to close the garage door. A red LED
(open_door_led) will also be lit if the Arduino has had to close
the garage door.
*/

#include <Time.h>

const long oneSecond = 1000;
const long oneMinute = oneSecond * 60;
int status_pin = 7;  // open (HIGH) or closed (LOW)

int operate_pin = 8;  // relay to open/close door
int open_door_led = 9; // LED to indicate door was left open today.

int door_count = 0; // Keep track of how many times the door has been left open.
int door = LOW;

void setup() 
{
  Serial.begin(9600);
  pinMode(status_pin, INPUT);

  pinMode(operate_pin, OUTPUT);
  pinMode(open_door_led, OUTPUT);
}

void loop()
{
  door = digitalRead(status_pin);
  
  if(door == LOW) // Door is closed.  Nothing to see here!
  {
    Serial.println("The door is closed.  Keep up the good work!");
    delay(10 * oneSecond);
  }
  else  // door is open
  {
    Serial.println("The door is open.  I'll give you 5 minutes to shut it!");
    delay(5 * oneMinute);  // giving you a chance to close door on your own.
    door = digitalRead(status_pin);
    if(door == LOW)
    {
      Serial.println("Good, you closed the door.  Whew!");
    }
    else
    {
      Serial.println("Looks like you forgot to close the garage door. Closing the door now.");
      digitalWrite(operate_pin, HIGH);  // Closing the door
      delay(100);
      digitalWrite(operate_pin, LOW); // Stop closing door
      door_count = door_count + 1;
      digitalWrite(open_door_led, HIGH);
      delay(20 * oneSecond);
      Serial.println("The door should be shut now.");
      Serial.print("The door has been left open ");
      Serial.print(door_count);
      Serial.println(" time(s).");
      delay(15000);
      door = digitalRead(status_pin);
      if(door == HIGH)
      {
        blockedOn();
      }
      else
      {
        loop();
      }
    }
  }
}

void blockedOn()
{
  digitalWrite(operate_pin, LOW);
}
