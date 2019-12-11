#include <8052.h>

#define k3 P3_2
#define led P2_0

void delay(unsigned int i){
    while(i--);
}

void int0Init(){
    IT0 = 1;
    EX0 = 1;
    EA = 1;
}

void int0() __interrupt 0 {
    delay(1000);
    if(!k3){
        led = !led;
    }
}

void main(){
    int0Init();
    while(1);
}
