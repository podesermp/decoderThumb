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
    return 0;
}
