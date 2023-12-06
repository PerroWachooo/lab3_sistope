#ifndef SALIDA_H
#define SALIDA_H
#include "celda.h"

// Entrada: nombre del archivo siendo un char, arreglo de posiciones siendo un double,
// largo del arreglo siendo un int, posicion maxima siendo un int y el maximo siendo un double.
// Salida: No tiene.
// Descripción: Esta función tiene el propósito de crear un archivo de salida con el nombre y
// el contenido que se le entrega en el arreglo de posiciones.
void escribir_archivo(char *nombre_archivo, double *arreglo_posiciones, int N, int posicion_max, double max);

// Entrada: N siendo de tipo int, input_file siendo un char, output_file siendo un char, show
// siendo un int, arreglo_ataque siendo un arreglo de celdas, arreglo_posiciones siendo un arreglo
// de doubles y max siendo un double.
// Salida: No tiene.
// Descripción: Esta función tiene el propósito de imprimir en consola el arreglo de posiciones.

void salida_consola(int N, char *input_file, char *output_file, int show, double *arreglo_posiciones, double max);

#endif