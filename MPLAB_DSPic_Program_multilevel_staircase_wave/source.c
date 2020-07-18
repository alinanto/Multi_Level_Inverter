#define    FCY    20000000UL
#include "xc.h"
#include "header.h"
#include <libpic30.h>

/*
unsigned int i=0;
int flag=1;
float DUTY=0;

 void __attribute__((interrupt,auto_psv)) _PWMInterrupt(void)
{
 if(flag) 
 {
     i+=5; 
     DUTY = (float)10000.00+(float)10000.00*sin((float)(3.14159)*((float)i/20000.00));
 }
 else     
 {
     i-=5; 
     DUTY = (float)10000.00-(float)10000.00*sin((float)(3.14159)*((float)i/20000.00));
 }
 if(i == 0 || i == 20000) flag = !flag; 
 PDC1= PDC2= PDC3= (int)DUTY;
 IFS2bits.PWMIF = 0;
}
*/

int main(void) {
    
    
   TRISE= 0x0000; 
   TRISC= 0x0000;
   LATC= 0;
   LATE= 0; 
   
   
   /*PTCONbits.PTOPS= 0b0000; //Time base Output Prescaler
                            //1111 1:16
                            //
                            //0000 1:1
   
   
   PTCONbits.PTCKPS = 0b00; //Time base Input Clock Prescaler
                            //11 64 Tcy
                            //10 16 Tcy
                            //01 04 Tcy
                            //00 01 Tcy
   
   PTCONbits.PTMOD= 0b00; //Time base Mode
                          //11 Up/Down double interupt
                          //10 Up/Down
                          //01 single event
                          //00 Free running
   
   PTPERbits.PTPER = 10000; // Time Base
      
   PWMCON1bits.PMOD1 = 0b0; //OUTPUT PAIR MODE
   PWMCON1bits.PMOD2 = 0b0; //1 independent
   PWMCON1bits.PMOD3 = 0b0; //0 complementary
   
   PWMCON1bits.PEN1H = 0b1; //OUTPUT PIN ENABLE
   PWMCON1bits.PEN2H = 0b1;
   PWMCON1bits.PEN3H = 0b1;
   PWMCON1bits.PEN1L = 0b1;
   PWMCON1bits.PEN2L = 0b1;
   PWMCON1bits.PEN3L = 0b1;
   
   PDC1= PDC2= PDC3= 10000;
   
   IEC2bits.PWMIE = 0b1; 
   IPC9bits.PWMIP= 1;  // turn on pwm interrupt
   
   
   PTCONbits.PTEN = 0b1; //Turn on PWM*/
   
   while(1)
   {
       /*T1=T4=1;
       __delay_us(9990);
       T1=T4=0;
       __delay_us(10);              SQUARE WAVE INVERTER
       T2=T3=1;
       __delay_us(9990);
       T2=T3=0;
       __delay_us(10);*/
       
       /*
   #define   T4      LATEbits.LATE0
   #define   T3      LATEbits.LATE1
   #define   T2      LATEbits.LATE2
   #define   T1      LATEbits.LATE3
   #define   S23_S22 LATEbits.LATE4
   #define   S21     LATEbits.LATE5
   #define   S11     LATCbits.LATC13
   #define   S12     LATCbits.LATC14  */
   
   #define DEADTIME 1
   #define D0       797
   #define D1       824
   #define D2       924
   #define D3       1241
   #define D4       3217  
   
 //  #define __delay_us(X) __delay_ms(5000)   // for tesing
             
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000011010; LATC=0b0100000000000000;
// 0 Vcc: T1,T3,S23_S22,S12;    
       __delay_us(D0);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000011000; LATC=0b0100000000000000;
// dead time: T1,S23_S22,S12;
       __delay_us(DEADTIME);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000011001; LATC=0b0100000000000000;
//1 Vcc: T1,T4,S23_S22,S12;
       __delay_us(D1);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000011001; LATC=0b0000000000000000;
//dead time: T1,T4,S23_S22;
       __delay_us(DEADTIME);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000011001; LATC=0b0010000000000000;
//2 Vcc: T1,T4,S23_S22,S11;
       __delay_us(D2);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000001001; LATC=0b0000000000000000;
//dead time: T1,T4;
       __delay_us(DEADTIME);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000101001; LATC=0b0100000000000000;
//3 Vcc: T1,T4,S21,S12;
       __delay_us(D3);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000101001; LATC=0b0000000000000000;
//dead time: T1,T4,S21;
       __delay_us(DEADTIME);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000101001; LATC=0b0010000000000000;
//4 Vcc: T1,T4,S21,S11;
       __delay_us(D4);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000101001; LATC=0b0000000000000000;
//dead time: T1,T4,S21;
       __delay_us(DEADTIME);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000101001; LATC=0b0100000000000000;
//3 Vcc: T1,T4,S21,S12;
       __delay_us(D3);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000001001; LATC=0b0000000000000000;
//dead time: T1,T4;
       __delay_us(DEADTIME);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000011001; LATC=0b0010000000000000;
//2 Vcc: T1,T4,S23_S22,S11;
       __delay_us(D2);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000011001; LATC=0b0000000000000000;
//dead time: T1,T4,S23_S22;
       __delay_us(DEADTIME);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000011001; LATC=0b0100000000000000;
//1 Vcc: T1,T4,S23_S22,S12;
       __delay_us(D1);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000010001; LATC=0b0100000000000000;
// dead time: T4,S23_S22,S12;
       __delay_us(DEADTIME);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000010101; LATC=0b0100000000000000;
// 0 Vcc: T2,T4,S23_S22,S12;    
       __delay_us(D0);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000010100; LATC=0b0100000000000000;
// dead time: T2,S23_S22,S12;
       __delay_us(DEADTIME);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000010110; LATC=0b0100000000000000;
//-1 Vcc: T2,T3,S23_S22,S12;
       __delay_us(D1);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000010110; LATC=0b0000000000000000;
//dead time: T2,T3,S23_S22;
       __delay_us(DEADTIME);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000010110; LATC=0b0010000000000000;
//-2 Vcc: T2,T3,S23_S22,S11;
       __delay_us(D2);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000000110; LATC=0b0000000000000000;
//dead time: T2,T3;
       __delay_us(DEADTIME);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000100110; LATC=0b0100000000000000;
//-3 Vcc: T2,T3,S21,S12;
       __delay_us(D3);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000100110; LATC=0b0000000000000000;
//dead time: T2,T3,S21;
       __delay_us(DEADTIME);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000100110; LATC=0b0010000000000000;
//-4 Vcc: T2,T3,S21,S11;
       __delay_us(D4);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000100110; LATC=0b0000000000000000;
//dead time: T2,T3,S21;
       __delay_us(DEADTIME);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000100110; LATC=0b0100000000000000;
//-3 Vcc: T2,T3,S21,S12;
       __delay_us(D3);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000000110; LATC=0b0000000000000000;
//dead time: T2,T3;
       __delay_us(DEADTIME);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000010110; LATC=0b0010000000000000;
//-2 Vcc: T2,T3,S23_S22,S11;
       __delay_us(D2);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000010110; LATC=0b0000000000000000;
//dead time: T2,T3,S23_S22;
       __delay_us(DEADTIME);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000010110; LATC=0b0100000000000000;
//-1 Vcc: T2,T3,S23_S22,S12;
       __delay_us(D1);
          // 0b5432109876543210;      0b5432109876543210;
       LATE= 0b0000000000010010; LATC=0b0100000000000000;
// dead time: T3,S23_S22,S12;
       __delay_us(DEADTIME);
}
  
   return 0;
}
