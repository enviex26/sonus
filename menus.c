#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extras.h"
#include "registro.h"
#include "artista.h"
#include "usuario.h"
#include "login.h"
#include "menus.h"

static int tipoSesion = 0;
static int sesionIdArtista = -1;

int menuInicial(char sesionNickname[]) {
    int option = 0;

    do {
        limpiarConsola();
        printf("------------\n");
        printf("Bienvenido a Sonus!\n");
        printf("------------\n");
        printf("Que desea hacer?\n");
        printf("1. Iniciar Sesion\n2. Registro\n0. Salir\n\nIngrese una opcion: ");
        scanf("%d", &option);


        switch(option) {

        case 1:
            limpiarConsola();
            menuLogin(sesionNickname);
            return 1;

        case 2:
            limpiarConsola();
            menu_registro(sesionNickname);
            return 1;;

        default:
            return 0;

        }
    } while (option);

}

int menuSesionIniciada(char sesionNickname[]) {
    int option = 0;

    do {
        limpiarConsola();
        printf("------------\n");
        printf("Bienvenido a Sonus, %s!\n", sesionNickname);
        printf("------------\n");
        printf("Que desea hacer?\n");
        printf("1. Menu Principal\n2. Cerrar Sesion\n0. Salir\n\nIngrese una opcion: ");
        scanf("%d", &option);


        switch(option) {

        case 1:
            limpiarConsola();
            if (tipoSesion == 1) { // Usuario
                menu_usuario(sesionNickname);
            } else if (tipoSesion == 2) { // Artista
                menu_artista(sesionIdArtista);
            } else if (tipoSesion == 3) { // Admin
                menu_admin(sesionNickname);
            }
            return 1;

        case 2:
            limpiarConsola();
            sesionNickname[0] = '\0';
            return 1;

        default:
            return 0;

        }
    } while (option);

}

int menuLogin(char sesionNickname[]) {
    int option = 0;
    do {
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
            char nickname[30];
            if (inicioSesionUsuario(nickname) == 1) {
                strcpy(sesionNickname, nickname);

                if (strcmp(nickname, "admin") == 0) {
                    tipoSesion = 3;
                    menu_admin(nickname);
                } else {
                    tipoSesion = 1;
                    menu_usuario(nickname);
                }

            }
            if(nickname[0] == '\0')
            {
                printf("ERROR en el login");
                return 0;
            }


            return 1; // los return son para que vuelva al menu anterior
            }
        case 2:
            {
            int id_log=-1;
            if (inicioSesionArtista(&id_log, sesionNickname) == 1) {
                tipoSesion = 2;
                sesionIdArtista = id_log;
                menu_artista(id_log);
            }
            return 1;
            }
        default:
            {
            return 0;
            }

        }
    } while (option);
}


void menu_registro() {
    int option=-1;
    printf("-----------------\n");
    printf("Registro\n");
    printf("-----------------\n");
    printf("Que tipo de usuario desea registrar\n");
    printf("1. Usuario\n");
    printf("2. Artista\n");
    printf("0. Salir\n");
    printf("\nIngrese una opcion: ");
    scanf("%d", &option);

        switch (option)
        {
        case 1:
            {
                int capacidad=1;
                int validos = 0;
                Usuario *usuarios=NULL;
                usuarios=crear_arreglo_din(capacidad);

                if(!usuarios)
                    return;

            if(validos==capacidad)
            {
            usuarios=redimensionar_arr(usuarios,&capacidad);
                if(validos==capacidad)
                {
                    printf("Error al redimensionar el arreglo!");
                    return;
                }
            }

            if(validos<capacidad)
            {
                if(crear_usuario(usuarios,&validos)==-1)
                {
                    printf("ERROR en la creacion de usuario.");
                    free(usuarios);
                    usuarios=NULL;
                    return;
                }
            }

            int exito= dumpearUsuariosABin("usuarios.bin",&usuarios[validos-1]);
            if(exito==-1){
                printf("Error a pasar el usuario al archivo.");
                free(usuarios);
                usuarios=NULL;
                return;
            }
            free(usuarios);
            usuarios=NULL;
            break;
        }
        case 2:
            {
            Artista b;
            int exito=cargar_artista(&b);
            if(exito==-1)
                return;

            exito=0;
            exito=pasar_artista_a_archivo(b);
            if(exito!=1)
            {
                printf("Error al pasar al archivo.\n");
                return;
            }
            else
            {
                printf("Artista registrado, bienvenido a Sonus.\n");
                esperarLimpieza(2);
            }
            mostrarArtistas();
            break;
            }
        default:
            return;
        }
}

