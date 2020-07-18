#define    FCY    20000000UL
#include "header.h"
#include "xc.h"
#include <libpic30.h>
#define DEADTIME __delay32(12)


extern int lookup[100][2];
int TON_flag=0;
int step=0;


 void __attribute__((interrupt,auto_psv)) _T1Interrupt(void)
 {
     T1CONbits.TON=0;//Timer turned off
     if(TON_flag) //now entering Toff state
     {
        PR1=lookup[step-1][1];
        if( (step>=1&&step<=4) || (step>=47&&step<=50) ) //level 1
        {
              //   5432109876543210
            LATE=0b0000000001011000;
            DEADTIME;
              //   5432109876543210
            LATE=0b0000000001011010;                         
        }
        else if( (step>=5&&step<=8) || (step>=43&&step<=46) ) //level 2
        {
              //   5432109876543210
            LATE=0b0000000000011001;
            DEADTIME;
              //   5432109876543210
            LATE=0b0000000001011001;
        }
        else if( (step>=9&&step<=13) || (step>=38&&step<=42) ) //level 3
        {
              //   5432109876543210
            LATE=0b0000000000001001;
            DEADTIME;
              //   5432109876543210
            LATE=0b0000000010011001;                         
        }
        else if( (step>=14&&step<=37) ) //level 4
        {
              //   5432109876543210
            LATE=0b0000000000101001;
            DEADTIME;
              //   5432109876543210
            LATE=0b0000000001101001;                         
        }
        else if( (step>=51&&step<=54) || (step>=97&&step<=100) ) //level -1
        {
              //   5432109876543210
            LATE=0b0000000001010010;
            DEADTIME;
              //   5432109876543210
            LATE=0b0000000001011010;
        }
        else if( (step>=55&&step<=58) || (step>=93&&step<=96) ) //level -2
        {
              //   5432109876543210
            LATE=0b0000000000010110;
            DEADTIME;
              //   5432109876543210
            LATE=0b0000000001010110;
        }
        else if( (step>=59&&step<=63) || (step>=88&&step<=92) ) //level -3
        {
              //   5432109876543210
            LATE=0b0000000000000110;
            DEADTIME;
              //   5432109876543210
            LATE=0b0000000010010110;                         
        }
        else //level -4
        {
              //   5432109876543210
            LATE=0b0000000000100110;
            DEADTIME;
              //   5432109876543210
            LATE=0b0000000001100110;                         
        }
        
        TON_flag=0; //flag cleared to indicate off state
     }
     else //now entering Ton state
     {
        step++;     //step increment prior to going to next state
        if(step==101)   step=1;
        PR1=lookup[step-1][0];
        if( (step>=1&&step<=4) || (step>=47&&step<=50) ) //level 1
        {
              //   5432109876543210
            LATE=0b0000000001011000;
            DEADTIME;
              //   5432109876543210
            LATE=0b0000000001011001;              
        }
        else if( (step>=5&&step<=8) || (step>=43&&step<=46) ) //level 2
        {
              //   5432109876543210
            LATE=0b0000000000011000;
            DEADTIME;
              //   5432109876543210
            LATE=0b0000000010011001;                         
        }
        else if( (step>=9&&step<=13) || (step>=38&&step<=42) ) //level 3
        {
              //   5432109876543210
            LATE=0b0000000000001001;
            DEADTIME;
              //   5432109876543210
            LATE=0b0000000001101001;
        }
        else if( (step>=14&&step<=37) ) //level 4
        {  
              //   5432109876543210
            LATE=0b0000000000001001;
            DEADTIME;
              //   5432109876543210
            LATE=0b0000000010101001;                         
        }
        else if( (step>=51&&step<=54) || (step>=97&&step<=100) ) //level -1
        {
              //   5432109876543210
            LATE=0b0000000001010010;
            DEADTIME;
              //   5432109876543210
            LATE=0b0000000001010110;
        }
        else if( (step>=55&&step<=58) || (step>=93&&step<=96) ) //level -2
        {
              //   5432109876543210
            LATE=0b0000000000010010;
            DEADTIME;
              //   5432109876543210
            LATE=0b0000000010010110;
        }
        else if( (step>=59&&step<=63) || (step>=88&&step<=92) ) //level -3
        {
              //   5432109876543210
            LATE=0b0000000000000110;
            DEADTIME;
              //   5432109876543210
            LATE=0b0000000001100110;
        }
        else //level -4
        {
              //   5432109876543210
            LATE=0b0000000000000110;
            DEADTIME;
              //   5432109876543210
            LATE=0b0000000010100110;             
        }
        TON_flag=1; //flag set to indicate on state        
     }
     TMR1 = 0; //counter cleared for fresh timing
     IFS0bits.T1IF=0; //interrupt flag cleared;
     T1CONbits.TON=1; // timer restarted
 }
 


/*
void __attribute__((interrupt,auto_psv)) _T1Interrupt(void)
 {
     T1CONbits.TON=0;//Timer turned off
     if(TON_flag)//entering off time
     {
         PR1=2000;
         LATE=0b0000000000000000;
         DEADTIME;
         LATE=0b0000000001010101;
         TON_flag=0;
     }
     else //entering on time
     {
         PR1=2000;
         LATE=0b0000000000000000;
         DEADTIME;
         LATE=0b0000000010101010;
         TON_flag=1;
     }
     TMR1 = 0; //counter cleared for fresh timing
     IFS0bits.T1IF=0; //interrupt flag cleared;
     T1CONbits.TON=1;        
}
         
    */     



int main(void) {
    TRISE=0; // configure PORT E as output
    LATE=0; // LATCH E  LOW
    PR1=3900; 
    TMR1=0;             //reset timer
    IPC0bits.T1IP=7;    //timer 1 high priority
    IEC0bits.T1IE=1;    //timer 1 interrupt enable
    T1CONbits.TON=1;    //timer ON;
    while(1);   
    return 0;
}
