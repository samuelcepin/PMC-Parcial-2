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

// Función para calcular la histéresis
int calcular(int vector_muestras[], int m, int tipo, int p, int *estado) {
    int score = 0;
    *estado = tipo; 

    for (int i = 0; i < m; i++) {
        int x = vector_muestras[i];
        if (*estado == 0 && x >= (p + 10)) {
            *estado = 1;
            score++;
        } else if (*estado == 1 && x <= p) {
            *estado = 0;
        }
    }
    return score;
}

// Función recursiva obligatoria para sumar los scores
int total_rec(Registro registros[], int n) {
    if (n == 0) {
        return 0;
    }
    return registros[n - 1].score + total_rec(registros, n - 1);
}

int main(void) {
    int n, m, q;
    Registro registros[MAX_UNIDADES];

    // 1. Leer los tres primeros datos generales
    if (scanf("%d %d %d", &n, &m, &q) != 3) {
        printf("ERROR\n");
        return 0;
    }

    if (n < 1 || n > 20 || m < 1 || m > 8 || q < 1 || q > 9999) {
        printf("ERROR\n");
        return 0;
    }

    // 2. Leer los datos de cada unidad
    for (int i = 0; i < n; i++) {
        if (scanf("%d %15s %d %d", &registros[i].id, registros[i].nombre, 
                  &registros[i].config.tipo, &registros[i].config.p) != 4) {
            printf("ERROR\n");
            return 0;
        }

        if (registros[i].id < 1 || registros[i].id > 9999 ||
            (registros[i].config.tipo != 0 && registros[i].config.tipo != 1) ||
            registros[i].config.p < 0 || registros[i].config.p > 100) {
            printf("ERROR\n");
            return 0;
        }

        for (int k = 0; k < i; k++) {
            if (registros[i].id == registros[k].id) {
                printf("ERROR\n");
                return 0;
            }
        }

        for (int j = 0; j < m; j++) {
            int x;
            if (scanf("%d", &x) != 1 || x < 0 || x > 100) {
                printf("ERROR\n");
                return 0;
            }
            muestras[i][j] = x;
        }
    }

    // 3. Calcular e imprimir resultados individuales
    for (int i = 0; i < n; i++) {
        int estado_final;
        int score_final = calcular(muestras[i], m, registros[i].config.tipo, registros[i].config.p, &estado_final);
        
        registros[i].score = score_final;
        registros[i].estado = estado_final;
        
        printf("%d %d %d\n", registros[i].id, registros[i].score, registros[i].estado);
    }

    // 4. Calcular e imprimir el total recursivo
    int suma_total = total_rec(registros, n);
    printf("TOTAL %d\n", suma_total);

    // 5. Ordenar por Score (Mayor a Menor) y desempatar por ID (Menor a Mayor)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (registros[j].score < registros[j + 1].score || 
               (registros[j].score == registros[j + 1].score && registros[j].id > registros[j + 1].id)) {
                Registro temp = registros[j];
                registros[j] = registros[j + 1];
                registros[j + 1] = temp;
            }
        }
    }

    printf("ORDER");
    for (int i = 0; i < n; i++) {
        printf(" %d", registros[i].id);
    }
    printf("\n");

    // 6. Buscar la unidad 'q' y mostrar su score
    int score_encontrado = -1;
    for (int i = 0; i < n; i++) {
        if (registros[i].id == q) {
            score_encontrado = registros[i].score;
            break;
        }
    }
    printf("FIND %d %d\n", q, score_encontrado);

    return 0;
}