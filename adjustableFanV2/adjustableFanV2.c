//  FOSC: 24.088MHz
//  Model: STC89C52RC (ver6.6C) 
//  ROM: 8KB
//  [X] Reset stops watchdog
//  [X] Internal XRAM
//  [X] Normal ALE pin
//  [ ] Full gain oscillator
//  [X] Not erase data EEPROM
//  [X] Download regardless of P1
//  [ ] 12T mode

#include <8052.h>

#define motorPin P2_0
#define testPin P2_7
#define key1 P3_1
#define key2 P3_0
#define key3 P3_2
#define key4 P3_3
#define CYCLE 63

static volatile unsigned char timeCountL;
static volatile unsigned char timeCountH;
static unsigned char speedInterval, speed;

void timer0Init()
{
    TMOD = 0x02;    // timer0, mode2

    TH0 = 0xc0;      // 8-bit counter with automatic reload
    TL0 = 0xc0;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void timer0Interrupt() __interrupt(1)
{
    timeCountL++;   // increment per 32us
    if(!timeCountL){
        timeCountH++;   // increment per 8ms
        // testPin = !testPin;
    }

    if(speedInterval < CYCLE){
        if(speedInterval < speed){
            motorPin = 1;
        } else{
            motorPin = 0;
        }
        speedInterval++;
    } else{
        speedInterval = 0;
    }
}

void delayNms(unsigned int n){
    unsigned char start, duration;
    while(n){
        n--;
        start = timeCountL;
        duration = 0;
        while(duration < 31){
            duration = timeCountL - start;
        }
    }
}

unsigned char keyScan()
{
    unsigned char pressedKey = 0;

    if(!key1){
        delayNms(20);
        if(!key1){
            pressedKey = 1;
        }
        while(!key1);
    } else if(!key2){
        delayNms(20);
        if(!key2){
            pressedKey = 2;
        }
        while(!key2);
    } else if(!key3){
        delayNms(20);
        if(!key3){
            pressedKey = 3;
        }
        while(!key3);
    } else if(!key4){
        delayNms(20);
        if(!key4){
            pressedKey = 4;
        }
        while(!key4);
    }

    return pressedKey;
}

void main(){
    timer0Init();

    speed = 0;
    unsigned char pressedKey = 0;
    while(1){
        pressedKey = keyScan();
        switch(pressedKey){
            case 1: speed = 0;
                    break;
            case 2: speed = 20;
                    break;
            case 3: speed = 40;
                    break;
            case 4: speed = 64;
                    break;
        } 
    }
}

