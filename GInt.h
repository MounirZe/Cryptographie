
#include <stdint-gcc.h>

class GInt {
private:
    uint32_t * p_uint;
    uint32_t taille;
public:
    GInt& Addition(GInt &add,GInt &final);
    GInt Multiplication(GInt &add);
    GInt& Egal(GInt &add);


    // Juste pour les test :
    void setp_int(uint32_t * p_int){
        p_uint = p_int;
    }
    void settaille(uint32_t t){
        taille = t;
    }

    uint32_t* getp_int(){
        return p_uint;
    }
};