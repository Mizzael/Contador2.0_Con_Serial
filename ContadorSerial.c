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
#INT_RDA
void isrRDA (void) 
{            
   
}
   //int_timer0

//variables globales

//aqui el void main(void)
void main(void)
{
   set_tris_a(0x00);
   set_tris_b(0x00);
   set_tris_d(0x00);
   
   int ContadorAnilloPortB=0x01;
   int ContadorAnilloPortC=0x80;
   int ContadorAnilloPortD=0x03;
   
   int FlagContador1=0;
   int FlagContador2=0;
   int FlagContador3=0;

while(1){
   
   int Opcion=input_a();
   
    if((Opcion&0x09)>0x00){
      FlagContador1=1;
   }
   else{
      FlagContador1=0;
   }
   
   if((Opcion&0x12)>0x00){
      FlagContador2=1;
   }
   else{
      FlagContador2=0;
   }
   
   if((Opcion&0x24)>0x00){
      FlagContador3=1;
   }
   else{
      FlagContador3=0;
   }
   
   if(FlagContador1==1){
      ContadorAnilloPortB=ContadorAnilloPortB<<1;
      if(ContadorAnilloPortB==0x80){
         ContadorAnilloPortB=0x01;
      }
   }
   
   if(FlagContador2==1){
      ContadorAnilloPortC=ContadorAnilloPortC>>1;
      if(ContadorAnilloPortC==0x00){
         ContadorAnilloPortC=0X80;
      }
   }
   
   if(FlagContador3==1){
      ContadorAnilloPortD=ContadorAnilloPortD<<2;
      if(ContadorAnilloPortD==0xC0){
         ContadorAnilloPortD=0x03;
      }
   }
   
   output_b(ContadorAnilloPortB);
   output_c(ContadorAnilloPortC);
   output_d(ContadorAnilloPortD);
   delay_ms(100);
}
}

