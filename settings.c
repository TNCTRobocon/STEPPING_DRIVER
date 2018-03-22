
#include<xc.h>
#include "settings.h"
#include"inerrupt.h"
#include "timer.h"

int setup(){ 
    uart_setup();
    TRISA = 0x00;
    TRISB = 0b00001111;
    TRISC = 0b10000000;         //RC7?RX??
    OSCCON = 0b01110000;        // ????8MHz
    ANSELA = 0x00;
    ANSELB = 0x00;
    
    T0CS=1;     // 0.内部クロック  1.外部クロック
    PSA=0;      // プリスケーラ WDT.1  TMR0.0  最大65,536
    PS0=1;      // プリスケーラの比を設定
    PS1=1;      // 000: 1 : 2 ,001: 1 : 4 ,010; 1 : 8 ,  011: 1 : 16 ,
    PS2=1;      // 100: 1 : 32,101: 1 : 64,110: 1 : 128, 111: 1 : 256
    TMR0=0;     // 記入カウント値=２５６-必要なカウント値
    T0IE=1;     // 1.割り込み許可　 0.許可しない
    T0IF=0;     // フラグを消す
    GIE=1;      // 1.全割り込み許可 0.許可しない

}