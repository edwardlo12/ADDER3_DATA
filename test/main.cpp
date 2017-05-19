//
//  main.cpp
//  test
//
//  Created by 羅仕昌 on 2017/5/15.
//  Copyright © 2017年 羅仕昌. All rights reserved.
//

#include <iostream>
struct DATA{
    int f[7];
    int b[7];
    int flag=0;
    
}data[128][128];
    
    
int main(int argc, const char * argv[]) {
    // insert code here...
    //std::cout << "Hello, World!\n";
    int f_a2,f_a1,f_a0,f_b2,f_b1,f_b0,f_cin,b_a2,b_a1,b_a0,b_b2,b_b1,b_b0,b_cin; //f:前值 b:後值
    int count=0;//計數
    std::cout<<"A2A1A0B2B1B0CIN\t TO A2A1A0B2B1B0CIN\tcount"<<std::endl;
    for(f_a2=0;f_a2<2;f_a2++)
    for(f_a1=0;f_a1<2;f_a1++)
    for(f_a0=0;f_a0<2;f_a0++)
    for(f_b2=0;f_b2<2;f_b2++)
    for(f_b1=0;f_b1<2;f_b1++)
    for(f_b0=0;f_b0<2;f_b0++)
    for(f_cin=0;f_cin<2;f_cin++) //frount
        for(b_a2=0;b_a2<2;b_a2++)
        for(b_a1=0;b_a1<2;b_a1++)
        for(b_a0=0;b_a0<2;b_a0++)
        for(b_b2=0;b_b2<2;b_b2++)
        for(b_b1=0;b_b1<2;b_b1++)
        for(b_b0=0;b_b0<2;b_b0++)
        for(b_cin=0;b_cin<2;b_cin++){//back
            int flag=0;
            int F[7]={f_a2,f_a1,f_a0,f_b2,f_b1,f_b0,f_cin};//前值
            int B[7]={b_a2,b_a1,b_a0,b_b2,b_b1,b_b0,b_cin};//後值
            int f_count=64*f_a2+32*f_a1+16*f_a0+8*f_b2+4*f_b1+2*f_b0+f_cin;
            int b_count=64*b_a2+32*b_a1+16*b_a0+8*b_b2+4*b_b1+2*b_b0+b_cin;
                for(int i=0;i<7;i++){
                //std::cout<<F[i]<<" "<<B[i]<<" "<<flag<<std::endl;
                    data[f_count][b_count].f[i]=F[i];
                    data[f_count][b_count].b[i]=B[i];
                if(F[i]!=B[i]){
                    flag=1; //只要有一位長得不一樣，flag就設為1
                    break;
                }
                
            }
            if(flag)
                std::cout<<f_a2<<f_a1<<f_a0<<f_b2<<f_b1<<f_b0<<f_cin<<"\t\t\t TO "<<b_a2<<b_a1<<b_a0<<b_b2<<b_b1<<b_b0<<b_cin<<"\t\t\t"<<++count<<std::endl;
                //A2A1A0B2B1B0CIN TO A2A1A0B2B1B0CIN 第N筆資料
            }
    for(int i=0;i<128;i++){
        std::cout<<i<<"\t";
        for(int j=0;j<128;j++){
            for(int k=0;k<7;k++)
                std::cout<<data[i][j].f[k];
            std::cout<<"->";
            for(int k=0;k<7;k++)
                std::cout<<data[i][j].b[k];
            std::cout<<"\t";
        }
        std::cout<<std::endl;
    }
    
        
    
    return 0;
}
