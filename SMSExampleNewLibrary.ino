
// include the GSM library
#include <GSM.h>

// PIN Number for the SIM
#define PINNUMBER "1234"//put your PIN here

// initialize the library instances
GSM gsmAccess;
GSM_SMS sms;

// Array to hold the number a SMS is retreived from
char senderNumber[20];

void setup() 
{
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  } 
  Serial.print("Powering on shield...");
  pinMode(9, OUTPUT); //pin 9 is shield power (normally HIGH requires a LOW for at least 400usec to toggle on/off)
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(50);
  digitalWrite(9, HIGH);
  Serial.println("done");
  //pin 8 is connected to shield reset if you need it...
  Serial.print("Starting GSM...");

  // connection state
  boolean notConnected = true;

  // Start GSM connection
  while(notConnected)
  {
    if(gsmAccess.begin(PINNUMBER)==GSM_READY)//remove PINNUMBER if your SIM doesn't need one just leave as begin()
      notConnected = false;
    else
    {
      Serial.print("not connected - resetting...");
      delay(1000);
    }
  }

  Serial.println("GSM initialized");
  Serial.println("Waiting for messages");
}

void loop() 
{
  char c;
  String message;

  // If there are any SMSs available()  
  if (sms.available())
  {
    Serial.println("Message received from:");

    // Get remote number
    sms.remoteNumber(senderNumber, 20);
    Serial.println(senderNumber);

    // An example of message disposal    
    // Any messages starting with # should be discarded
    if(sms.peek()=='#')
    {
      Serial.println("Discarded SMS");
      sms.flush();
    }

    // Read message bytes and print them
    while(c=sms.read()){
      message=message+c;
    }
    Serial.println("END OF MESSAGE");

    Serial.println(message);
    //Strings are easy to compare...char arrays require strcmp
    //replace +506xxxxxxxx with the telephone number of the authorized sender
    if(message=="mycommand" && strcmp(senderNumber, "+506xxxxxxxx")==0){
      Serial.println("Command received from authorized sender");
      Serial.print("[FreeMem]");
      Serial.println(freeRam());

      sms.beginSMS(senderNumber);
      sms.print("Command received");
      sms.endSMS();
      Serial.println("Message Sent...");


    }
    // Delete message from modem memory
    sms.flush();
    message="";
    Serial.println("MESSAGE DELETED");
  }

  delay(1000);

}
int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}





