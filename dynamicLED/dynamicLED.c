#include <8052.h>

unsigned char code[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71}; //0~F
void delay(){
    unsigned int i = 10000;
    while(i--);
}

void selectLed(unsigned int n){
    switch (n){
        case 1:
            P2_2 = P2_3 = P2_4 = 0;
            break;
        case 2:
            P2_2 = 1;
            P2_3 = P2_4 = 0;
            break;
        case 3:
            P2_2 = P2_4 = 0;
            P2_3 = 1;
            break;
        case 4:
            P2_2 = P2_3 = 1;
            P2_4 = 0;
            break;
        case 5:
            P2_2 = P2_3 = 0;
            P2_4 = 1;
            break;
        case 6:
            P2_2 = P2_4 = 1;
            P2_3 = 0;
            break;
        case 7:
            P2_2 = 0;
            P2_3 = P2_4 = 1;
            break;
        case 8:
            P2_2 = P2_3 = P2_4 = 1;
            break;
        default:
            break;
    }
}

void display(unsigned int n){
    selectLed(n);
    P0 = code[n];
    delay();
    P0 = 0x00;
}
void main(){
    while(1){
        for(int i=1;i<=8;i++){
           display(i);
       }
    }
}
