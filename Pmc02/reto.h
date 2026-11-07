#ifndef RETO_H
#define RETO_H

// Constantes para las capacidades máximas exigidas
#define MAX_UNIDADES 20
#define MAX_MUESTRAS 8

// 1. Estructura anidada para la configuración (tipo y p)
typedef struct {
    int tipo;
    int p;
} Configuracion;

// 2. Estructura principal del registro de la celda
typedef struct {
    int id;
    char nombre[16];      // De 1 a 15 caracteres alfanuméricos + '\0'
    Configuracion config; // Estructura anidada exigida
    int score;
    int estado;
} Registro;

// Prototipos de las funciones obligatorias
int calcular(int muestras_unidad[], int m, int tipo, int p, int *estado);
int total_rec(Registro registros[], int n);
void ordenar(Registro registros[], int n);
int buscar(Registro registros[], int n, int q);

#endif