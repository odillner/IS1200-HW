#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

volatile int* TRISE_ADR = (int*) 0xBF8860D0;

int getsw(void){
    return (*TRISE_ADR>>8)&(0xf);
}
int getbtns(void){
    return (*TRISE_ADR>>5)&(0x7);
}