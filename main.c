#include <stdio.h>
#include <stdlib.h>
#include "registro.h"
#include "login.h"

int main(void){
    int option;
    printf("------------\n");
    printf("Bienvenido a Sonus!\n");
    printf("------------\n");



    while (option) {
        printf("Que desea hacer?\n");
        printf("1. Iniciar Sesion\n2. Registro\n3. Salir\nIngrese una opcion: ");
        scanf("%d", &option);


        switch(option) {
        case 1:
            menuInicioSesion();
            break;

        case 2:
            menu_registro();
            break;
        case 3:
            return 0;
        }
    }



}
