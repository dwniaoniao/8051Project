//同时点亮几个LED，亮度各不相同
#include <8052.h>

#define led P2

void delay(unsigned int i){
    while(i--);
}

void myDelay(){
    delay(1);
}

void main(){
    while(1){
        led = 0x00;
        myDelay();
        led = 0x80;
        myDelay();
        led = 0xc0;
        myDelay();
        led = 0xe0;
        myDelay();
        led = 0xf0;
        myDelay();
        led = 0xf8;
        myDelay();
        led = 0xfc;
        myDelay();
        led = 0xfe;
        myDelay();
        led = 0xff;
        myDelay();
    }
}
