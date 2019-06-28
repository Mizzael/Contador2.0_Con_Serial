#include <18F4620.h>
#fuses HS,NOWDT,NOMCLR
#use delay(clock=16 MHZ)

//Aqui deben ir las interfaces tales como la rs-232, I^2C

#define _DEBUG_SERIAL_
#ifdef _DEBUG_SERIAL_
   #define TX_232    PIN_C6
   #define RX_232    PIN_C7
   #use RS232(BAUD=9600,XMIT=TX_232,BITS=8,PARITY=N,STOP=1,UART1,RCV=RX_232)
   #use fast_io(c)
#endif
//Aqui deben ir la IsR's interrupciones

int  FlagSerial;
char Dato;

#INT_RDA
void isrRDA (void) {            
   Dato=getc();
   FlagSerial=1;   
}   
//int_timer0

//aqui el void main(void)
void main(void){
   set_tris_c(0x80);
   set_tris_a(0x00);
   set_tris_b(0x00);
   set_tris_d(0x00);
   enable_interrupts(global);
   enable_interrupts(int_rda);
   
   int ContadorA=0x01;
   int ContadorB=0x80;
   int ContadorD=0x03;
   
   int FlagContador1=0;
   int FlagContador2=0;
   int FlagContador3=0;
   
   
while(1){
      if(FlagSerial==1){
         putc(Dato);
         FlagSerial=0;
         if((Dato&0x09)>0x00){
            FlagContador1=1;
         }
         else{
            FlagContador1=0;
         }
         
         if((Dato&0x12)>0x00){
            FlagContador2=1;
         }
         else{
            FlagContador2=0;
         }
         
         if((Dato&0x24)>0x00){
            FlagContador3=1;
         }
         else{
            FlagContador3=0;
         }
         
         if(FlagContador1==1){
            ContadorA=ContadorA<<1;
            if(ContadorA==0x80){
                  ContadorA=0x01;
            }
         }
         if(FlagContador2==1){
            ContadorB=ContadorB>>1;
            if(ContadorB==0x01){
               ContadorB=0x80;
            }
         } 
         if(FlagContador3==1){
            ContadorD=ContadorD<<2;
            if(ContadorD==0xC0){
               ContadorD=0x03;
            }
         }
      }
      output_a(ContadorA);
      output_b(ContadorB);
      output_d(ContadorD);
      delay_ms(100);
   }
}

