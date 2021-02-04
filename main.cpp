#include "signal_generator.h"
#include "BLE.h"
#include "Oscilliscope.h"
#include "mbed.h"

Timer test;
DigitalOut test_R(D15);
DigitalOut test_C(D14);

int main() {
    initbt();
    init_arduino_comms();
    printf("boot\r\n");
    //define variable for this scope
    uint8_t frequency = 0;
    uint8_t wave = 0;
    uint8_t voltage = 0;
    uint8_t multiplier = 0;
    uint32_t change = 0;

    //start watchdog
    IWDG_HandleTypeDef hiwdg;
    hiwdg.Instance = IWDG;
    hiwdg.Init.Prescaler = IWDG_PRESCALER_256; 
    hiwdg.Init.Reload = 1000;  
    //watchdog refresh rate at (256*1000)/(32*10^3)  = 8 seconds   
    //spin while no message has been recieved
    while(command==0){         
        //reset watchdog
        HAL_IWDG_Init(&hiwdg);
        //check for message
        poll();
    }
    //debug
    printf("%d\r\n",(command>>24)&0xFF);


    while(1){
        //check message
        poll();
        //debug
        if(command!=change){
            change = command;
            printf("wave = %X   voltage = %X   multiplier = %X   freq = %X   command = %X\r\n",wave,voltage,multiplier,frequency,command);
        }

        //if byte 4 == 1 generate a signal
        if(((command>>24)&0xFF)==1)
            Signal_Gen();
        //if byte 4 == 2 sample signal
        if(((command>>24)&0xFF)==2){
            Read_Send_Signal();}

        //tell arduino to test resistor
        while(((poll()>>24)&0xFF)==3){
            //reset watchdog
            HAL_IWDG_Init(&hiwdg);
            test_R = 1;
        }
        if(test_R == 1)
            test_R = 0;

        //tell arduino to test capacitor
        while(((poll()>>24)&0xFF)==4){      
            //reset watchdog    
            HAL_IWDG_Init(&hiwdg);
            test_C = 1;
        }
        if(test_C == 1)          
            test_C = 0;
        
    }
}