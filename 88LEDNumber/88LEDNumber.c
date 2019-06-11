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
    unsigned char a[] = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
    unsigned char b[] = {0x00,0x00,0x3e,0x41,0x41,0x41,0x3e,0x00};

    while(1){
        p0 = 0xff;
        for(int i=0;i<8;i++){
            p0 = a[i];           //从左向右扫描
            hc595SendByte(b[i]);
            delay(1);
            hc595SendByte(0x00); //消隐
        }
    }
}
