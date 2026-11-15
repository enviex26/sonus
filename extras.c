#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void limpiarConsola() {
    printf("\033[H\033[2J"); // caracteres especiales para limpiar consola
    fflush(stdout); // limpieza buffer
}

void esperarLimpieza(int segundos) {
    time_t start = time(NULL); // consula el reloj del sistema
    while(difftime(time(NULL), start) < segundos); // compara los segundos que pasaron con los que hay que esperar
}
