#include <8052.h>

#define PWMport0 P2_0
#define PWMport1 P2_1
#define key1 P3_0
#define key2 P3_1
#define key3 P3_2
#define key4 P3_3

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
    PWMport0 = !PWMport0;
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

void setFanSpeed(unsigned char speed){
    // speed from 0 to 100
    genaratePWM(speed);
    genaratePWM1(0);
}

static volatile unsigned char j;
void delay50ms()
{ 
    for(j=0;j<50;j++){
        if(!i){
            j++;    // increment per 1024us, about 1ms
        }
    }
}

unsigned char keyScan()
{
    unsigned char pressedKey = 0;

    if(!key1){
        delay50ms();
        if(!key1){
            pressedKey = 1;
        }
        while(!key1);
    } else if(!key2){
        delay50ms();
        if(!key2){
            pressedKey = 2;
        }
        while(!key2);
    } else if(!key3){
        delay50ms();
        if(!key3){
            pressedKey = 3;
        }
        while(!key3);
    } else if(!key4){
        delay50ms();
        if(!key4){
            pressedKey = 4;
        }
        while(!key4);
    }

    return pressedKey;
}

// void main()
// {
//     unsigned char pressedKey = 0;
//     unsigned char fanSpeed = 0;
// 
//     timer0Init();
//     while(1){
//         setFanSpeed(fanSpeed);
//         pressedKey = keyScan();
//         switch(pressedKey){
//             case 1: fanSpeed = 0;
//                     break;
//             case 2: fanSpeed = 30;
//                     break;
//             case 3:
//                     fanSpeed = 60;
//                     break;
//             case 4:
//                     fanSpeed = 100;
//                     break;
//         }
//     }
// }

void main(){
    timer0Init();
    while(1);
}
