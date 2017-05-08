#include <ReceiveOnlySoftwareSerial.h> //http://gammon.com.au/Arduino/ReceiveOnlySoftwareSerial.zip
#include <Arduino.h>

#ifndef APEX5400BILLACCEPTOR_H
#define APEX5400BILLACCEPTOR_H

struct codeMap{
	int code;
	char description[12];
};

class Apex5400BillAcceptor{
	
	private:
		int pin_enable_line;
		int pin_interrupt_line;
		int pin_send_line;		
		int pin_ttl_rx;

		struct codeMap codes[13] = {
			{0x81, "$1 Credit"},
			{0x82, "Not Used"},
			{0x83, "$5 Credit"},
			{0x84, "$10 Credit"},  
			{0x85, "$20 Credit"},  
			{0x86, "$50 Credit"},  
			{0x87, "$100 Credit"},    
			{0x88, "Reserved"},      
			{0x89, "Vend"},      
			{0x8A, "Return"},      
			{0x8B, "Reject"},      
			{0x8C, "Failure"},      
			{0x8D, "Full or Jam"}
		};
		
	public:
		ReceiveOnlySoftwareSerial *mySerial;
		Apex5400BillAcceptor(int a, int b, int c, int d){
			
			pin_enable_line = a;
			pinMode(pin_enable_line, OUTPUT);
			digitalWrite(pin_enable_line, LOW);
			
			pin_interrupt_line = b;						
			pinMode(pin_interrupt_line, INPUT);
			
			pin_send_line = c;
			pinMode(pin_send_line, OUTPUT);					
			
			pin_ttl_rx = d;
			pinMode(pin_ttl_rx, INPUT_PULLUP);
			mySerial = new ReceiveOnlySoftwareSerial(pin_ttl_rx);
			mySerial->begin(600);
		}
	
		int checkForBill(){
			if (digitalRead(pin_interrupt_line) == LOW){
				digitalWrite(pin_send_line, LOW);
				digitalWrite(pin_send_line, HIGH);  

				delay(5);
				
				if (mySerial->available()){
					int code = mySerial->read();					
					return code;
				}
			}
			return 0;
		}
		
		char* getDescription(int codeFromBillAcceptor){
			for(int i=0; i < sizeof(codes)/sizeof(codes[0]); i++){
				if (codes[i].code == codeFromBillAcceptor){
					return codes[i].description;
				}
			}
			return "(code undefined)";
		}
		
		void enable(){
			digitalWrite(pin_enable_line, LOW);
		}
		
		void disable(){
			digitalWrite(pin_enable_line, HIGH);
		}
		
		void toggle(){
			digitalWrite(pin_enable_line, !digitalRead(pin_enable_line));
		}
	
};
#endif