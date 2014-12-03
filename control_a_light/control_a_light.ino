//simple button GET server code to control servo and arduino pin 5
//for use with IDE 1.0
//open serial monitor to see what the arduino receives
//use the \ slash to escape the " in the html 
//for use with W5100 based ethernet shields
//Powering a servo from the arduino usually DOES NOT WORK.
//note that the below bug fix may be required
// http://code.google.com/p/arduino/issues/detail?id=605 
//
//upload this sketch to your Arduino: http://pastebin.com/sL0pVr2v
//
//After, plug in your ethernet cable, and power on your Arduino.
//
//Next, go to the IP Address: 192.168.1.177 and turn on and off the LED!
//-----------------------------------------------------------------------------------------------------------------------------------
//To port forward this go to your router settings (usually 192.168.1.1, otherwise look in CMD and type in ipconfig) and click on Applications and Gaming.
//
//Next, type in 192.168.1.177 and select TCP as the protocol. The ports are 80.
//
//Afterwards, go to http://www.whatismyip.com/ and type in your IP into the address bar.

#include <SPI.h>
#include <Ethernet.h>

#include <Servo.h> 
Servo myservo;  // create servo object to control a servo 

byte mac[] = { 0xDE, 0xAB, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address
byte ip[] = { 10, 0, 0, 50 }; // ip in lan
byte gateway[] = { 192, 168, 1, 254 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
EthernetServer server(22); //server port

String readString; 

//////////////////////

void setup(){

  pinMode(6, OUTPUT); //pin selected to control
  //start Ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  //the pin for the servo co
  //enable serial data print 
  Serial.begin(9600); 
  Serial.println("server LED test 1.0"); // so I can keep track of what is loaded
}

void loop(){
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100) {

          //store characters to string 
          readString += c; 
          //Serial.print(c);
        } 

        //if HTTP request has ended
        if (c == '\n') {

          ///////////////
          Serial.println(readString); //print to serial monitor for debuging 

          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();

          client.println("<HTML>");
          client.println("<HEAD>");
          client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
          client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
          client.println("<link rel='stylesheet' type='text/css' href='http://chriscosma.co.cc/a.css' />");
          client.println("<TITLE>Home Automation</TITLE>");
          client.println("</HEAD>");
          client.println("<BODY>");
          client.println("<H1>Home Automation</H1>");
          client.println("<hr />");
          client.println("<br />");
          
          client.println("<a href=\"/?lighton\"\">Turn On Light</a>"); 
          client.println("<a href=\"/?lightoff\"\">Turn Off Light</a><br />");         
 
          client.println("</BODY>");
          client.println("</HTML>");
 
          delay(1);
          //stopping client
          client.stop();

          ///////////////////// control arduino pin
          if(readString.indexOf("?lighton") >0)//checks for on
          {
            digitalWrite(6, HIGH);    // set pin 4 high
            Serial.println("Led On");
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/on.png' />");
          }
          else{
          if(readString.indexOf("?lightoff") >0)//checks for off
          {
            digitalWrite(6, LOW);    // set pin 4 low
            Serial.println("Led Off");
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/off.png' />");
          }
          }
          //clearing string for next read
          readString="";

        }
      }
    }
  }
}