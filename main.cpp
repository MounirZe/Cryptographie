#include <iostream>
#include "GInt.h"

int main(){
    uint32_t d =0;
    d = d-1;
    GInt a,b,c;
    uint32_t *p_inta = new uint32_t[3];
    uint32_t *p_intb = new uint32_t[3];


    for(int i =0;i<3;i++){
        p_inta[i] = 1;
        p_intb[i] = 0;

    }
    p_intb[0] = 5;
    a.setp_int(p_inta);
    b.setp_int(p_intb);
    a.settaille(3);
    b.settaille(3);


    a.Addition(b,c);

    for(int i =0;i<4;i++){
        std::cout<<c.getp_int()[i]<<std::endl;
    }



    delete []p_inta,p_intb,c.getp_int();

    return 0;
}

