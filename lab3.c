#include <stdio.h>
#include <stdlib.h> // Se utiliza para atoi
#include <getopt.h>
#include <unistd.h>
#include <sys/wait.h>
#include "celda.h"
#include "lectura.h"
#include <pthread.h>
#include "salida.h"
#include "funciones.h"
#include "argumento.h"

int main(int argc, char *argv[])
{
    // Se declaran variables y se inicializan
    int option;
    char *N = "0"; // Numero de celdas
    char *H = "0"; // numero hebras a generar
    char *c = "0"; // numero de chunks
    char *p = "0";
    char *input_file = NULL;
    char *output_file = NULL;
    char *show = "0";

    int final_archivo = 0; // Indica si se llego al final del archivo, 0= no se ha llegado, 1= se llego

    pthread_mutex_t *lectura;
    pthread_mutex_t *escritura;

    // Se utiliza get opt para extraer -N con el número de celdas
    // -i con el nombre del archivo de entrada, -o con el nombre del archivo de salida
    // -D que permite ver por consola el resultado.
    while ((option = getopt(argc, argv, "N:H:i:o:c:D")) != -1)
    {
        switch (option)
        {
        case 'N':

            // Se guarda el número de celdas
            N = optarg;
            // Se verifica que n sea un numero entero
            if (atoi(N) < 0)
            {
                printf("Error: N debe ser mayor a 0\n");
                exit(1);
            }
            break;

        case 'H':

            // Se guarda el número de Hebras a crear
            H = optarg;
            // Se verifica que P sea un numero entero
            if (atoi(H) < 0)
            {
                printf("Error: H debe ser mayor a 0\n");
                exit(1);
            }
            break;

        case 'i':

            // Se guarda el nombre del archivo de entrada
            input_file = optarg;
            break;

        case 'o':
            // Se guarda el nombre del archivo de salida
            output_file = optarg;
            break;

        case 'c':
            // Se guarda el número de chunks
            c = optarg;
            // Se verifica que c sea un numero entero
            if (atoi(c) < 0)
            {
                printf("Error: c debe ser mayor a 0\n");
                exit(1);
            }
            break;

        case 'D':
            show = "1";
            break;
        default:
            // Se muestra un mensaje de error
            printf("Error: Opción no válida\n");
            break;
        }

        // Verificaciones de datos ingresados
    }
    if (atoi(N) == 0)
    {
        printf("Error: No se ingresó el número de celdas\n");
        exit(1);
    }
    if (atoi(H) == 0)
    {
        printf("Error: No se ingresó el número de Hebras a crear\n");
        exit(1);
    }
    if (atoi(c) == 0)
    {
        printf("Error: No se ingresó el número de chunks\n");
        exit(1);
    }
    if (input_file == NULL)
    {
        printf("Error: No se ingresó el nombre del archivo de entrada\n");
        exit(1);
    }
    if (output_file == NULL)
    {
        printf("Error: No se ingresó el nombre del archivo de salida\n");
        exit(1);
    }

    // Se crea arreglo de celdas global
    double *arreglo_posiciones = (double *)malloc(sizeof(double) * atoi(N));

    // Se lee el archivo de entrada
    FILE *archivo = fopen(input_file, "r");
    if (archivo == NULL)
    {
        printf("Error: Archivo no encontrado\n");
        exit(1);
    }

    // Se lee la primera linea del archivo de entrada y se crea un array de array de celdas
    // con el tamaño de la primera linea.
    // Moverse al final del archivo
    fseek(archivo, 0, SEEK_END);

    // Obtener la posición actual (tamaño del archivo en bytes)
    long tamaño = ftell(archivo);

    if (tamaño == 0)
    {
        printf("El archivo está vacío.\n");
        exit(1);
    }

    // Volver al inicio del archivo
    fseek(archivo, 0, SEEK_SET);
    int contador = 0;

    // Se crea el struct de argumentos para las hebras
    argumentos *args = (argumentos *)malloc(sizeof(argumentos));
    args->arreglo_celdas_a_modifiar = arreglo_posiciones;
    args->read = lectura;
    args->write = escritura;
    args->contador = 0;
    args->chunks = atoi(c);
    args->file = archivo;
    args->largo_celdas = atoi(N);

    // Creamos las hebras hijas
    pthread_t hebras_hijas[atoi(N)];
    for (int i = 0; i < atoi(N); i++)
    {
        pthread_create(&hebras_hijas[i], NULL, trabajo_hebra, (void *)args);
    }

    // Ejecutamos las hebras hijas
    for (int i = 0; i < atoi(N); i++)
    {
        pthread_join(hebras_hijas[i], NULL);
    }

    close(fileno(archivo));

    // Se  imprime mensaje de termino
    printf("Termino de ejecutarse las hebras\n");

    // // Encuentra el valor maximo del arreglo_posiciones
    // double max = 0;
    // int posicion_max = 0;
    // for (int i = 0; i < atoi(N); i++)
    // {
    //     if (arreglo_posiciones[i] > max)
    //     {
    //         max = arreglo_posiciones[i];
    //         posicion_max = i;
    //     }
    // }

    // // Se escribe el archivo de salida
    // escribir_archivo(output_file, arreglo_posiciones, atoi(N), posicion_max, max);

    // // Se muestra el arreglo por consola
    // salida_consola(atoi(N), input_file, output_file, atoi(show), arreglo_posiciones, max);
}
