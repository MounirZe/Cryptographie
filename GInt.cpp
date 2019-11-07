
#include "GInt.h"
#include <math.h>
#include <iostream>


GInt& GInt::Addition(GInt &add,GInt &final){// final juste pour les tests, à adapter au vrai code
    long long int s1,s2,c,addition;
    uint32_t a = 0;
    long long int max =(long long int) (a-1); // max unsigned int
    int taillefin;

    c=0;
    taillefin = fmax(taille,add.taille) +1;
    // DECLARATION tab de taille taillefin
    final.p_uint = new uint32_t[taillefin];
    final.taille = taillefin;

    for(int i =0;i<taillefin;i++){
        s1 = i<taille?p_uint[i]:0; // Si on i < taille alors on prend la valeur dans le tableau sinon 0, on peut donc add deux nombre de taille differente
        s2 = i<add.taille?add.p_uint[i]:0;

        addition = s1+s2+c;

        c= addition<max ? 0 :1;

        addition = addition>max?addition-(max + 1):addition;

        final.p_uint[i] = addition;
    }


    final.p_uint[taillefin-1] = addition;


    return final;
}

GInt &GInt::SoustraitUn(GInt &final) {
    GInt add;
    add.setp_int(new uint32_t);
    add.settaille(1);
    add.p_uint[0] = 1;
    this->Soustrait(add,final);
    delete []add.p_uint;
    return final;
}

GInt &GInt::Soustrait(GInt &add,GInt &final) {// On suppose que this > add
    long long int s1,s2,c,c1;
    uint32_t addition;

    uint32_t a = 0;
    long long int max =(long long int) (a-1); // max unsigned int
    int taillefin;

    c=0;
    taillefin = taille;
    // DECLARATION tab de taille taillefin
    final.p_uint = new uint32_t[taillefin];
    final.taille = taillefin;

    for(int i =0;i<taillefin;i++){
        s1 = i<taille?p_uint[i]:0; // Si on i < taille alors on prend la valeur dans le tableau sinon 0, on peut donc add deux nombre de taille differente
        s2 = i<add.taille?add.p_uint[i]:0;
        c1=c;
        c= s1>=(s2+c1)?0:1;


        addition = s1-s2 -c1 + c*(max+1);
        final.p_uint[i] = addition;

    }


    return final;

}


/*
GInt GInt::Multiplication(GInt &add);
GInt& GInt::Egal(GInt &add);*/