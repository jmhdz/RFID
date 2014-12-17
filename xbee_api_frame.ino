int led = 13;                           //  set pin 13 as led

void setup() {                          //  start setup
pinMode(led, OUTPUT);                   //  set led as output
Serial.begin(9600);                     //  Start serial comm
}

void loop() {
  digitalWrite(led, HIGH);               // turn on led
  setRemoteState(0x5);
  delay(5000);
  digitalWrite(led, LOW);
  setRemoteState(0x4);
  delay(5000);
}

void setRemoteState(char value) {
  Serial.write(0x7E);                      //  start byte
  Serial.write((byte)0x00);                //  high part of lenght (always zero);
  Serial.write(0x10);                      //  low part of lenght (the number of bytes that follow)
  Serial.write(0x17);                      //  0X17 is a remote AT command
  Serial.write((byte)0x00);                //  frame id set to zero for no replay
  
                                           //  ID or recipient, or use 0xFFFF for broadcast
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);
  Serial.write(0xFF);
  Serial.write(0xFF);                       //  0xFF for broadcast
  
  //16 bits of recipient or 0xFFFE
  
  Serial.write(0xFF);
  Serial.write(0xFE);
  
  Serial.write(0x02);                        //  0x02 to apply changes immediatly
  
  //command name in ASCII characters
  Serial.write('D');
  Serial.write('3');
  
  //command data in as many bytes as needed
  Serial.write(value);
  
  //checksum is all bytes after lenght
  long sum = 0x17 + 0xFF + 0xFF + 0xFF + 0xFE + 0x02 + 'D' + '3' + value;
  Serial.write ( 0xFF - ( sum & 0xFF));   // calculate the checksum
}
