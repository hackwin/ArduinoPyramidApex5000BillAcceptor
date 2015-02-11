//Pyramid Technologies APEX Series 5000 Bill Acceptor
//Arduino Library
//By Jesse Campbell, www.jbcse.com
//Configuration info: http://imgur.com/a/KHgPG, http://i.imgur.com/b6bOSuH.jpg
//2014-11-15

#include <ReceiveOnlySoftwareSerial.h>
//http://gammon.com.au/Arduino/ReceiveOnlySoftwareSerial.zip

#define PIN_TTL_RX 10 //Green wire, Transmit Data Line from acceptor
#define PIN_INTERRUPT_LINE 4 //Orange wire on Apex, Request to send data to host
#define PIN_SEND_LINE 5 //White/Blue wire, Host Ready Signal

ReceiveOnlySoftwareSerial mySerial(PIN_TTL_RX); // RX

struct codeMap{
  int code;
  String description;
};

const int codeCount = 13;
codeMap codes[codeCount];

void setup()  
{
  Serial.begin(115200);
  while (!Serial) { }  // wait for Serial to become available

  // set the data rate for the ReceiveOnlySoftwareSerial port
  mySerial.begin(600);
  digitalWrite(PIN_TTL_RX, HIGH); //internal pull-up required
    
  codes[0].code = 0x81;
  codes[0].description = "$1 Credit";
  codes[1].code = 0x82;
  codes[1].description = "Not Used";
  codes[2].code = 0x83;
  codes[2].description = "$5 Credit";
  codes[3].code = 0x84;
  codes[3].description = "$10 Credit";
  codes[4].code = 0x85;
  codes[4].description = "$20 Credit";
  codes[5].code = 0x86;
  codes[5].description = "$50 Credit";
  codes[6].code = 0x87;
  codes[6].description = "$100 Credit";
  codes[7].code = 0x88;
  codes[7].description = "Reserved";
  codes[8].code = 0x89;
  codes[8].description = "Vend";
  codes[9].code = 0x8A;
  codes[9].description = "Return";
  codes[10].code = 0x8B;
  codes[10].description = "Reject";
  codes[11].code = 0x8C;
  codes[11].description = "Failure";
  codes[12].code = 0x8D;
  codes[12].description = "Full or Jam";
  
  pinMode(PIN_INTERRUPT_LINE, INPUT);
  pinMode(PIN_SEND_LINE, OUTPUT);
}

void loop() // run over and over
{
  
  if (digitalRead(PIN_INTERRUPT_LINE) == LOW){
    digitalWrite(PIN_SEND_LINE, LOW);
    digitalWrite(PIN_SEND_LINE, HIGH);  
  }
  
  long start = millis();
  
  while(millis() < start+5)
  if (mySerial.available()){
  	
    int codeFromBillAcceptor = mySerial.read();
    //Serial.println(codeFromBillAcceptor, HEX);
        
    for(int i=0; i<codeCount; i++)
      if (codes[i].code == codeFromBillAcceptor){
      	//Serial.print(millis());
        Serial.println(codes[i].description);
      }
  }
  
}
