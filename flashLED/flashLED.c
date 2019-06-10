#include <8051.h>

void delay(unsigned int i){
    while(i--);
}

void flashLED(){
    while(1){
        P2_0 = !P2_0;
        delay(5000);
    }
}

void main(){
    flashLED();
}
