#ifndef BLE
#define BLE

#include "mbed.h"

extern uint32_t command;
extern Mutex comm_mutex;

uint32_t BT(void);
void flushSerialBuffer(void);
void initbt(void);
void callback(void);
uint32_t poll(void);

#endif