#include<xc.h>
#include<math.h>
#include"rotaion.h"
#include<stdint.h>
#define _XTAL_FREQ 8000000  
int step_pattern_left[4][4]= //???
    {{0,0,0,1},
    {0,1,0,0},
    {0,0,1,0},
    {1,0,0,0}
};

int step_pattern_right[4][4]={ //???
    {0,1,0,0},
    {0,0,0,1},
    {1,0,0,0},
    {0,0,1,0}
};

int step(int deg){
    uint16_t a=ceil(14*deg/1.8);
    return a;
}

void right(int mal,int speed){         
    int k = 0;
    uint16_t pluse = step(mal);
    while(k < pluse-20){
        for(int i = 0;i < 4;i++){  
            RA0 = step_pattern_right[i][0];
            RA4 = step_pattern_right[i][1];
            RC1 = step_pattern_right[i][2];                                                                                                                                                                                                                                       
            RC2 = step_pattern_right[i][3];
            __delay_us(3000);
            k++;
        }
    }
}

void left(int mal,int speed){              //??????????
    int i;
    int k = 0;
    uint16_t pluse = step(mal);
    while(k < pluse-20){
        for(i = 0;i < 4;i++){                                                                                                                                                                                                                                                                                            
            RA0 = step_pattern_left[i][0];
            RA4 = step_pattern_left[i][1];
            RC1 = step_pattern_left[i][2];
            RC2 = step_pattern_left[i][3];     //??
            __delay_us(3000);
            k++;
        }
    }
}
