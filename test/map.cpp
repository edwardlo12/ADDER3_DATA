//
//  map.cpp
//  test
//
//  Created by 羅仕昌 on 2017/5/19.
//  Copyright © 2017年 羅仕昌. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <iomanip>
#define max 10 //max^2矩陣

int data[128][128];     //順序資料
int flag[128][128]={0}; //旗標
int count=0;
int FLAG=0;     //顯示錯誤位置旗標
int DATA=1;     //顯示資料順序
int PATTERN=1;  //列出輸入資料

// ============ Please edit the input vector ============
// the number of patterns
int pattern_number = 10 ;
double period = 3.0 ; //ns
// input patterns
int A0[max] ;
int A1[max] ;
int A2[max] = {1,1,0,1,1} ;
int B0[max] = {1,0,0,0,1} ;
int B1[max] = {1,0,0,1,1} ;
int B2[max] = {1,1,0,1,1} ;
int CIN[max]= {1,0,1,1,1} ;
// golden output patterns
int AS0[max] = {1,1,0,1,1} ;
int AS1[max] = {1,1,0,0,1} ;
int AS2[max] = {1,0,1,1,1} ;
int ACOUT[max]={0,1,0,1,1} ;
// Set to 1 if you want to patch pex result file
int patch_pex_file = 1 ; // Yes:1 No:0
//=======================================================



int main()
{
    int input=0;
    for(int i=0;i<pattern_number;i++)
        flag[i][i]=1;
    
    for(int i=0;i<(pattern_number*(pattern_number-1));i++){
        //init input function with input
        A0[i] = (input>>6)%2;
        A1[i] = (input>>5)%2;
        A2[i] = (input>>4)%2;
        B0[i] = (input>>3)%2;
        B1[i] = (input>>2)%2;
        B2[i] = (input>>1)%2;
        CIN[i]= (input)%2;
        //std::cout<<"line"<<std::setw(2)<<i+1<<": "<<A0[i]<<A1[i]<<A2[i]<<B0[i]<<B1[i]<<B2[i]<<CIN[i]<<std::endl;
        //==============================
        for(int j=pattern_number-1;j>=0;j--){
            if(flag[input][j]==0){
                flag[input][j]=1;
                data[input][j]=++count;
                input=j;
                break;
            }
        }
    }
    if(FLAG){
        std::cout<<"FLAG:"<<std::endl;
        for(int i=0;i<pattern_number;i++){
            for(int j=0;j<pattern_number;j++){
                if(flag[j][i]==0)
                    std::cout<<j<<" "<<i<<std::endl;
                //std::cout<<std::setw(2)<<flag[j][i]<<" ";
            }
            //std::cout<<std::endl;
        }

    }
    if(DATA){
        std::cout<<"DATA:"<<std::endl;
        for(int i=0;i<pattern_number;i++){
            for(int j=0;j<pattern_number;j++)
                std::cout<<std::setw(2)<<data[j][i]<<" ";
            std::cout<<std::endl;
        }
    }
    if(PATTERN){
        for(int i=0;i<(pattern_number*(pattern_number-1));i++){
            std::cout<<"line"<<std::setw(2)<<i+1<<": "<<A0[i]<<A1[i]<<A2[i]<<B0[i]<<B1[i]<<B2[i]<<CIN[i]<<std::endl;
        }
    }
    
    return 0;
}

