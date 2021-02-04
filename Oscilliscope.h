#ifndef OSCILLI
#define OSCILLI

#include "mbed.h"

void chip_select(uint8_t bit);
void init_arduino_comms(void);
void Read_Send_Signal(void);
void Send_Byte(uint8_t byte);
void B1(bool write);
void F1(bool write);
bool F2();

#endif