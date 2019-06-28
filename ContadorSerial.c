#include <18F4620.h>
#fuses HS,NOWDT,NOMCLR
#use delay(clock=16 MHZ)

//Aqui deben ir las interfaces tales como la rs-232, I^2C

#define MaxTam 10

#define _DEBUG_SERIAL_
#ifdef _DEBUG_SERIAL_
   #define TX_232    PIN_C6
   #define RX_232    PIN_C7
   #use RS232(BAUD=9600,XMIT=TX_232,BITS=8,PARITY=N,STOP=1,UART1,RCV=RX_232)
   #use fast_io(c)
#endif
//Aqui deben ir la IsR's interrupciones

char IndiceBuffer=0;
int  FlagSerial;
char Buffer[MaxTam];

#INT_RDA
void isrRDA (void) {            
   Buffer[IndiceBuffer]=getc();
   FlagSerial = 1;
   IndiceBuffer++;
   if(IndiceBuffer>MaxTam){
   IndiceBuffer=0;
   }
}
   //int_timer0

//variables globales

//aqui el void main(void)
void main(void){
   set_tris_c(0x80);
   set_tris_a(0x00);
   set_tris_b(0x00);
   set_tris_d(0x00);
while(1){
      
}
}

