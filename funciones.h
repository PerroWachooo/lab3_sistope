#ifndef FUNCIONES_H
#define FUNCIONES_H
// Entradas: int posicion_particula, int energia_particula, int posicion_arreglo,
// int energia_arreglo int largo_arreglo
// Salida: float que la energia que queda en la posicion del arreglo
// Funcionamiento: Calcula la energia residual que llega a la celda, si es mayor
// al umbral minimo de energia, se suma la energia del arreglo con el residuo de energia.

double suma_formula(int posicion_particula, int energia_particula, int posicion_arreglo, double energia_arreglo, int largo_arreglo);

// Entradas: float energia_maxima, float energia_material
// Salida: int porcentaje de o
// Funcionamiento: Calcula la cantidad de "o" que deberia imprimir considerando como
// 100% la energia maxima y la energia del material como el porcentaje de "o" que se
// debe imprimir.

int o_proporcional(double energia_maxima, double energia_material);
#endif