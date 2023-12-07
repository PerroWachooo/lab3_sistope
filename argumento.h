#ifndef ARGUMENTO_H
#define ARGUMENTO_H

#include <pthread.h>
#include <stdio.h>

// Estructura para los argumentos
typedef struct
{
    pthread_mutex_t *read;
    pthread_mutex_t *write;
    double *arreglo_celdas_a_modifiar;
    FILE *file;
    int contador;
    int chunks;
    int largo_celdas;

} argumentos;

#endif