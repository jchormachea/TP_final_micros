/***************************************************************************//**
 @file     display.c
 @brief    display control
 @author   Conradeus
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "UART.h"
#include "cqueue.h"
#include "common.h"
#include "board.h"
#include "timer.h"
#include "hardware.h"
#include "gpio.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define RX_FULL  UCA0RXIFG
#define TX_EMPTY UCA0TXIFG
#define RX_BUFFER UCA0RXBUF
#define TX_BUFFER UCA0TXBUF

#define UART_DELAY_MS 10
#define MAX_SCALE 255
#define MAX_VOLTAJE 3300

#define NEW_LINE 10 //ASCII for new line
#define MAX_MESSAGES 15
#define FINISH_MESSAGE 13//ASCII for finish transmition
//type of messages
enum {RAW_MESSAGE, VOLTAGE_MESSAGE};



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static void uart_put_char(char);
static int getTXStatus(void);

static void uart_send_message(void);
static void print_voltage(unsigned long);

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

//unsigned char uart_message;
unsigned long uart_message;
//char hexString[3]

/*******************************************************************************
 *******************************************************************************
 GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void uart_init(void){

    QueueInit();
    //PIN1.1 Configure UART mode(Rx)
    P1SEL |= PIN_UART_RX;
    P1SEL2 |= PIN_UART_RX;

    //PIN1.2 Configure UART mode(Tx)
    P1SEL |= PIN_UART_TX;
    P1SEL2 |= PIN_UART_TX;

    UCA0CTL1 = UCSWRST; //Reset state


    UCA0CTL0 &= ~UCPEN; //parity not enabled
    UCA0CTL0 &= ~UCMSB; //LSB first
    UCA0CTL0 &= ~UC7BIT; //8 bits character
    UCA0CTL0 &= ~UCSPB; //one stop bit

    UCA0CTL1 |= UCSSEL_2; // SMCLK

    //set baudRate to 9600 for 8MHz clock
    //UCA0BR0 = 833 & 0xFF;
    //UCA0BR1 = 833 >> 8;
    UCA0BR0 = 65; //
    UCA0BR1 = 3; // (UCA0BR0+256*UCA0BR1) = 833
    UCA0MCTL = UCBRS1; // USCI Second Stage Modulation Select 1

    UCA0CTL1 &= ~UCSWRST; //dissabled reset start

    IE2 |= UCA0RXIE; //enable rx interrupts


}

void uart_set_message(unsigned long value){
    
    uart_message = value;
    
}

/*******************************************************************************
 LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/




static void uart_put_char(char message){

    while(getTXStatus()!=TX_EMPTY); // USCI_A0 TX buffer ready?
    
    TX_BUFFER = message;


}

static int getTXStatus(void)
{
    return (IFG2 & TX_EMPTY);
}

char getChar(void)
{
    unsigned char rxdata;
    PullQueue(&rxdata);
    return rxdata;
}

int getRXStatus(void)
{
    return(QueueStatus());

}



#pragma vector=USCIAB0RX_VECTOR
__interrupt void uart_rx_isr(void) {
    if (IFG2 & RX_FULL) {   // Comprobar si el flag RXIFG está activo
    PushQueue(RX_BUFFER);    
    IFG2 &= ~RX_FULL;    // bajo el flag
    }
}




/******************************************************************************/

