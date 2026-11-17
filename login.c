#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"
#include "registro.h"
#include "extras.h"
#include "artista.h"
#include "usuario.h"

// ---------- MENU ----------
int menuLogin() {
    int option;
    while (option) {
        limpiarConsola();
        printf("-----------------\n");
        printf("Inicio de sesion\n");
        printf("-----------------\n");
        printf("Con que tipo de usuario desea iniciar sesion?\n");
        printf("0. Salir\n1. Usuario\n2. Artista\n\nIngrese una opcion: ");
        scanf("%d", &option);
        while (getchar() != '\n');
        switch(option) {

        case 1:
            {
            char nickName[30];
            inicioSesionUsuario(&nickName);
            if(nickName[0] == '\0')
            {
                printf("ERROR en el login");
                return 0;
            }
            menu_usuario(nickName);
            return 1; // los return son para que vuelva al menu anterior
            }
        case 2:
            {
            int id_log=-1;
            inicioSesionArtista(&id_log);
            if(id_log==-1)
            {
                printf("ERROR en el login");
                return 0;
            }
            menu_artista(id_log);
            return 1;
            }
        default:
            {
            return 0;
            }

        }
    }
}



// ---------- LOGIN USUARIO ----------
int verificarUsuarioExiste(char filename[], char nickname[]) {
    FILE *buffer = fopen(filename, "rb");
    if (!buffer) {
        printf("No se pudo abrir el archivo.\n");
        return 0;
    }
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

int verificarContraseniaUsuario(char filename[], char contrasenia[], char nickname[]) {
    FILE *buffer = fopen(filename, "rb");
    if (!buffer) return 0;
    Usuario usr;

    while (fread(&usr, sizeof(Usuario), 1, buffer) == 1) {
        if (strcmp(usr.nickname, nickname)==0) {
            if (strcmp(usr.contrasenia, contrasenia)==0){
                printf("Contrasenia correcta!\n");
                esperarLimpieza(2);
                fclose(buffer);
                return 1;
            }
        }
    }

    fclose(buffer);
    printf("La contrasenia no es valida!\n");
    return 0;
}


void inicioSesionUsuario(char *nickname) {
    char contrasenia[20];
    FILE *buffer = fopen("usuarios.bin", "rb");
    limpiarConsola();
    if (!buffer) {
        printf("ERROR: No se pudo abrir el archivo.\n");
        esperarLimpieza(2);
        return;

    }
    printf("-----------------\n");
    printf("Inicio de sesion (Usuario)\n");
    printf("-----------------\n");
    do {
        printf("Ingrese su nickname (Usuario): ");
        scanf("%s", nickname);
    } while(verificarUsuarioExiste("usuarios.bin", nickname) == 0);

    do {
        printf("Ingrese la contrasenia: ");
        scanf("%s", contrasenia);
    } while(verificarContraseniaUsuario("usuarios.bin", contrasenia, nickname) == 0);

    fclose(buffer);
}


// ---------- LOGIN ARTISTA ----------

int verificarArtistaExiste(char filename[], char nickname[]) {
    FILE *buffer = fopen(filename, "rb");
    if (!buffer) return -1;
    Artista art;


    while (fread(&art, sizeof(Artista), 1, buffer) == 1) {
        if (strcmp(art.nickname, nickname)==0) {
            fclose(buffer);
            return 1;
        }
    }

    fclose(buffer);
    printf("El artista no existe!\n");
    return 0;
}

int verificarContraseniaArtista(char filename[], char contrasenia[], char nickname[]) {
    FILE *buffer = fopen(filename, "rb");
    if (!buffer) return 0;
    Artista art;

    while (fread(&art, sizeof(Artista), 1, buffer) == 1) {
        if (strcmp(art.nickname, nickname)==0) {
            if (strcmp(art.contrasenia, contrasenia)==0){
                printf("Contrasenia correcta!\n");
                esperarLimpieza(2);
                fclose(buffer);
                return 1;
            }
        }
    }

    fclose(buffer);
    printf("La contrasenia no es valida!\n");
    return 0;
}


void inicioSesionArtista(int* id_log) {

    char nickname[30];
    char contrasenia[20];

    FILE *buffer = fopen("Artistas.dat", "rb");
    limpiarConsola();
    if (!buffer) {
        printf("ERROR: No se pudo abrir el archivo.\n");
        esperarLimpieza(2);
        return;
    }
    printf("-----------------\n");
    printf("Inicio de sesion (Artista)\n");
    printf("-----------------\n");
    do {
        printf("Ingrese su nickname (Artista): ");
        scanf("%s", nickname);
    } while(verificarArtistaExiste("Artistas.dat", nickname) == 0);

    do {
        printf("Ingrese la contrasenia: ");
        scanf("%s", contrasenia);
    } while(verificarContraseniaArtista("Artistas.dat", contrasenia, nickname) == 0);

    int id_encontrado=buscar_id_artista(nickname);

    if(id_encontrado==-1){
            printf("Error buscando ID. \n");
            fclose(buffer);
            return;
    }

    (*id_log)=id_encontrado;

    fclose(buffer);
}
int buscar_id_artista(char nickname[])
{
    int id_buscado=0;

    FILE *buffer = fopen("Artistas.dat", "rb");

    if (!buffer) return -1;

    Artista art;


    while (fread(&art, sizeof(Artista), 1, buffer) == 1) {
        if (strcmp(art.nickname, nickname)==0)
        {
            id_buscado=art.IdArtista;
            fclose(buffer);
            return id_buscado;
        }
    }

    fclose(buffer);
    return id_buscado;
}

