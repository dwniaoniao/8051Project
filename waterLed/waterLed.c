//流水灯 
#include <8052.h>

#define led P2

static unsigned char a, b, c, d, e;

void delay(unsigned int i){
    while(i--);
}

void timer0Init(){
    TMOD |= 0x01;   // set timer 0 mode
    TH0 = 0x00;     // initiate timer high 0 value 
    TL0 = 0x18;     // initiate timer low 0 value
    EA = 1;         // global interrupt enable
    ET0 = 1;        // timer 0 interrupt enable
    TR0 = 1;        // start timer 0
}

void shift(){
    if (a == 0x0f){
        a = a << 1;
        b = b << 1;
        c = c << 1;
        d = d << 1;
    }
    else if (a == 0x1e){
        a = a << 1;
        b = b << 1;
        c = c << 1;
        d = (d << 1) + 1;
    }
    else if (a == 0x3c){
        a = a << 1;
        b = b << 1;
        c = (c << 1) + 1;
        d = (d << 1) + 1;
    } 
    else if (a == 0x78){
        a = a << 1;
        b = (b << 1) + 1;
        c = (c << 1) + 1;
        d = (d << 1) + 1;
    }
    else{
        a = (a << 1) + 1;
        b = (b << 1) + 1;
        c = (c << 1) + 1;
        d = (d << 1) + 1;
    }
}

void timer0() __interrupt 1{
    TH0 = 0x00;
    TH1 = 0x00;
    shift();    
}

void main(){
    timer0Init();
    a = 0xf0;
    b = 0xf1;
    c = 0xf3;
    d = 0xf7;
    e = 0xff;
    while(1){
        led = a;
        delay(1);
        led = b;
        delay(1);
        led = c;
        delay(1);
        led = d; 
        delay(1);
        led = e;
        delay(1);
    }
}
