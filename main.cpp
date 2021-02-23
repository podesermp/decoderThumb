#include <iostream>
#include "decoder.h"
#include <unistd.h>
#include <fstream>

using namespace std;

int main(){
    char instrucaoCompleta[16];
    ifstream fin;
    fin.open("decoderThumb.txt");
    while (fin.getline(instrucaoCompleta,16)){
        opcode(instrucaoCompleta);
    }
    
    
    
    
    
    /*char bitInstrucao;
    int i = 0;
    
    while(bitInstrucao != 10){
        read(STDIN_FILENO, &bitInstrucao, 1);
        instrucaoCompleta[i] = bitInstrucao;
        i++;
    }
    //cout << validarHexadecimal(instrucaoCompleta, i-1) << endl;
    
    */
    return 0;
}