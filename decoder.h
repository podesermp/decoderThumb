#ifndef DECODER_H
#define DECODER_H

bool validarHexadecimal(char *hex, int tam);                //Verifica o char de entrada é um numero hexadecimal. Retorna "True" se sim, senão "False";
void opcode(char *hex);                                     //retorna o numero binario

#endif