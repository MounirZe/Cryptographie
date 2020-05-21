#include "GInt.h"
#include <math.h>
#include <iostream>
#include <algorithm> //
#include <bitset>//


using namespace std;


GInt::GInt(std::string nombre){ //convertir chaine de carac base 10 vers base 2¨32
    std::reverse(nombre.begin(),nombre.end());

    std::string b;
    int i = 0;
    GInt base(1);
    GInt base2(1);

    base.p_uint[0] = 1000000000; //10^9


    base2.p_uint[0] =  1;

    taille = floor(nombre.length()*log(10)/(32*log(2)))+ 1; //floor prend la valeur basse ex 5 pour 5,3. CONVERSION DES TAILLES
	(*this) = GInt(taille);

    while((i+1)*9<=nombre.length()){ //je coupe tous les 9
        GInt a(1);
        //for(int j = 0;j<9;j++){
        //    a.p_uint[0] += nombre[i*9 +j]*pow(10,9-j);
        //}

        b = nombre.substr(i*9,9);
        std::reverse(b.begin(),b.end());


        a.p_uint[0] = std::stoi(b);


        a =a.Multiplication(base2);
		(*this) = (*this) + a;


        base2 = base2.Multiplication(base);

        i++;
    }

    if(nombre.length()%9!= 0){ // verifie si il reste des nbs à gauche
        GInt c(1);
        //std::cout<<std::stoi(nombre.substr(i*9));

        //std::cout<<nombre.substr(i*9);


        b = nombre.substr(i*9);

        std::reverse(b.begin(),b.end());

        c.p_uint[0] = std::stoi(b);
        c = c.Multiplication(base2);


        (*this) = (*this) + c;
    }
}


GInt::GInt(const GInt &copie){
    if(copie.taille == 0){
        p_uint = nullptr;
        taille = 0;
    }
    else{

        if(copie.p_uint[copie.taille-1]==0 && taille > 1){ //si dernier élèment=0 j'enleve cet élèment
            taille = copie.taille - 1;

        }
        else{
            taille = copie.taille;
        }

        p_uint = new unsigned int[taille];
        for(unsigned int i=0;i<taille;i++){
            p_uint[i] = copie.p_uint[i];
        }
    }
}



GInt & GInt::operator=( GInt copie) {
    delete[] this->p_uint;

    if(copie.taille == 0){
        p_uint = nullptr;
        taille= 0;
    }
    else{
        if(copie.p_uint[copie.taille-1]==0 && taille > 1){
            taille = copie.taille - 1;
        }
        else{
            taille = copie.taille;
        }
        p_uint = new unsigned int[taille];
        for(unsigned int i =0;i<taille;i++){
            p_uint[i] = copie.p_uint[i];
        }

    }
    return *this;
}
GInt GInt::Addition(const GInt &add){
    long long int s1,s2,c,addition; //long long int-->2^63-1
    unsigned int a = 0;
    a= a-1; // a= 2^32 - 1

    long long int max =(long long int) a;//la je fais un cast // max unsigned int
    int taillefin;

    c=0;
    taillefin = fmax(taille,add.taille) +1; //fonction fmax pr déterminer qui est le + grd, ici je raj une case au cas ou le nv nbr est + grd que le + grd des 2 nbrs.
    GInt final(taillefin);

    for(int i =0;i<taillefin;i++){
        s1 = i<taille?p_uint[i]:0; // Si on a i < taille alors on prend la valeur dans le tableau sinon 0, on peut donc add deux nombre de taille differente
        s2 = i<add.taille?add.p_uint[i]:0;

        addition = s1+s2+c; //j'ajoute valeur de la case du 1er tab à celui du 2ème et j'ajoute retenue

        c= addition>max ? 1 :0; // avec max= 2^32 - 1, si dépassement c= 1

        addition = addition>max?addition-(max + 1):addition; // je fais additions mod 2^32

        final.p_uint[i] = addition;
    }

    return final;
}

