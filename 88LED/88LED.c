#include <8052.h>

#define p0 P0
#define srclk P3_6
#define rclk P3_5
#define ser P3_4

void delay(unsigned int i){
    while(i--);
}

void hc595SendByte(unsigned char goldByte){
    //74HC595输出一个字节数据
    srclk = 0;
    rclk = 0;
    for(int a=0;a<8;a++){
        ser = goldByte >> 7;
        goldByte <<= 1;
        srclk = 1;  //产生一个上升沿
        delay(1);
        srclk = 0;
    }
    rclk = 1;   //上升沿
    delay(1);
    rclk = 0;
}

void main(){
    hc595SendByte(0x08);
    p0 = 0xf7;
    while(1);
}
