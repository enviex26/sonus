#include <stdio.h>
#include <stdlib.h>
#include "registro.h"
#include "login.h"
#include "extras.h"

int main(void){
    int option;
// EN LOS CASES, AGREGAR OTRO MENU PARA LAS FUNCIONALIDADES
// QUE SOLO SEA ACCESIBLE SI EL USUARIO INICIO SESIÓN

    while (option) {
        limpiarConsola();
        printf("------------\n");
        printf("Bienvenido a Sonus!\n");
        printf("------------\n");
        printf("Que desea hacer?\n");
        printf("0. Salir\n1. Iniciar Sesion\n2. Registro\n\nIngrese una opcion: ");
        scanf("%d", &option);


        switch(option) {

        case 1:
            limpiarConsola();
            menuLogin();
            break;

        case 2:
            limpiarConsola();
            menu_registro();
            break;

        default:
            return 0;

        }
    }



}
