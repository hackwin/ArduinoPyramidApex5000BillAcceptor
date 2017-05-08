//Pyramid Technologies APEX Series 5000 Bill Acceptor
//By Jesse Campbell, www.jbcse.com
//Configuration info: http://imgur.com/a/NWwfP
//2017-05-08
//Requires library: http://gammon.com.au/Arduino/ReceiveOnlySoftwareSerial.zip

#include <Arduino.h>
#include <Apex5400BillAcceptor.h>

#define PIN_ENABLE 7 //Purple wire, to enable set low, to disable set high
#define PIN_INTERRUPT_LINE 8 //Orange wire on Apex, Request to send data to host
#define PIN_SEND_LINE 9 //White/Blue wire, Host Ready Signal
#define PIN_TTL_RX 10 //Green wire, Transmit Data Line from acceptor

Apex5400BillAcceptor *billAcceptor;
int code;

void setup() {
  Serial.begin(9600);  
  billAcceptor = new Apex5400BillAcceptor(PIN_ENABLE, PIN_INTERRUPT_LINE, PIN_SEND_LINE, PIN_TTL_RX);    
  //billAcceptor->disable();
  //billAcceptor->toggle();
  //billAcceptor->enable();
}

void loop() {
  if(code = billAcceptor->checkForBill()){
    Serial.print("Code: 0x");
    Serial.print(code, HEX);
    Serial.print(", Description: ");
    Serial.println(billAcceptor->getDescription(code));
  }
}