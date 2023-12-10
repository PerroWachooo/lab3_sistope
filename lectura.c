#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "globals.h"
#include "celda.h"

// Función para comenzar a leer desde una línea específica
void comenzarDesdeLinea(FILE *archivo, int numeroLinea)
{
    // Asumiendo que cada línea tiene un máximo de 4096 caracteres
    char buffer[4096];

    // Mover el puntero de archivo al principio del archivo
    fseek(archivo, 0, SEEK_SET);

    // Leer y descartar las primeras "numeroLinea - 1" líneas
    for (int i = 1; i < numeroLinea; ++i)
    {
        if (fgets(buffer, sizeof(buffer), archivo) == NULL)
        {
            break;
        }
    }
}

// Entrada: nombre del archivo siendo un char.
// Salida: arreglo de celdas (estructura).
// Descripción: Esta función tiene el propósito de leer el archivo de entrada
// y retornar un array de celdas.
Celda *leer_archivo(FILE *archivo, int chucks)
{
    // Se inicializan las variables
    Celda *arreglo;

    // Se lee la primera linea
    char linea[100];
    int tamaño_array = atoi(fgets(linea, 100, archivo));
    if (tamaño_array <= 0)
    {
        printf("Error: No Cumple con el Formato Pedido\n");
        exit(1);
    }
    // Se crea un array de array de caracteres con el tamaño de la primera linea
    arreglo = (Celda *)malloc(sizeof(Celda) * tamaño_array);

    // Luego se comienza a leer linea por linea separando las lineas por " " y se guarda en el array de celdas
    // Leeme el archivo linea por linea
    int i = 0;
    int primer_numero;
    int segundo_numero;
    while (fscanf(archivo, "%d %d", &primer_numero, &segundo_numero) != EOF && i < chucks)
    {
        if (primer_numero < 0 || segundo_numero <= 0)
        {
            printf("Error: No Cumple con el Formato Pedido\n");
            exit(1);
        }
        arreglo[i].posicion = primer_numero;
        arreglo[i].valor = segundo_numero;
        arreglo[i].largo_del_arreglo = tamaño_array;
        i++;
    }
    arreglo[0].largo_del_arreglo = i;

    // Si llegó al final del archivo
    if (feof(archivo))
    {
        final_archivo = 1;
    }

    return arreglo;
}