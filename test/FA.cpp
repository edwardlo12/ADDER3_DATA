//
//  FA.cpp
//  test
//
//  Created by 羅仕昌 on 2017/5/18.
//  Copyright © 2017年 羅仕昌. All rights reserved.
//

#include <iostream>

int main(){
    int f_a,f_b,f_cin,b_a,b_b,b_cin,j=0;
    for(f_a=0;f_a<2;f_a++)
    for(f_b=0;f_b<2;f_b++)
    for(f_cin=0;f_cin<2;f_cin++)//front
        for(b_a=0;b_a<2;b_a++)
        for(b_b=0;b_b<2;b_b++)
        for(b_cin=0;b_cin<2;b_cin++){//back
            int F[3]={f_a,f_b,f_cin};
            int B[3]={b_a,b_b,b_cin};
            int flag=0;
            for(int i=0;i<3;i++){
                if(F[i]!=B[i]){
                    flag=1;
                    break;
                }
            }
            if(flag)
            std::cout<<f_a<<f_b<<f_cin<<" TO "<<b_a<<b_b<<b_cin<<" "<<++j<<std::endl;
        }
    
}
