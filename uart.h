/* 
 * File:   uart.h
 * Author: MORIYAMA
 *
 * Created on 2018/03/10, 14:49
 */

#ifndef UART_H
#define	UART_H
#include<stddef.h>
#include<stdint.h>
void uart_setup();//
char uart_getc();//
char uart_putc(char);//
void uart_send(char data);
char* uart_gets(char* mem,size_t size);//
const char* uart_get(const char*);//
const char* uart_write(const char*,size_t);
char* uart_read(const char*,size_t);
void receive_isr(void);
size_t uart_received();//
inline void uart_flush();//
void TXInterrupt();//
void RXInterrupt();//
#endif	/* UART_H */

