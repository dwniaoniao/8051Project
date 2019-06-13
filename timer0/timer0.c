#include <8052.h>

#define led P2_0

void timer0Init(){
    TMOD |= 0x01;   // set timer 0 mode
    TH0 = 0xFC;     // initiate timer high 0 value 
    TL0 = 0x18;     // initiate timer low 0 value
    EA = 1;         // global interrupt enable
    ET0 = 1;        // timer 0 interrupt enable
    TR0 = 1;        // start timer 0
}

static unsigned int i;
void timer0() __interrupt 1 {
    TH0 = 0xFC;     //reset timer 0
    TL0 = 0x18;
    i++;
    if (i == 1000){
        i = 0;
        led = !led;
    }
}

void main(){
    timer0Init();
    while(1);
}
