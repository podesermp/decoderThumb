#include <iostream>
#include <cstring>
#include <math.h>   //PARA A FUNÇÃO QUE TRANSFORMA DE BINARIO PARA DECIMAL
#include <fstream>  //PARA AS FUNÇÕES DE ARQUIVO
#include "decoder.h"

using namespace std;

bool validarHexadecimal(char *hex, int tam){

    int valido = 0;//quantos numeros válidos há na instrução
    int cont = 0;//indice pra acessar os valores da string
    

    if(tam <= 0 || tam > 4){
        cout << "Hexadecimal inválido!" << endl;
        return false;
    }
    //4 pq cada instrução em Thumb tem 16 bit
    cont = 0;
    while(cont < 4){
        if(hex[cont] == '0' || hex[cont] == '1' || hex[cont] == '2' || hex[cont] == '3' || hex[cont] == '4' || hex[cont] == '5' || hex[cont] == '6' ||
        hex[cont] == '7' || hex[cont] == '8' || hex[cont] == '9' || (hex[cont] == 'a' || hex[cont] == 'A') || (hex[cont] == 'b' || hex[cont] == 'B')|| (hex[cont] == 'c' || hex[cont] == 'C')||
        (hex[cont] == 'd' || hex[cont] == 'D') || (hex[cont] == 'e' || hex[cont] == 'E') || (hex[cont] == 'f' || hex[cont] == 'F')){
            valido++;
        }else{
            cout << "Hexadecimal inválido!" << endl; 
            return false;
        }
        cont++;
    }

    if(valido == 4){
        return true;
    }else{
        cout << "Hexadecimal inválido!" << endl;
        return false;
    }
}
//RETORNA APENAS A PARTE DESEJADA DO BINARIO
string separabinario(string binario, int pos, int tam){
    string bin;
    while(tam>0){
        bin+=binario[pos];
        tam--;
        pos++;
    }
    return bin;
}

//CONVERTE UM BINARIO EM DECIMAL
int convertebindec(string binario, int tam){
    int decimal=0;
    for(int i= 0; i<tam ;i++){
        if(binario[i]=='1')decimal+= pow(2,(tam-1)-i);
    }
    return decimal;
}


string converteHexBin(string hex){
    string binario;
    int i = 0;

    string hex0("0000");
    string hex1("0001");
    string hex2("0010");
    string hex3("0011");
    string hex4("0100");
    string hex5("0101");
    string hex6("0110");
    string hex7("0111");
    string hex8("1000");
    string hex9("1001");
    string hexa("1010");
    string hexb("1011");
    string hexc("1100");
    string hexd("1101");
    string hexe("1110");
    string hexf("1111");

    while(i < 4){
        switch(hex[i]){
            case '0':
                binario+=hex0;
                break;
            case '1':
                binario+=hex1;
                break;
            case '2':
                binario+=hex2;
                break;
            case '3':
                binario+=hex3;
                break;
            case '4':
                binario+=hex4;
                break;
            case '5':
                binario+=hex5;
                break;
            case '6':
                binario+=hex6;
                break;
            case '7':
                binario+=hex7;
                break;
            case '8':
                binario+=hex8;
                break;
            case '9':
                binario+=hex9;
                break;
            case 'a':
                binario+=hexa;
                break;
            case 'b':
                binario+=hexb;
                break;
            case 'c':
                binario+=hexc;
                break;
            case 'd':
                binario+=hexd;
                break;
            case 'e':
                binario+=hexe;
                break;
            case 'f':
                binario+=hexf;
                break;
            default:
                cout << "Hexadecimal inválido!"<<endl;
                break;
        }
        i++;
    }
    return binario;
}

