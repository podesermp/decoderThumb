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
    for(int i= 0; tam>0 ;i++){
        if(binario[tam-1]=='1'){
            decimal+= pow(2,i);
        }
        tam--;
    }
    return decimal;
}
//DECODIFICA O COND DA INSTRUÇÃO B<COND>
string decodeCond(char hex){
    switch(hex){
        case '0':
            return "EQ";
            break;
        case '1':
            return "NE";
            break;
        case '2':
            return "CS_HS";
            break;
        case '3':
            return "CC_LO";
            break;
        case '4':
            return "MI";
            break;
        case '5':
            return "PL";
            break;
        case '6':
            return "VS";
            break;
        case '7':
            return "VC";
            break;
        case '8':
            return "HI";
            break;
        case '9':
            return "LS";
            break;
        case 'a':
            return "GE";
            break;
        case 'A':
            return "GE";
            break;
        case 'b':
            return "LT";
            break;
        case 'B':
            return "LT";
            break;
        case 'c':
            return "GT";
            break;
        case 'C':
            return "GT";
            break;
        case 'd':
            return "LE";
            break;
        case 'D':
            return "LE";
            break;
        case 'e':
            return "{AL}";
            break;
        case 'E':
            return "{AL}";
            break;
        default:
            return "ERRO";
            break;
    }
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
            case 'A':
                binario+=hexa;
                break;
            case 'b':
                binario+=hexb;
                break;
            case 'B':
                binario+=hexb;
                break;
            case 'c':
                binario+=hexc;
                break;
            case 'C':
                binario+=hexc;
                break;
            case 'd':
                binario+=hexd;
                break;
            case 'D':
                binario+=hexd;
                break;
            case 'e':
                binario+=hexe;
                break;
            case 'E':
                binario+=hexe;
                break;
            case 'f':
                binario+=hexf;
                break;
            case 'F':
                binario+=hexf;
                break;
            default:
                cout << "ERRO: "<< hex << " inválido!"<<endl;
                exit(1);
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
    fout.open("decoderThumb.out", ios::ate | ios::out | ios::in);
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
    //ASR | ADD | SUB | ADD | SUB
    else if(hex[0]=='1'){
        if(binario[4]=='0'){
            //ASR
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
    else if(hex[0] == '4'){
        //AND | EOR | LSL | LSR
        if(hex[1] == '0'){
            //AND
            if(binario[8] == '0' && binario[9]=='0'){
                    fout << hex << "    AND r" << convertebindec(separabinario(binario,13,3), 3) <<
                    ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
            }
            //EOR
            else if(binario[8] == '0' && binario[9]=='1'){
                    fout << hex << "    EOR r" << convertebindec(separabinario(binario,13,3), 3) <<
                    ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
            }
            //LSL
            else if(binario[8] == '1' && binario[9]=='0'){
                    fout << hex << "    LSL r" << convertebindec(separabinario(binario,13,3), 3) <<
                    ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
            }
            //LSR
            else if(binario[8] == '1' && binario[9]=='1'){
                    fout << hex << "    LSR r" << convertebindec(separabinario(binario,13,3), 3) <<
                    ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
            }
        }
        //ASR | ADC | SBC | ROR
        else if(hex[1] == '1'){
            //ASR
            if(binario[8] == '0' && binario[9]=='0'){
                    fout << hex << "    ASR r" << convertebindec(separabinario(binario,13,3), 3) <<
                    ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
            }
            //ADC
            else if(binario[8] == '0' && binario[9]=='1'){
                    fout << hex << "    ADC r" << convertebindec(separabinario(binario,13,3), 3) <<
                    ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
            }
            //SBC
            else if(binario[8] == '1' && binario[9]=='0'){
                    fout << hex << "    SBC r" << convertebindec(separabinario(binario,13,3), 3) <<
                    ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
            }
            //ROR
            else if(binario[8] == '1' && binario[9]=='1'){
                    fout << hex << "    ROR r" << convertebindec(separabinario(binario,13,3), 3) <<
                    ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
            }
        }
        //TST | NEG | CMP | CMN
        else if(hex[1] == '2'){
            //TST
            if(binario[8] == '0' && binario[9]=='0'){
                    fout << hex << "    TST r" << convertebindec(separabinario(binario,13,3), 3) <<
                    ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
            }
            //NEG
            else if(binario[8] == '0' && binario[9]=='1'){
                    fout << hex << "    NEG r" << convertebindec(separabinario(binario,13,3), 3) <<
                    ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
            }
            //CMP
            else if(binario[8] == '1' && binario[9]=='0'){
                    fout << hex << "    CMP r" << convertebindec(separabinario(binario,13,3), 3) <<
                    ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
            }
            //CMN
            else if(binario[8] == '1' && binario[9]=='1'){
                    fout << hex << "    CMN r" << convertebindec(separabinario(binario,13,3), 3) <<
                    ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
            }
        }
        //ORR | MUL | BIC | MVN
        else if(hex[1] == '3'){
            //ORR
            if(binario[8] == '0' && binario[9]=='0'){
                fout << hex << "    ORR r" << convertebindec(separabinario(binario,13,3), 3) <<
                ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
            }
            //MUL
            else if(binario[8] == '0' && binario[9]=='1'){
                fout << hex << "    MUL r" << convertebindec(separabinario(binario,13,3), 3) <<
                ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
            }
            //BIC
            else if(binario[8] == '1' && binario[9]=='0'){
                fout << hex << "    BIC r" << convertebindec(separabinario(binario,13,3), 3) <<
                ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
            }
            //MVN
            else if(binario[8] == '1' && binario[9]=='1'){
                fout << hex << "    MVN r" << convertebindec(separabinario(binario,13,3), 3) <<
                ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
            }
        }
        //CPY
        else if(hex[1]=='6' && binario[8]=='0' && binario[9]=='0'){
            fout << hex << "    CPY r" << convertebindec(separabinario(binario,13,3), 3) <<
                ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
        }
        //ADD Ld,Hm
        else if(hex[1]=='4' && binario[8]=='0' && binario[9]=='1'){
            fout << hex << "    ADD r" << convertebindec(separabinario(binario,13,3), 3) <<
                ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
        }
        //MOV Ld,Hm
        else if(hex[1]=='6' && binario[8]=='0' && binario[9]=='1'){
            fout << hex << "    MOV r" << convertebindec(separabinario(binario,13,3), 3) <<
                ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
        }
        //ADD Hd,Lm
        else if(hex[1]=='4' && binario[8]=='1' && binario[9]=='0'){
            fout << hex << "    ADD r" << convertebindec(separabinario(binario,13,3), 3) <<
                ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
        }
        //MOV Hd,Lm
        else if(hex[1]=='6' && binario[8]=='1' && binario[9]=='0'){
            fout << hex << "    MOV r" << convertebindec(separabinario(binario,13,3), 3) <<
                ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
        }
        //ADD Hd,Hm
        else if(hex[1]=='4' && binario[8]=='1' && binario[9]=='1'){
            fout << hex << "    ADD r" << convertebindec(separabinario(binario,13,3), 3) <<
                ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
        }
        //MOV Hd,Hm
        else if(hex[1]=='6' && binario[8]=='1' && binario[9]=='1'){
            fout << hex << "    MOV r" << convertebindec(separabinario(binario,13,3), 3) <<
                ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
        }
        //CMP
        else if(hex[1]=='5' && binario[8]=='0' && binario[9]=='1'){
            fout << hex << "    CMP r" << convertebindec(separabinario(binario,13,3), 3) <<
                ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
        }
        //CMP
        else if(hex[1]=='5' && binario[8]=='1' && binario[9]=='0'){
            fout << hex << "    CMP r" << convertebindec(separabinario(binario,13,3), 3) <<
                ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
        }
        //CMP
        else if(hex[1]=='5' && binario[8]=='1' && binario[9]=='1'){
            fout << hex << "    CMP r" << convertebindec(separabinario(binario,13,3), 3) <<
                ", r" << convertebindec(separabinario(binario,10,3), 3)<<endl;
        }
        //BX | BLX
        else if(hex[1]=='7' && binario[13]=='0' && binario[14]=='0' && binario[15]=='0'){
            //BX
            if(binario[8]=='0'){
                fout << hex << "    BX r" << convertebindec(separabinario(binario,9,4), 4)<<endl;
            }//BLX
            else{
                fout << hex << "    BLX r" << convertebindec(separabinario(binario,9,4), 4)<<endl;
            }
        }
        //LDR
        else if(binario[4]=='1'){
            fout << hex << "    LDR r" << convertebindec(separabinario(binario,5,3), 3)<<
            ", [pc, #" << convertebindec(separabinario(binario,8,8), 8) << "]" <<endl;
        }
    }
    //STR | STRH | STRB | LDRSB
    else if(hex[0]=='5'){
        if(binario[4]=='0'){
            //STR
            if(binario[5]=='0' && binario[6]=='0'){
                fout << hex << "    STR r" << convertebindec(separabinario(binario,13,3), 3)<<
                                ", r" << convertebindec(separabinario(binario,10,3), 3) << ", r" <<
                                convertebindec(separabinario(binario,7,3), 3) << endl;
            }
            //STRH
            else if(binario[5]=='0' && binario[6]=='1'){
                fout << hex << "    STRH r" << convertebindec(separabinario(binario,13,3), 3)<<
                                ", r" << convertebindec(separabinario(binario,10,3), 3) << ", r" <<
                                convertebindec(separabinario(binario,7,3), 3) << endl;
            }
            //STRB
            else if(binario[5]=='1' && binario[6]=='0'){
                fout << hex << "    STRB r" << convertebindec(separabinario(binario,13,3), 3)<<
                                ", r" << convertebindec(separabinario(binario,10,3), 3) << ", r" <<
                                convertebindec(separabinario(binario,7,3), 3) << endl;
            }
            //LDRSB
            else if(binario[5]=='1' && binario[6]=='1'){
                fout << hex << "    LDRSB r" << convertebindec(separabinario(binario,13,3), 3)<<
                                ", r" << convertebindec(separabinario(binario,10,3), 3) << ", r" <<
                                convertebindec(separabinario(binario,7,3), 3) << endl;
            }
        }
        //LDR | LDRH | LDRB | LDRSH
        else if(binario[4]=='1'){
            //LDR
            if(binario[5]=='0' && binario[6]=='0'){
                fout << hex << "    LDR r" << convertebindec(separabinario(binario,13,3), 3)<<
                                ", r" << convertebindec(separabinario(binario,10,3), 3) << ", r" <<
                                convertebindec(separabinario(binario,7,3), 3) << endl;
            }
            //LDRH
            else if(binario[5]=='0' && binario[6]=='1'){
                fout << hex << "    LDRH r" << convertebindec(separabinario(binario,13,3), 3)<<
                                ", r" << convertebindec(separabinario(binario,10,3), 3) << ", r" <<
                                convertebindec(separabinario(binario,7,3), 3) << endl;
            }
            //LDRB
            else if(binario[5]=='1' && binario[6]=='0'){
                fout << hex << "    LDRB r" << convertebindec(separabinario(binario,13,3), 3)<<
                                ", r" << convertebindec(separabinario(binario,10,3), 3) << ", r" <<
                                convertebindec(separabinario(binario,7,3), 3) << endl;
            }
            //LDRSH
            else if(binario[5]=='1' && binario[6]=='1'){
                fout << hex << "    LDRSH r" << convertebindec(separabinario(binario,13,3), 3)<<
                                ", r" << convertebindec(separabinario(binario,10,3), 3) << ", r" <<
                                convertebindec(separabinario(binario,7,3), 3) << endl;
            }
        }
    }
    //STR | LDR Ld, [Ln, #immed*4]
    else if(hex[0]=='6'){
        //STR Ld, [Ln, #immed*4]
        if(binario[4]=='0'){
            fout << hex << "    STR r" << convertebindec(separabinario(binario,13,3), 3)<<
            ", [r"<< convertebindec(separabinario(binario,10,3), 3)<<", #" << 
            convertebindec(separabinario(binario,5,5), 5)*4 << "]" <<endl;
        }//LDR Ld, [Ln, #immed*4]
        else{
            fout << hex << "    LDR r" << convertebindec(separabinario(binario,13,3), 3)<<
            ", [r"<< convertebindec(separabinario(binario,10,3), 3)<<", #" << 
            convertebindec(separabinario(binario,5,5), 5)*4 << "]" <<endl;
        }
    }
    //STRB | LDRB Ld, [Ln, #immed]
    else if(hex[0]=='7'){
        //STRB Ld, [Ln, #immed]
        if(binario[4]=='0'){
            fout << hex << "    STRB r" << convertebindec(separabinario(binario,13,3), 3)<<
            ", [r"<< convertebindec(separabinario(binario,10,3), 3)<<", #" << 
            convertebindec(separabinario(binario,5,5), 5) << "]" <<endl;
        }//LDRB Ld, [Ln, #immed]
        else{
            fout << hex << "    LDRB r" << convertebindec(separabinario(binario,13,3), 3)<<
            ", [r"<< convertebindec(separabinario(binario,10,3), 3)<<", #" << 
            convertebindec(separabinario(binario,5,5), 5) << "]" <<endl;
        }
    }
    //STRH | LDRH Ld, [Ln, #immed*2]
    else if(hex[0]=='8'){
        //STRH Ld, [Ln, #immed*2]
        if(binario[4]=='0'){
            fout << hex << "    STRH r" << convertebindec(separabinario(binario,13,3), 3)<<
            ", [r"<< convertebindec(separabinario(binario,10,3), 3)<<", #" << 
            convertebindec(separabinario(binario,5,5), 5)*2 << "]" <<endl;
        }//LDRH Ld, [Ln, #immed*2]
        else{
            fout << hex << "    LDRH r" << convertebindec(separabinario(binario,13,3), 3)<<
            ", [r"<< convertebindec(separabinario(binario,10,3), 3)<<", #" << 
            convertebindec(separabinario(binario,5,5), 5)*2 << "]" <<endl;
        }
    }
    //STR | LDR Ld, [sp, #immed*4]
    else if(hex[0]=='9'){
        //STR Ld, [sp, #immed*4]
        if(binario[4]=='0'){
            fout << hex << "    STR r" << convertebindec(separabinario(binario,5,3), 3)<<
            ", [sp, #" << convertebindec(separabinario(binario,8,8), 8)*4 << "]" <<endl;
        }//LDR Ld, [sp, #immed*4]
        else{
            fout << hex << "    LDR r" << convertebindec(separabinario(binario,5,3), 3)<<
            ", [sp, #" << convertebindec(separabinario(binario,8,8), 8)*4 << "]" <<endl;
        }
    }
    //ADD Ld, pc, #immed*4 | ADD Ld, sp, #immed*4
    else if(hex[0]=='a' || hex[0]=='A'){
        //ADD Ld, pc, #immed*4
        if(binario[4]=='0'){
            fout << hex << "    ADD r" << convertebindec(separabinario(binario,5,3), 3)<<
            ", pc, #" << convertebindec(separabinario(binario,8,8), 8)*4 << endl;
        }//ADD Ld, sp, #immed*4
        else{
            fout << hex << "    ADD r" << convertebindec(separabinario(binario,5,3), 3)<<
            ", sp, #" << convertebindec(separabinario(binario,8,8), 8)*4 << endl;
        }
    }
    else if(hex[0]=='b' || hex[0]=='B'){
        //ADD sp, #immed*4 | SUB sp, #immed*4
        if(hex[1]=='0'){
            //ADD sp, #immed*4
            if(binario[8]=='0'){
                fout << hex << "    ADD sp, #" << convertebindec(separabinario(binario,9,7), 7)*4 << endl;
            }//SUB sp, #immed*4
            else{
                fout << hex << "    SUB sp, #" << convertebindec(separabinario(binario,9,7), 7)*4 << endl;
            }
        }
        //SXTH | SXTB | UXTH | UXTB
        else if(hex[1]=='2'){
            //SXTH
            if(binario[8]=='0' && binario[9]=='0'){
                fout << hex << "    SXTH r" << convertebindec(separabinario(binario,13,3), 3)<<
                                ", r" << convertebindec(separabinario(binario,10,3), 3) << ", r" <<
                                convertebindec(separabinario(binario,7,3), 3) << endl;
            }
            //SXTB
            else if(binario[8]=='0' && binario[9]=='1'){
                fout << hex << "    SXTB r" << convertebindec(separabinario(binario,13,3), 3)<<
                                ", r" << convertebindec(separabinario(binario,10,3), 3) << endl;
            }
            //UXTH
            else if(binario[8]=='1' && binario[9]=='0'){
                fout << hex << "    UXTH r" << convertebindec(separabinario(binario,13,3), 3)<<
                                ", r" << convertebindec(separabinario(binario,10,3), 3) << endl;
            }
            //UXTB
            else if(binario[8]=='1' && binario[9]=='1'){
                fout << hex << "    UXTB r" << convertebindec(separabinario(binario,13,3), 3)<<
                                ", r" << convertebindec(separabinario(binario,10,3), 3) << endl;
            }
        }
        //REV | REV16 | | REVSH
        else if(hex[1]=='A' || hex[1]=='a'){
            //REV
            if(binario[8]=='0' && binario[9]=='0'){
                fout << hex << "    REV r" << convertebindec(separabinario(binario,13,3), 3)<<
                                ", r" << convertebindec(separabinario(binario,10,3), 3) <<
                                convertebindec(separabinario(binario,7,3), 3) << endl;
            }
            //REV16
            else if(binario[8]=='0' && binario[9]=='1'){
                fout << hex << "    REV16 r" << convertebindec(separabinario(binario,13,3), 3)<<
                                ", r" << convertebindec(separabinario(binario,10,3), 3) << endl;
            }
            //REVSH
            else if(binario[8]=='1' && binario[9]=='1'){
                fout << hex << "    REVSH r" << convertebindec(separabinario(binario,13,3), 3)<<
                                ", r" << convertebindec(separabinario(binario,10,3), 3) << endl;
            }
            
        }
        //PUSH | POP
        else if(binario[5]=='1' && binario[6]=='0'){
            //PUSH
            if(binario[4]=='0'){
                //R=0
                if(binario[7]=='0'){
                    fout << hex << "    PUSH {r" << convertebindec(separabinario(binario,8,4), 4)<<
                                ", r" << convertebindec(separabinario(binario,12,4), 4) << "}"<< endl;
                }//R=1
                else{
                    fout << hex << "    PUSH {lr, r" << convertebindec(separabinario(binario,8,4), 4)<<
                                ", r" << convertebindec(separabinario(binario,12,4), 4) << "}"<< endl;
                }
            }//POP
            else{
                //R=0
                if(binario[7]=='0'){
                    fout << hex << "    POP {r" << convertebindec(separabinario(binario,8,4), 4)<<
                                ", r" << convertebindec(separabinario(binario,12,4), 4) << "}" << endl;
                }//R=1
                else{
                    fout << hex << "    POP {pc, r" << convertebindec(separabinario(binario,8,4), 4)<<
                                ", r" << convertebindec(separabinario(binario,12,4), 4) << "}" << endl;
                }
            }
        }
        //SETEND LE | SETEND BE
        else if(hex[1]=='6' && (hex[2]=='A' || hex[2]=='a')){
            //SETEND LE
            if(hex[3]=='0'){
                fout << hex << "    SETEND LE "<< endl;
            }//SETEND BE
            else if(hex[3]=='8'){
                fout << hex << "    SETEND BE " << endl;
            }
        }
        //CPSIE | CPSID
        else if(hex[1]=='6'){
            //CPSIE
            if(hex[2]=='6'){
                fout << hex << "    CPSIE "<< endl;
            }//CPSID
            else if(hex[2]=='7'){
                fout << hex << "    CPSID " << endl;
            }
        }
        //BKPT immed8
        else if(hex[1]=='E' || hex[1]=='e'){
            fout << hex << "    BKPT #" << convertebindec(separabinario(binario,8,8),8) << endl;
        }
    }
    //STMIA | LDMIA Ln!, {register-list}
    else if(hex[0]=='C' || hex[0]=='c'){
        //STMIA
        if(binario[4]=='0'){
            fout << hex << "    STMIA r" << convertebindec(separabinario(binario,5,3), 3)<<
                                "!, {r" << convertebindec(separabinario(binario,8,4), 4)<<
                                ", r"<<convertebindec(separabinario(binario,12,4), 4) << "}"<< endl;
        }//LDMIA
        else{
            fout << hex << "    LDMIA r" << convertebindec(separabinario(binario,5,3), 3)<<
                                "!, {r" << convertebindec(separabinario(binario,8,4), 4)<<
                                ", r"<<convertebindec(separabinario(binario,12,4), 4) << "}"<< endl;
        }
    }
    else if(hex[0]=='D' || hex[0]=='d'){
        //B<cond> instruction_address+4+offset*2
        if(decodeCond(hex[1])!="ERRO"){
            int immed= convertebindec(separabinario(binario,8,8), 8)*2 + 4;
            fout << hex << "    B" << decodeCond(hex[1])<<" #" << std::to_string(immed) <<endl;
                              
        }//Undefined and expected to remain so
        else if(hex[1]=='E' || hex[1]=='e'){
            fout << hex << "    Undefined and expected to remain so" << endl;
        }//SWI immed8
        else if(hex[1]=='F' || hex[1]=='f'){
            fout << hex << "    SWI #" << convertebindec(separabinario(binario,8,8), 8) << endl;
        }
    }
    else if(hex[0]=='E' || hex[0]=='e'){
        //B instruction_address+4+offset*2
        if(binario[4]=='0'){
            int immed= convertebindec(separabinario(binario,5,11), 11)*2 + 4;
            fout << hex << "    B #" << std::to_string(immed) << endl;
        }//BLX ((instruction+4+(poff<<12)+offset*4) &~ 3)
        else if(binario[4]=='1' && binario[15]=='0'){
            int immed= convertebindec(separabinario(binario,5,10), 10)*2 + 4;
            fout << hex << "    BLX #" << std::to_string(immed) << endl;
        }
    }
    else if(hex[0]=='F' || hex[0]=='f'){
        //BL instruction+4+ (poff<<12)+offset*2
        int immed= convertebindec(separabinario(binario,5,11), 11)*2 + 4;
        fout << hex << "    BL #" << std::to_string(immed) << endl;
    }
}
