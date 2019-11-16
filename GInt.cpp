
#include "GInt.h"
#include <math.h>
#include <iostream>


GInt::GInt(std::string nombre){
    std::reverse(nombre.begin(),nombre.end());

    std::string b;
    int i = 0;
    GInt base(1);
    GInt base2(1);

    base.p_uint[0] = 1000000000;//10^9


    base2.p_uint[0] =  1;

    taille = floor(nombre.length()*log(10)/(32*log(2)) )+ 1;
    p_uint = new unsigned int[taille];
    p_uint[0] = 0;

    GInt ret(taille);

    while((i+1)*9<nombre.length()){
        GInt a(1);
        //for(int j = 0;j<9;j++){
        //    a.p_uint[0] += nombre[i*9 +j]*pow(10,9-j);
        //}

        b = nombre.substr(i*9,(i+1)*9);
        std::reverse(b.begin(),b.end());


        a.p_uint[0] = std::stoi(b);


        a = a.Multiplication(base2);
        ret = ret.Addition(a);


        base2 = base2.Multiplication(base);

        i++;
    };
    GInt c(1);
    //std::cout<<std::stoi(nombre.substr(i*9));

    //std::cout<<nombre.substr(i*9);


    b = nombre.substr(i*9);

    std::reverse(b.begin(),b.end());

    c.p_uint[0] = std::stoi(b);
    c = c.Multiplication(base2);


    ret = ret.Addition(c);

    for(unsigned int i=0;i<taille;i++){
        p_uint[i] = ret.p_uint[i];
    }
}


GInt::GInt(const GInt &copie){
    if(copie.p_uint[copie.taille-1]==0){
        taille = copie.taille - 1;

    }
    else{
        taille = copie.taille;
    }

    p_uint = new uint32_t[taille];
    for(uint32_t i=0;i<taille;i++){
        p_uint[i] = copie.p_uint[i];
    }
}


GInt & GInt::operator=(const GInt &copie) {
    delete[] this->p_uint;

    if(copie.p_uint[copie.taille-1]==0){
        taille = copie.taille - 1;

    }
    else{
        taille = copie.taille;
    }
    p_uint = new uint32_t[taille];
    for(uint32_t i =0;i<taille;i++){
        p_uint[i] = copie.p_uint[i];
    }
    return *this;
}



GInt GInt::Addition(const GInt &add){
    long long int s1,s2,c,addition;
    uint32_t a = 0;
    long long int max =(long long int) (a-1); // max unsigned int
    int taillefin;

    c=0;
    taillefin = fmax(taille,add.taille) +1;
    GInt final(taillefin);

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
GInt GInt::SoustraitUn(){
    GInt add(1);

    add.p_uint[0] = 1;

    return Soustrait(add);
}

GInt GInt::Soustrait(const GInt &add) {// On suppose que this > add
    long long int s1,s2,c,c1;
    uint32_t addition;

    uint32_t a = 0;
    long long int max =(long long int) (a-1); // max unsigned int
    c=0;
    GInt final(taille);

    for(int i =0;i<taille;i++){
        s1 = p_uint[i]; // Si on i < taille alors on prend la valeur dans le tableau sinon 0, on peut donc add deux nombre de taille differente
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
