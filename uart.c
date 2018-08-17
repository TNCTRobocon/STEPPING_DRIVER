#include"uart.h"
#include <xc.h>
#include<string.h>
#include<stddef.h>
#include<stdint.h>
#include<stdbool.h>
#define RX_BUFFER_SIZE 32
#define TX_BUFFER_SIZE 32
static char rxbuf[RX_BUFFER_SIZE];
static char rx_in,rx_out,rx_used;
static char txbuf[TX_BUFFER_SIZE];
static char tx_in,tx_out,tx_used;

void uart_setup(){
    //管理領域初期化
    memset(rxbuf,0,sizeof(rxbuf));
    rx_in = 0;
    rx_out = 0;
    rx_used = 0;
    
    SPBRG = 42;
//    BRGH = 0;
    RCSTA  = 0b10010000;        // UART受信有効
    TXSTA  = 0b00100000;        // UART送信有効
    
    RCIF = 0;                   //?????????
    RCIE = 1;                   //??????????
    PEIE = 1;                   //??????????
    
    TXIE = 1;                   //送信割り込み有効
    TXIE = 1;                   //送信有効
    TXIF = 0;                   //フラグリセット   
}

size_t uart_received(){
    return rx_used;
}

char uart_getc(){
    uint8_t result = 0;
    if(rx_used > 1){
        result = rxbuf[rx_out];
        rx_out = (rx_out+1)%RX_BUFFER_SIZE;
        rx_used--;
    }
    return result;
}

inline char uart_bufc(char c) {
    txbuf[tx_in] = c;
    tx_in = (tx_in + 1) == TX_BUFFER_SIZE ? 0 : tx_in + 1;
    tx_used++;
    return c;
}

inline char uart_bufnl(){
    return uart_bufc('\r');
}

char uart_putc(char c){
    if(tx_used + 1 < TX_BUFFER_SIZE){
        uart_bufc(c);
        uart_flush();
        return c;
    }else{
        return '\0';
    }
}

inline void uart_flush(){
    if(TXIE){
        while(tx_used > 0){
            TXREG = txbuf[tx_out];
            tx_out = (tx_out+1) == TX_BUFFER_SIZE ? 0 : tx_out +1;
            tx_used--;
        }
        TXIE = true;
    }
    while(tx_used > (TX_BUFFER_SIZE >> 2));
}

static size_t find(void){
    uint8_t idx;
    uint8_t tail=(rx_out+rx_used)%RX_BUFFER_SIZE;
    uint8_t it;
    size_t size=0;
    for (idx=rx_out;idx!=tail;idx=(idx+1)%RX_BUFFER_SIZE){
        it=rxbuf[idx];
        size++;
        if(it=='\n'||it=='\r')return size;
    }
    return 0;
}

char* uart_gets(uint8_t* mem,size_t size){
    size_t pos=find();
    uint8_t *it=mem;
    if(0<pos && pos<size){
        uint8_t idx;
        uint8_t tail=(rx_out+pos)%RX_BUFFER_SIZE;
        for (idx=rx_out;idx!=tail;idx=(idx+1)%RX_BUFFER_SIZE){
            *(it++)=rxbuf[idx];
        }
        it--;
        *it='\0';
        rx_in=rx_out=rx_used=0;
        return mem;
    }else{
        return NULL;
    }
}

const char* uart_get(const char*){
    register char *c;
    if(rx_used > 0){
        c = &rxbuf[rx_out];
        rx_out = (rx_out + 1) == RX_BUFFER_SIZE ? 0 : rx_out + 1;
        rx_used--;
    }else{
        c = '\0';
    }
return c;
}

void receive_isr(void){
    uint8_t temp;
    temp=RCREG;
    if (rx_used<RX_BUFFER_SIZE) {
        rxbuf[rx_in]=temp;
        rx_in=(rx_in+1)%RX_BUFFER_SIZE;
        rx_used++;
    }
    RCIF=0;
    return;
}

void RXInterrupt(){
    char c;
    c = RCREG;
        if(rx_used < RX_BUFFER_SIZE){
            rxbuf[rx_in] = c;
            rx_used ++;
            rx_in = (rx_in + 1) == RX_BUFFER_SIZE ? 0 : rx_in + 1;  
        }else{
        }
    RCIF = false;
}

void TXInterrupt(){
    while(txbuf == false){
        TXREG = txbuf[tx_out];
        tx_out = (tx_out + 1) == TX_BUFFER_SIZE ? 0 : tx_out + 1;
        tx_used--;
    }
    TXIE = tx_used > 0;
    TXIF = false;
}

void uart_send(char data){
    while(!TXIF);
    TXREG=data;
    return;
}