#include "funciones.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "celda.h"
#include <pthread.h>
#include "argumento.h"
#include "lectura.h"
#include "globals.h"

// Entradas: int posicion_particula, int energia_particula, int posicion_arreglo,
// int energia_arreglo int largo_arreglo
// Salida: float que la energia que queda en la posicion del arreglo
// Funcionamiento: Calcula la energia residual que llega a la celda, si es mayor
// al umbral minimo de energia, se suma la energia del arreglo con el residuo de energia.
double suma_formula(int posicion_particula, int energia_particula, int posicion_arreglo, double energia_arreglo, int largo_arreglo)
{
    double energia_particula_float = (double)energia_particula;
    double largo_arreglo_float = (double)largo_arreglo;

    double raiz = sqrt(abs(posicion_particula - posicion_arreglo) + 1); // se transforma la energia de la particula a float

    double residuo_energia = ((1000 * energia_particula_float) / (largo_arreglo_float * raiz)); // se aplica la formula entregada en enunciado
    double min_energy = (pow(10, -3) / largo_arreglo);                                          // se calcula el umbral minimo de energia

    if (residuo_energia >= min_energy)
    { // si el residuo de energia es mayor al minimo, se le suma a la energia ya existente del material
        return energia_arreglo + residuo_energia;
    }
    else
    {
        return energia_arreglo; // si no, se devuelve la energia del material
    }
}

// Entradas: float energia_maxima, float energia_material
// Salida: int porcentaje de o
// Funcionamiento: Calcula la cantidad de "o" que deberia imprimir considerando como
// 100% la energia maxima y la energia del material como el porcentaje de "o" que se
// debe imprimir.
int o_proporcional(double energia_maxima, double energia_material)
{
    double porcentaje_o = ((energia_material * 100) / energia_maxima);
    return (int)porcentaje_o;
}

void *trabajo_hebra(void *estructura)
{
    argumentos *args = (argumentos *)estructura;
    pthread_mutex_t *semaforo_lectura = args->read;
    pthread_mutex_t *semaforo_escritura = args->write;
    Celda *arreglo_ataque = (Celda *)malloc(sizeof(Celda) * 100);

    // Insertar semaforo
    pthread_mutex_lock(semaforo_lectura);
    if (final_archivo == 1)
    {
        pthread_mutex_unlock(semaforo_lectura);
        pthread_exit(NULL);
    }

    FILE *file = args->file;
    int contador = args->contador;
    int chunks = args->chunks;
    int N = args->largo_celdas;

    // Se comienza a leer el archivo desde la linea que se quedo
    comenzarDesdeLinea(file, contador);

    arreglo_ataque = leer_archivo(file, chunks);
    contador += chunks;

    // Guarda el valor de contador en la estructura
    args->contador = contador;

    pthread_mutex_unlock(semaforo_lectura);

    pthread_mutex_lock(semaforo_escritura);
    double *arreglo_celdas_a_modifiar = args->arreglo_celdas_a_modifiar;
    // Agregar semaforo para escribir
    //  Se comienza a hacer se hace dos ciclos for se recorre todo el arreglo aplicandole la ecuación.
    //  Se guarda el resultado en arreglo de posiciones.
    for (int i = 0; i < arreglo_ataque[0].largo_del_arreglo; i++)
    {
        int array_length = N; // Suponiendo que N es un puntero a la longitud del arreglo
        for (int j = 0; j < array_length; j++)
        {
            arreglo_celdas_a_modifiar[j] = suma_formula(arreglo_ataque[i].posicion, arreglo_ataque[i].valor, j, arreglo_celdas_a_modifiar[j], array_length);
        }
    }
    // Se guarda arreglo de posiciones en la estructura
    args->arreglo_celdas_a_modifiar = arreglo_celdas_a_modifiar;

    pthread_mutex_unlock(semaforo_escritura);
    // liberar semaforo para escribir
    // Se cierra while

    pthread_exit(NULL);
}
