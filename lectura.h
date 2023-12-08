#include "celda.h"
#ifndef LECTURA_H
#define LECTURA_H

// Entrada: nombre del archivo siendo un char.
// Salida: arreglo de celdas (estructura).
// Descripción: Esta función tiene el propósito de leer el archivo de entrada
// y retornar un array de celdas.
Celda *leer_archivo(FILE *archivo, int chucks);

void comenzarDesdeLinea(FILE *archivo, int numeroLinea);

#endif