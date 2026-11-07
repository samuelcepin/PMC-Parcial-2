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

// Función obligatoria para calcular la histéresis de una unidad
int calcular(int vector_muestras[], int m, int tipo, int p, int *estado) {
    int score = 0;
    *estado = tipo; // Inicie encendido=tipo y score=0[cite: 1]

    for (int i = 0; i < m; i++) {
        int x = vector_muestras[i];
        
        // Si está apagado y x >= p+10, encienda y sume 1 a score[cite: 1]
        if (*estado == 0 && x >= (p + 10)) {
            *estado = 1;
            score++;
        } 
        // Si está encendido y x <= p, apague[cite: 1]
        else if (*estado == 1 && x <= p) {
            *estado = 0;
        }
        // En los demás casos conserva el estado[cite: 1]
    }
    
    return score;
}

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

    // 3. Calcular la histéresis e imprimir resultados individuales
    // Calcule score y estado por separado para cada registro[cite: 1]
    for (int i = 0; i < n; i++) {
        int estado_final;
        
        // Llamamos a la función enviando la fila de la matriz y recibiendo el estado por referencia
        int score_final = calcular(muestras[i], m, registros[i].config.tipo, registros[i].config.p, &estado_final);
        
        // Guardamos los cálculos en el registro de la unidad
        registros[i].score = score_final;
        registros[i].estado = estado_final;
        
        // Para entrada válida imprima, en el orden original, una línea por unidad: id score estado[cite: 1]
        printf("%d %d %d\n", registros[i].id, registros[i].score, registros[i].estado);
    }

    // TODO: Paso 4 - Calcular total recursivo, ordenar e imprimir TOTAL, ORDER y FIND

    return 0;
}