void menu_usuario(char nickNameUsuario[])
{
    int opcion = -1;
    while (opcion != 0)
    {
        limpiarConsola();
        printf("-----------------\n");
        printf("Menu Principal (Usuario)\n");
        printf("-----------------\n");
        printf("1. Ver Catalogo por Artista \n");
        printf("2. Ver Canciones por Album: \n");
        printf("3. Ver Informacion Detallada de Canci—n\n");
        printf("4. Calificar Cancion\n");
        printf("5. Ver Mis Calificaciones\n");
        printf("0. Salir\n");
        printf("\nIngrese una opcion: ");
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 0:
                break;
            case 1:
                {
                    verCatalogoporArtista("Artistas.dat", "Albumes.dat", "Canciones.dat");
                    break;
                }
            case 2:
                {
                    verCancionesPorAlbum("Albumes.dat", "Canciones.dat");
                    break;
                }
            case 3:
                {
                    infoDetalladaCancion("Canciones.dat", "Calificaciones.dat");
                    break;
                }
            case 4:
                {
                    calificarCancion("Canciones.dat", "Calificaciones.dat", nickNameUsuario);
                    break;
                }
            case 5:
                {
                    verMisCalificaciones("Calificaciones.dat", nickNameUsuario);
                    break;
                }
            default:
                {
                    printf("Opcion Incorrecta\n");
                    break;
                }
        }
    }
}

void menu_artista(int id_Artista_ing)
{
    int opcion=-1;
    while(opcion!=0)
    {
        limpiarConsola();
        printf("-----------------\n");
        printf("Menu Principal (Artista)\n");
        printf("-----------------\n");
        printf("1. Albumes \n");
        printf("2. Canciones \n");
        printf("0. Salir \n");
        printf("\nIngrese una opcion: ");


        scanf("%d",&opcion);
        switch(opcion)
        {
        case 0:
            {
                return;
            }
            case 1:
                {
                    char option;
                    printf("Ingrese una opcion: \n");
                    printf("a. Agregar Album. \n");
                    printf("b. Modificar Album (Solo tus albumes). \n");
                    scanf(" %c", &option);
                    switch(option)
                    {
                        case 'a':
                            {
                                Album a;
                                int exito=agregar_album(&a, id_Artista_ing);
                                if(exito==-1)
                                {
                                    printf("No se pudo ingresar el album");
                                    return;
                                }
                                if(pasar_archivo_album(a)==-1)
                                {
                                 printf("ERROR en el archivo.\n");
                                }
                                break;
                            }
                        case 'b':
                            {
                                modificar_album(id_Artista_ing);
                                break;
                            }
                        default:
                            {
                                printf("Opcion invalida.\n");
                                break;
                            }
                    }//Finaliza Switch Interno

                    //Primer Switch
                    break;
                }

            case 2:
                {
                    char option;
                    printf("Ingrese una opcion: \n");
                    printf("a. Agregar Cancion. \n");
                    printf("b. Modificar Cancion (Solo tus canciones). \n");
                    scanf(" %c", &option);
                    switch(option)
                    {
                        case 'a':
                            {
                                Cancion c;
                                int exito=agregar_cancion(&c, id_Artista_ing);
                                if(exito==-1)
                                {
                                    printf("No se pudo ingresar la cancion.");
                                    return;
                                }
                                if(pasar_archivo_cancion(c)==-1)
                                {
                                 printf("ERROR en el archivo.\n");
                                }
                                break;
                            }
                        case 'b':
                            {
                                modificar_cancion(id_Artista_ing);
                                break;
                            }
                        default:
                            {
                                printf("Opcion invalida.\n");
                                break;
                            }
                    }//Finaliza Switch Interno

                    //Primer Switch
                    break;
                }

            default:
                {
                    printf("Opcion Incorrecta\n");

                }
        }
    }
}

void menu_admin(char sesionNickname[])
{
    int opcion=-1;
    int seguir = -1;
    int idArtista = -1;
    int idUsuario = -1;
    while(opcion!=0)
    {
        limpiarConsola();
        printf("-----------------\n");
        printf("Menu Principal (Admin)\n");
        printf("-----------------\n");
        printf("1. Mostrar todos los usuarios\n");
        printf("2. Mostrar todos los Artistas\n");
        printf("3. Borrar un artista\n");
        printf("4. Borrar un usuario\n");
        printf("5. Reactivar un artista\n");
        printf("6. Reactivar un usuario\n");
        printf("0. Salir \n");
        printf("\nIngrese una opcion: ");


        scanf("%d",&opcion);

        switch(opcion) {
        case 0:
            return;
        case 1:
            limpiarConsola();
            do {
            mostrarUsuarios();
            printf("\nIngrese '0' para salir: ");
            scanf("%d", &seguir);
            } while (seguir != 0);
            break;
        case 2:
            limpiarConsola();
            do {
            mostrarArtistas();
            printf("\nIngrese '0' para salir: ");
            scanf("%d", &seguir);
            } while (seguir != 0);
            break;
        case 3:
            limpiarConsola();
            printf("Ingrese la ID del artista a borrar: ");
            scanf("%d", &idArtista);
            bajaArtista(idArtista);
            esperarLimpieza(2);
            break;
        case 4:
            limpiarConsola();
            printf("Ingrese la ID del usuario a borrar: ");
            scanf("%d", &idUsuario);
            bajaUsuario(idUsuario);
            esperarLimpieza(2);
            break;
        case 5:
            limpiarConsola();
            printf("Ingrese la ID del artista a reactivar: ");
            scanf("%d", &idArtista);
            reactivarArtista(idArtista);
            esperarLimpieza(2);
        case 6:
            limpiarConsola();
            printf("Ingrese la ID del usuario a reactivar: ");
            scanf("%d", &idUsuario);
            reactivarUsuario(idUsuario);
            esperarLimpieza(2);
        }
    }
}
