#include <8052.h>

#define PWMport0 P2_0
#define PWMport1 P2_1

void timer0Init()
{
    TMOD = 0x02;    // timer0, mode2

    TH0 = 0xfb;      // 8-bit counter with automatic reload
    TL0 = 0xfb;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

static volatile unsigned char i = 0;
void timer0Interrupt() __interrupt(1)
{
    i++;    // increment per 4us
}

void genaratePWM(unsigned char dutyCycle)
{ // dutyCycle from 0 to 100, PWM 8-bit, 1kHz
    if(i*100/256 < dutyCycle){
        PWMport0 = 1;
    } else{
        PWMport0 = 0;
    }
}

void genaratePWM1(unsigned char dutyCycle)
{
    if(i*100/256 < dutyCycle){
        PWMport1 = 1;
    } else{
        PWMport1 = 0;
    }
}

void main()
{
    timer0Init();
    while(1){
        genaratePWM(50);
        genaratePWM(0);
    }
}
