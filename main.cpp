#include <iostream>
#include "decoder.h"
#include <unistd.h>

using namespace std;

int main(){

    char instrucaoCompleta[16];
    char bitInstrucao;
    int i = 0;
    
    while(bitInstrucao != 10){
        read(STDIN_FILENO, &bitInstrucao, 1);
        instrucaoCompleta[i] = bitInstrucao;
        i++;
    }
    //cout << validarHexadecimal(instrucaoCompleta, i-1) << endl;
    opcode(instrucaoCompleta);

    return 0;
}