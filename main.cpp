#include <iostream>
#include "decoder.h"
#include <unistd.h>
#include <fstream>

using namespace std;

int main(){
    char instrucaoCompleta[16];                //ARRAY QUE GUARDARA O HEXADECIMAL LIDO DO ARQUIVO
    ifstream fin;                              //CRIA O ARQUIVO
    fin.open("decoderThumb.in");              //ABRE O ARQUIVO PARA LEITURA
    while (fin.getline(instrucaoCompleta,16)){ //TIRA CADA LINHA DO ARQUIVO
        opcode(instrucaoCompleta);             //MANDA A LINHA LIDA DO ARQUIVO PARA A FUNÇÃO OPCODE
    }
    return 0;
}