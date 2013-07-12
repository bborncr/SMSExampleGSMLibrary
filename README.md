SMSExampleGSMLibrary
====================

Example for using a SIM900 Shield with the Arduino built-in GSM library

The new built-in GSM library works well (at least with SMS messages) with the iComSat v1.1 shield.
This example tests sending and receiving of messages as well as responding to a command coming from an authorized sender.

The shield must be set for 9600 baud to use the GSM.  AT+IPR=9600 can be used to set the baud if need be.

CONFIGURATION:

Set your PIN number or if your SIM requires no PIN then remove PINNUMBER from the gsmAccess.begin(PINNUMBER) or the application will get stuck...just change it to gsmAccess.begin()

The example shows how the incoming SMS message can be stored in a String called message.  The incoming sending telephone number is stored in a char array called senderNumber and compared using strcmp().

USAGE:

The message from any phone gets printed out in the serial monitor.
Sending the message "mycommand" from the authorized phone returns a message back to sender stating "Command received" and also prints a message to the serial monitor.
