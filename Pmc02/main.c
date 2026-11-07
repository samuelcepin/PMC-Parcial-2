/*************************************************************************************/
/*                  Programación para mecatrónicos                                   */
/*  Nombre:    Samuel Cepin                                                          */
/*  Matricula: 2024-0566                                                             */
/*  Seccion:   Sabados                                                               */
/*  Practica:  Parcial 2                                                             */
/*  Fecha:     06/11/2026                                                            */
/*  Link Practica: https://github.com/samuelcepin/PMC-Parcial-2                      */
/*************************************************************************************/

#include <stdio.h>
#include <string.h>
#include "reto.h"

// Matriz global exigida por la rúbrica
int muestras[MAX_UNIDADES][MAX_MUESTRAS];

int main(void) {
    int n, m, q;
    Registro registros[MAX_UNIDADES];

    // 1. Leer los tres primeros datos generales
    if (scanf("%d %d %d", &n, &m, &q) != 3) {
        printf("ERROR\n");
        return 0;
    }

    // Validar dominios estrictos (n: 1-20, m: 1-8, q: 1-9999)
    if (n < 1 || n > 20 || m < 1 || m > 8 || q < 1 || q > 9999) {
        printf("ERROR\n");
        return 0;
    }

    // 2. Leer los datos de cada unidad
    for (int i = 0; i < n; i++) {
        // Leer id, nombre (máximo 15 caracteres), tipo y parámetro p
        if (scanf("%d %15s %d %d", &registros[i].id, registros[i].nombre, 
                  &registros[i].config.tipo, &registros[i].config.p) != 4) {
            printf("ERROR\n");
            return 0;
        }

        // Validar dominios de la unidad (id: 1-9999, tipo: 0 o 1, p: 0-100)
        if (registros[i].id < 1 || registros[i].id > 9999 ||
            (registros[i].config.tipo != 0 && registros[i].config.tipo != 1) ||
            registros[i].config.p < 0 || registros[i].config.p > 100) {
            printf("ERROR\n");
            return 0;
        }

        // Validar que el ID no esté duplicado revisando los anteriores
        for (int k = 0; k < i; k++) {
            if (registros[i].id == registros[k].id) {
                printf("ERROR\n");
                return 0;
            }
        }

        // 3. Leer las muestras de esta unidad directamente a la matriz
        for (int j = 0; j < m; j++) {
            int x;
            // Leer y validar que la muestra x esté entre 0 y 100
            if (scanf("%d", &x) != 1 || x < 0 || x > 100) {
                printf("ERROR\n");
                return 0;
            }
            muestras[i][j] = x;
        }
    }

    // TODO: Paso 3 - Calcular la histéresis (score y estado)

    return 0;
}