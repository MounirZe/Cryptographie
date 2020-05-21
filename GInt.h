#include <cstdint>
#include <string>
#include <iostream>

class GInt {
private:

	unsigned int*p_uint;
	unsigned int taille;

public:
    GInt(const unsigned int tailletab) {
        taille = tailletab;
        p_uint = new unsigned int[taille];
        for (unsigned int i = 0; i < taille; i++) {
            p_uint[i] = 0;
        }
    }

    GInt(std::string nombre);

    GInt() {
        taille = 0;
        p_uint = nullptr;
    }

    GInt(const GInt &copie);

    GInt &operator=(const GInt copie);


    GInt Addition(const GInt &add);

    GInt Multiplication(GInt &add);

    static GInt MulMon(GInt &A, GInt &B, GInt &Nprime, GInt &N);


    
    void setp_int(unsigned int*p_int) {
        p_uint = p_int;
    }

    void settaille(unsigned int t) {
        taille = t;
    }

	unsigned int*getp_int() {
        return p_uint;
    }

	unsigned int gettaille() {
        return taille;
    }

    ~GInt() {
		if (p_uint != nullptr) {
			delete[] p_uint;
		}
    }


    bool operator>(const GInt &copie);

    GInt operator+(GInt &copie);


    GInt operator+(unsigned int nbr);

    GInt operator*(GInt &copie);

    bool operator==(GInt &comp);

	GInt Soustrait(const GInt& add);

	GInt operator-(GInt& copie);

    GInt operator*(unsigned int nbr);

	GInt Div10(std::string& strret);
	void AfficheB10();

    static GInt ExponentiationMod(GInt &clair, GInt &e, GInt &N, GInt &ninvN, GInt &Gamma);


};