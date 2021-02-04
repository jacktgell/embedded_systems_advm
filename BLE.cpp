#include "BLE.h"

uint8_t func = 0;
uint32_t command;
RawSerial device(PC_12, PD_2);
//set volatile so that it is only define once across files
volatile bool global = 0;

void initbt(void){
    //initiate bluetooth attach interupt
    device.attach(&callback);
}

void callback(){
    //detach interrupt
    device.attach(NULL);
    //let program know the buffer has a message by setting global = 1
    global = 1;
}

uint32_t poll(){
    if (global) {
        //get message
        command = BT();
        //message read set global flag low
        global = 0;
        //reattach blutooth serial interupt
        device.attach(&callback);
    }
    return command;
}

void flushSerialBuffer(void){ 
    char char1 = 0; 
    //empty buffer
    while (device.readable()){ 
        char1 = device.getc();
    } 
    return;
}

uint32_t BT(void){
    //define variables
    char        read[4];
    uint32_t    hold = 0;
    int i = 0;
    //if the device is readble else return the last known message
    if(device.readable()){
        while(i<4){
            while(device.readable()){
                read[i] = device.getc();
                i++;
            }
        }
        //bitshift back into a single variable
        hold = (read[3] << 24) + (read[2] << 16) + (read[1] << 8) + read[0];
        return hold;
        //clear anything in left in the serail buffer
        flushSerialBuffer();
    }
    return command;
}
