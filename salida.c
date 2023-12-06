#include <stdio.h>
#include <stdlib.h>
#include "salida.h"
#include "celda.h"
#include "funciones.h"

// Entrada: nombre del archivo siendo un char, arreglo de posiciones siendo un double,
// largo del arreglo siendo un int, posicion maxima siendo un int y el maximo siendo un double.
// Salida: No tiene.
// Descripción: Esta función tiene el propósito de crear un archivo de salida con el nombre y
// el contenido que se le entrega en el arreglo de posiciones.
void escribir_archivo(char *nombre_archivo, double *arreglo_posiciones, int N, int posicion_max, double max)
{
    // funcion para crear un archivo

    FILE *archivo = fopen(nombre_archivo, "w");
    if (archivo == NULL)
    {
        printf("Error: No se pudo crear el archivo de salida\n");
        exit(1);
    }

    // Se imrpime el material com mas energia
    fprintf(archivo, "%d : %f \n", posicion_max, max);
    // Se imprime el arreglo de posiciones en el archivo de salida
    for (int i = 0; i < N; i++)
    {
        fprintf(archivo, "%d:  %f\n", i, arreglo_posiciones[i]);
    }
}

// Entrada: N siendo de tipo int, input_file siendo un char, output_file siendo un char, show
// siendo un int, arreglo_ataque siendo un arreglo de celdas, arreglo_posiciones siendo un arreglo
// de doubles y max siendo un double.
// Salida: No tiene.
// Descripción: Esta función tiene el propósito de imprimir en consola el arreglo de posiciones.
void salida_consola(int N, char *input_file, char *output_file, int show, double *arreglo_posiciones, double max)
{
    if (show == 0)
    {
        return;
    }

   
    // Se imprime arreglo de posiciones con su grafico
    for (int i = 0; i < N; i++)
    {
        printf("%d  %f | ", i, arreglo_posiciones[i]);

        for (int t = 0; t < o_proporcional(max, arreglo_posiciones[i]); t++)
        {
            printf("o");
        }
        printf("\n");
    }
}