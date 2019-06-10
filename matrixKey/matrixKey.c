#include <8052.h>

unsigned char code[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71}; //0~F

void delay(unsigned int i){
    while(i--);
}

unsigned int checkKey(){
    unsigned int keyNum;
    P1 = 0x0f;
    if(P1 != 0x0f){
        delay(5000);
        if(P1 != 0x0f){
            switch(P1){
                case 0x07: keyNum = 0; break;
                case 0x0b: keyNum = 1; break;
                case 0x0d: keyNum = 2; break;
                case 0x0e: keyNum = 3; break;
            }

            P1 = 0xf0;
            switch(P1){
                case 0x70: break;
                case 0xb0: keyNum += 4; break;
                case 0xd0: keyNum += 8; break;
                case 0xe0: keyNum += 12; break;
            }
            
            while(P1 != 0xf0){
                delay(5000);
            }
        }
    }
    return keyNum;
}

void main(){
    while(1){
        P2_2 = P2_3 = P2_4 = 0;
        P0 = code[checkKey()];
    }
}