//COLOQUEI A FUNÇÃO PRA NÃO RETORNAR, MAS A FUNÇÃO GRAVA A INSTRUÇÃO NO ARQUIVO
//NESSA FUNÇÃO ANALISA-SE O OPCODE E DIZ QUAL A INSTRUÇÃO QUE FOI COLOCADA
void opcode(char *hex){
    fstream fout;
    fout.open("decoderThumb(saida).txt", ios::ate | ios::out | ios::in);
    string binario;
    if(validarHexadecimal(hex, 4)){
        binario = converteHexBin(hex);
    }else{
        exit(1);
    }
    //OS IFs Vão PEGAR OS 4 PRIMEIROS BITS, QUE É PARA SABER QUAL INSTRUÇÃO
    //DENTRO DE CADA CONDIÇAO DE CADA INSTRUÇÃO É QUE VAI ESPECIFICAR QUAL INSTRUÇÃO SERÁ USADA
    //*****************************************************************************************//
    //LSL    
    if(hex[0]=='0'){
        if(binario[4]=='0'){
                fout << hex << "    LSL r" << convertebindec(separabinario(binario, 13, 3), 3) <<
                    ", r" << convertebindec(separabinario(binario, 10, 3), 3) << ", #" <<
                    convertebindec(separabinario(binario, 5, 5), 5) << endl;
            }
            //LSR
            else{
                fout << hex << "    LSR r" << convertebindec(separabinario(binario, 13, 3), 3) <<
                               ", r" << convertebindec(separabinario(binario, 10, 3), 3) << ", #"<<
                               convertebindec(separabinario(binario, 5, 5), 5) << endl;
            }
    }
    else if(hex[0]=='1'){
        if(binario[4]=='0'){
            fout << hex << "    ASR r" << convertebindec(separabinario(binario, 13, 3), 3) <<
                           ", r" << convertebindec(separabinario(binario, 10, 3), 3) << ", #" <<
                           convertebindec(separabinario(binario, 5, 5), 5) << endl;
        }else{
            //ADD
            if(binario[5]=='0' && binario[6]=='0'){
                fout << hex << "    ADD r" << convertebindec(separabinario(binario, 13, 3), 3) <<
                               ", r" << convertebindec(separabinario(binario, 10, 3), 3) << ", r"<<
                               convertebindec(separabinario(binario, 7, 3), 3) << endl;
            }//SUB
            else if(binario[5]=='0' && binario[6]=='1'){
                fout << hex << "    SUB r" << convertebindec(separabinario(binario, 13, 3), 3) <<
                               ", r" << convertebindec(separabinario(binario, 10, 3), 3) << ", r"<<
                               convertebindec(separabinario(binario, 7, 3), 3) << endl;
            }//ADD
            else if(binario[5]=='1' && binario[6]=='0'){
                fout << hex << "    ADD r" << convertebindec(separabinario(binario, 13, 3), 3) <<
                               ", r" << convertebindec(separabinario(binario, 10, 3), 3) << ", #"<<
                               convertebindec(separabinario(binario, 7, 3), 3) << endl;
            }//SUB
            else if(binario[5]=='1' && binario[6]=='1'){
                fout << hex << "    SUB r" << convertebindec(separabinario(binario, 13, 3), 3) <<
                               ", r" << convertebindec(separabinario(binario, 10, 3), 3) << ", #"<<
                               convertebindec(separabinario(binario, 7, 3), 3) << endl;
            }
        }
    }//MOV | CMP
    else if(hex[0]=='2'){
        //MOV
        if(binario[4]=='0'){
            fout << hex << "    MOV r" << convertebindec(separabinario(binario, 5, 3), 3) <<
                                ", #"<< convertebindec(separabinario(binario, 8, 8), 8) << endl;
        }//CMP
        else{
            fout << hex << "    CMP r" << convertebindec(separabinario(binario, 5, 3), 3) <<
                                ", #"<< convertebindec(separabinario(binario, 8, 8), 8) << endl;
        }
    }//ADD | SUB
    else if(hex[0]=='3'){
        //ADD
        if(binario[4]=='0'){
            fout << hex << "    ADD r" << convertebindec(separabinario(binario, 5, 3), 3) <<
                                ", #"<< convertebindec(separabinario(binario, 8, 8), 8) << endl;
        }//SUB
        else{
            fout << hex << "    SUB r" << convertebindec(separabinario(binario, 5, 3), 3) <<
                                ", #"<< convertebindec(separabinario(binario, 8, 8), 8) << endl;
        }
    }   
}
