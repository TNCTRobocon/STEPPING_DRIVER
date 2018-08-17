
/*
 * File:   newmain.c
 * Author: MORIYAMA
 *
 * Created on 2018/03/07, 10:55
 */


#include <xc.h>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include<stdbool.h>
#include <stdint.h>
#include<stddef.h>
#include<math.h>
#include "uart.h"
#include "settings.h"
#include"rotaion.h"
#include"timer.h"

// PIC16F1938 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable (All VCAP pin functionality is disabled)
#pragma config PLLEN = ON      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = HI        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), high trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ 8000000          //????8MHz

#define LED1 RA1
#define LED2 RA2
#define LED3 RA3
#define LED_SEL RA5
#define OFFSET 32

void main() {
    char line[32];
    char* argv[4],* title,* val;
    int argc;
    char* it;
    const char tokens[]=" ,";
    int address = (RB2*1+RB3*2+RB0*4+RB1*8);
    bool mode_sel=0;
    while(PLLR==0);
    setup();        //初期設定
    LED1 = 0;
    LED2 = 0;
    LED3 = 0;
    LED_SEL = 0;        //全LEDOFF
    while(1){
        if(uart_gets(line,sizeof(line))!=NULL){
            size_t len=strlen(line);
            if (line[len-1]=='!')continue;
            argv[0] = strtok(line,tokens);
            for (argc=1;argc<sizeof(argv)/sizeof(argv[0]);argc++){
                argv[argc]=it=strtok(NULL,tokens);
                if(it==NULL)break;
            }
            title=argv[0];
            val=argv[1];
            if(!strcmp(title,"sel")){
                int addr=0;
                if(argc>=2&&argv!=NULL)addr=atoi(val);
                if(addr==address)mode_sel=LED_SEL=1;
                else if(!addr){
                    mode_sel=1;
                    LED_SEL=0;
                }else mode_sel=LED_SEL=0;
            }else if(!strcmp(title,"right")){
                uart_send("right");
                right(val,0);
            }
            else if(!strcmp(title,"left")){
                uart_send("left");
                left(val,0);
            }else if(!strcmp(title,"echo")){
                for(int i=0;i<strlen(val);i++){
                    uart_send(val[i]);
                }
            }
         }
        }
}

