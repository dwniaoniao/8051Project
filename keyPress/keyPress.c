#include <8052.h>

void delay(unsigned int i){
    while(i--);
}

void keyPress(){
    if(P3_1 == 0){
        delay(5000);    //消除抖动
        if(P3_1 == 0)
            P2_0 = !P2_0;
        while(!P3_1);
    }
}

void main(){
    while(1){
        keyPress();
    }
}
