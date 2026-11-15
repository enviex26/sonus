#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"
#include "registro.h"

void inicioSesion() {
}

int verificarUsuarioExiste(char filename[], char nickname[]) {
    FILE *buffer = fopen(filename, "rb");
    if (!buffer) return -1;
    Usuario usr;


    while (fread(&usr, sizeof(Usuario), 1, buffer) == 1) {
        if (strcmp(usr.nickname, nickname)==0) {
            fclose(buffer);
            return 1;
        }
    }

    fclose(buffer);
    printf("El usuario no existe!\n");
    return 0;
}

int verificarContrasenia(char filename[], char contrasenia[], char nickname[]) {
    FILE *buffer = fopen(filename, "rb");
    if (!buffer) return -1;
    Usuario usr;
    int flag = 0;

    while (fread(&usr, sizeof(Usuario), 1, buffer) == 1) {
        if (strcmp(usr.nickname, nickname)==0) {
            if (strcmp(usr.contrasenia, contrasenia)==0){
                printf("Contrasenia correcta!\n");
                fclose(buffer);
                return 1;
            }
        }
    }

    fclose(buffer);
    printf("La contrasenia no es valida!\n");
    return 0;
}


void menuInicioSesion() {
    int ingresado = 0;
    char nickname[30];
    char contrasenia[20];

    printf("---------\n");
    do {
        printf("Ingrese su nombre de usuario: ");
        scanf("%s", nickname);
    } while(verificarUsuarioExiste("usuarios.bin", nickname) == 0);

    do {
        printf("Ingrese la contrasenia: ");
        scanf("%s", contrasenia);
    } while(verificarContrasenia("usuarios.bin", contrasenia, nickname) == 0);
}
