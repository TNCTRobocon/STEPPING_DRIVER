#include<xc.h>
#include<stdbool.h>
#include"uart.h"
void interrupt isr(){
    if(TMR0IF){
        //関数の作成
        TMR0IF = false;
    }
    if(RCIF){
        RA1=!RA1;
        receive_isr();
        RCIF = 0;
    }
}