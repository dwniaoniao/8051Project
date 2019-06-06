#include <8052.h>

void delay(unsigned int i){
    while(i--);
}
void main(){
    while(1){
        P1_5 = !P1_5;
        delay(100);
    }
}