GInt GInt::Multiplication(GInt &b){
    
        unsigned long long int produit;
        unsigned int c;
        unsigned int r;

        GInt temp;
        uint32_t m = 0;
        long long int max =(long long int) (m-1); // max unsigned int

        for (unsigned int i=0;i<taille;i++)
        {
            for(unsigned int j=0;j<b.taille;j++){
                GInt a(i+j+2);
                produit = (unsigned long long int) p_uint[i]*(unsigned long long int)b.p_uint[j]; // unsigned long long int -> unsigned int
                r= produit % (max+1);
                produit -= r;
                c = produit / (max+1);

                a.p_uint[i+j+1] = c;
                a.p_uint[i+j] = r;

                for(unsigned int k = 0;k<i+j;k++){ //la on fait 0 0 0 0 0 0 0 0 R C
                    a.p_uint[k] = 0;
                }

                temp= temp+a;
            }
        }
        return temp;
    
}


GInt  GInt::operator*(GInt &copie){

    return this->Multiplication(copie);
}

GInt GInt::operator+(GInt &copie){
    return this->Addition(copie);
}

GInt GInt::operator*(unsigned int nbr){
    GInt copie(1);
    copie.p_uint[0] = nbr;
    return this->Multiplication(copie);
}

GInt  GInt::operator+(unsigned int nbr){
    GInt copie(1);
    copie.p_uint[0] = nbr;
    return this->Addition(copie);
}

bool  GInt::operator==(GInt &comp){
    bool retour = true;

    if(this->taille != comp.taille){
        retour = false;
    }
    else{
        for(int i = 0;i<taille;i++){
            if(this->p_uint[i] != comp.p_uint[i]){
                retour = false;
                break;
            }
        }
    }

    return retour;
}

GInt GInt::Soustrait(const GInt &add) {// On suppose que this > add
    long long int s1,s2,c,c1;
    unsigned int addition;

    unsigned int a = 0;
    long long int max =(long long int) (a-1); // max unsigned int
    c=0;
    GInt final(taille); //si je fais c=a-b, le "taille" corresp à la taille de c et de a

    for(int i =0;i<taille;i++){
        s1 = p_uint[i];
        s2 = i<add.taille?add.p_uint[i]:0;
        c1=c;
        c= s1>=(s2+c1)?0:1; //si s1 inf à s2 je prend une retenue c=1
        addition = s1-s2 -c1 + c*(max+1);// si addit° négative je fais + la base (2^32)
        //ex: add= 1 0 - 0 1 + c*10 donc add= -1 + 10=9 (c=1 si s1<s2)
        final.p_uint[i] = addition;
    }


    return final;
}
GInt GInt::operator-(GInt &copie){
    return this->Soustrait(copie);
}

bool GInt::operator>(const GInt &copie) {
    bool retour = false;

    if(taille > copie.taille){
        retour = true;
    }
    else if(taille < copie.taille){
            retour = false;
    }
    else{
        for(int i = taille-1;i>=0;i--){
            if(p_uint[i]>copie.p_uint[i]){
                retour = true;
                break;
            }
            else if(p_uint[i]<copie.p_uint[i]){
                retour = false;
                break;
            }
        }
    }

    return retour;
}

 GInt GInt::MulMon(GInt &A,GInt &B,GInt &Nprime,GInt &N) { 
	 GInt S;
	 S = B * A.p_uint[0];
	 GInt m(N.taille+2);
	 for (int i = 1; i < N.taille+1; i++) {
		 GInt Npcopie(Nprime);
		 Npcopie = Npcopie * S.p_uint[0];
		 m.p_uint[i] = Npcopie.p_uint[0];

		 GInt calc;
		 calc = B * (A.taille > i ? A.p_uint[i] : 0);
		 GInt calc2(N);
		 calc2 = calc2 * m.p_uint[i];
		 calc2 = calc2 + S;
		 if (calc2.taille > 1) {
			 GInt calc2div(calc2.taille - 1);
			 for (int j = 1; j < calc2.taille; j++) {
				 calc2div.p_uint[j - 1] = calc2.p_uint[j];
			 }
			 S = calc + calc2div;
		 }
		 else {
			 S = calc;
		 }

	 }
	 GInt calc3(Nprime);
	 calc3 = calc3 * S.p_uint[0];
	 m.p_uint[m.taille - 1] = calc3.p_uint[0];

	 GInt calc4(N);
	 calc4 = calc4 * m.p_uint[m.taille - 1];
	 calc4 = calc4 + S;
	 GInt calc4div(calc4.taille - 1);
	 for (int j = 1; j < calc4.taille; j++) {
		 calc4div.p_uint[j - 1] = calc4.p_uint[j];
	 }
	 S = calc4div;
	 return S;
 }



