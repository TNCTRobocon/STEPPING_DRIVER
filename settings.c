
#include<xc.h>
#include "settings.h"
#include"inerrupt.h"
#include "timer.h"

int setup(){ 
    uart_setup();
    TRISA = 0x00;
    TRISB = 0b00001111;
    TRISC = 0b10000000;         //RC7?RX??
    OSCCON = 0b11110000;        // ????8MHz
    ANSELA = 0x00;
    ANSELB = 0x00;
    
    GIE=1;      // 1.全割り込み許可 0.許可しない

}