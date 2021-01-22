#include <Arduino.h>

#define ledStat 36
#define ledStat2 38

typedef enum {
   Idle,
   StartUp
} State;

void setup()
{
    Serial.begin(9600);//begin serial communication for the serial monitor
    while(!Serial)
    {
        ;//wait until Serial connects
    }
    Serial.println("Serial connection opened");

    Serial1.begin(9600);//begin serial connunication for the Xbee 
    while(!Serial1)
    {
        ;//wait until Serial1 connects
    }
    Serial.println("Serial 1 connection opened");
}

void loop()
{
    String logData, modeData;

    if(Serial1.available())//if statement b/c the entire thing is already in a loop. Will allow the mode to be changed during reading
    {
        logData = Serial1.readStringUntil('\n');
        //logData += "\n";
        if(logData != "")
        {
            Serial.println(logData);//sends the logged data from SCA to the GUI. Should be sending a zero terminator then new line at the end
        }
        logData = "";
    }
    
    //if(Serial2.available())//reads current state from the GUI, then executes some tasks accordingly
    if(Serial.available())
    {
        char currState = Serial2.read();
        switch(currState){
            case '0':{
                Serial1.print('a');//sending the mode to the xbee for transmission
                Serial.println("sent Idle command");
                break;
            }
            case '1':{
                Serial1.print('b');//sending the mode to the xbee for transmission
                Serial.println("sent Start up command");
                break;
            }
            default:{
                Serial.println("ERROR");
                break;
            }
        }
    }

}