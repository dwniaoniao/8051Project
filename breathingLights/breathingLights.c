//呼吸灯
#include <8052.h>

#define led P2

void delay(unsigned int i){
    while(i--);
}

void breathing(){
    unsigned int cycle, left, right;
    cycle = 500;
    left = 0;
    while (left != cycle){
        right = cycle - left;
        delay(left);
        led = ~led;
        delay(right);
        led = ~led;
        left++;
    }
    while (left){
        right = cycle-left;
        delay(left);
        led = ~led;
        delay(right);
        led = ~led;
        left--;
    }
}

void main(){
    while(1){
        breathing();
    }
}
