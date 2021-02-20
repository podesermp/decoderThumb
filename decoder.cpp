#include <iostream>
#include <cstring>
#include "decoder.h"

using namespace std;

bool validarHexadecimal(char *hex, int tam){

    int valido = 0;//quantos numeros válidos há na instrução
    int cont = 0;//indice pra acessar os valores da string
    //int i = 0;//indice pra saber o tamanho da string
    

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