GInt  GInt::ExponentiationMod(GInt &clair,GInt &e,GInt &N,GInt &ninvN,GInt &Gamma){
    GInt clairmon;
    clairmon = GInt::MulMon(clair,Gamma,ninvN,N);
    GInt retourmon(clairmon);
    GInt retour;
    std::string ebit;
    std::string ei;
    GInt un("1");

    for(uint32_t i = 0;i<e.taille;i++){
        ei =  std::bitset<32>( e.p_uint[i] ).to_string();
        ebit = ei + ebit;
    }

    ebit = ebit.substr(ebit.find("1"));

    for(uint32_t i = 1;i<ebit.length();i++){
        if(ebit[i] == '1'){
            retourmon = GInt::MulMon(retourmon,retourmon,ninvN,N);// square
            retourmon = GInt::MulMon(retourmon,clairmon,ninvN,N);// multiply
        }
        else if (ebit[i] == '0') {
            retourmon = GInt::MulMon(retourmon,retourmon,ninvN,N);// square
        }
    }
    retour = GInt::MulMon(retourmon,un ,ninvN,N);
    return retour;
}



GInt GInt::Div10(std::string& strret) // Non fonctionnel
{
	GInt reste((*this));
	GInt Quotient(taille);
	unsigned int max = 0;
	max--;
	while (reste.p_uint[taille - 1] >= 10) {
		Quotient.p_uint[taille - 1]++;
		reste.p_uint[taille - 1] -= 10;
	}
	for (int i = taille - 1; i > 0; i--) {
		if (reste.p_uint[i] == 10) {
			Quotient.p_uint[i - 1] = max;
		}
		else {
			long long int r = ((long long int)max) + 1;
			long long int calc = ((long long int)reste.p_uint[i]) * r + (long long int)reste.p_uint[i - 1];
			calc = calc / 10;

			Quotient.p_uint[i - 1] = (unsigned int)calc;
		}
		GInt calc(2);
		calc.p_uint[1] = 10;
		calc = calc * Quotient.p_uint[i - 1];

		GInt calc2(3);
		calc2.p_uint[2] = reste.p_uint[i];
		calc2.p_uint[1] = reste.p_uint[i - 1];
		calc2.p_uint[0] = reste.p_uint[i - 2];

		while (calc > calc2) {
			Quotient.p_uint[i - 1] = Quotient.p_uint[i - 1] - 1;
			GInt calc(2);
			calc.p_uint[1] = 10;
			calc = calc * Quotient.p_uint[i - 1];
		}
		GInt calc3(i);
		calc3.p_uint[i - 1] = 10;
		calc3 = calc3 * Quotient.p_uint[i - 1];
		if (reste > calc3 || reste == calc3) {
			reste = reste - calc3;
		}
		else {
			GInt calc3(i);
			calc3.p_uint[i - 1] = 10;
			Quotient.p_uint[i - 1] = Quotient.p_uint[i - 1] - 1;
			calc3 = calc3 * Quotient.p_uint[i - 1];
			reste = reste + calc3;
		}
	}

	strret=to_string( reste.p_uint[0]);

	return Quotient;
}

void GInt::AfficheB10()
{
	GInt copie((*this));
	string affiche;
	string temp;
	GInt zero(1);
	while (copie > zero) {
		copie = copie.Div10(temp);
		affiche += temp;
	}
	std::reverse(affiche.begin(), affiche.end());
	cout << affiche;
}



