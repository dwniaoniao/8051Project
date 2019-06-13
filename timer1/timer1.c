#include <8052.h>

#define led P2_0

unsigned char code[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71}; //0~F

void timer1Init(){
    TMOD |= 0x10;
    TH1 = 0xFC;
    TL1 = 0x18;
    EA = 1;
    ET1 = 1;
    TR1 = 1;
}

void display(unsigned char n){
    P2_4 = P2_3 = P2_2 = 0;
    P0 = code[n];
}

static unsigned int i = 0;
static unsigned char j = 0;

void timer1() __interrupt 3 {
    TH1 = 0xFC;
    TL1 = 0X18;
    display(j);
    i++;
    if(i == 1000){
        i = 0;
        j++;
        if(j == 16) j = 0;
        P0 = 0x00;
    }
}

void main(){
    timer1Init();
    while(1);
}
