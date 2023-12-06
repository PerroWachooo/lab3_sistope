#ifndef CELDA_H
#define CELDA_H

// Estructura usada para almacenar los datos del archivo de entrada, todo esto para poder
// usarlo en el resto del programa. (Durante el cálculo de la ecuación)
typedef struct
{
    int posicion;          // Posición de la particula
    int valor;             // Energia del impacto
    int largo_del_arreglo; // Se guarda el largo del arreglo de todas formas
} Celda;

#endif