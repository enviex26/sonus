#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "registro.h"
#include "extras.h"


void limpiarConsola() {
    printf("\033[H\033[2J"); // caracteres especiales para limpiar consola
    fflush(stdout); // limpieza buffer
}

void esperarLimpieza(int segundos) {
    time_t start = time(NULL); // consula el reloj del sistema
    while(difftime(time(NULL), start) < segundos); // compara los segundos que pasaron con los que hay que esperar
}

void mostrarUsuarios() {
    printf("-----------------\n");
    printf("Todos los usuarios\n");
    printf("-----------------\n");

    FILE *buffer = fopen("usuarios.bin", "rb");
    if (!buffer) return;
    Usuario usr;

    while (fread(&usr, sizeof(Usuario), 1, buffer) == 1) {
        mostrarUsuario(usr);
    }


    fclose(buffer);
}

void mostrarUsuario(Usuario usuario) {
    printf("-------------------\n");
    printf("ID: %d\n", usuario.idUsuario);
    printf("Nickname: %s\n", usuario.nickname);
    printf("Email: %s\n", usuario.email);
    printf("Activo: %d\n", usuario.activo);
}


void mostrarArtista(Artista b)
{
    printf("-------------------\n");
    printf("Nickname: %s \n",b.nickname);
    printf("ID: %i \n",b.IdArtista);
    printf("Nombre: %s \n",b.nombre);
    printf("Genero: %s \n",b.generoPrincipal);
    printf("Activo: %d\n", b.activo);

}
void mostrarArtistas()
{
    printf("-----------------\n");
    printf("Todos los artistas\n");
    printf("-----------------\n");
    FILE*archivo=fopen("Artistas.dat","rb");
    if(!archivo)
        return;
    Artista aux;

    while(fread(&aux,sizeof(Artista),1,archivo)==1)
    {
        mostrarArtista(aux);
    }
    fclose(archivo);
}

int bajaUsuario(int idUsuario) {
    FILE *buffer = fopen("usuarios.bin", "r+b");
    if (!buffer) return -1;
    Usuario usr;

    while (fread(&usr, sizeof(Usuario), 1, buffer) == 1) {
        if (usr.idUsuario == idUsuario && usr.activo != 0) {
            usr.activo = 0;
            fseek(buffer, -(long)sizeof(Usuario), SEEK_CUR);
            fwrite(&usr, sizeof(Usuario), 1, buffer);
            fclose(buffer);
            printf("Se ha borrado el usuario correctamente.\n");
            return 1;
        }
    }

    fclose(buffer);
    printf("No se ha podido borrar el usuario.\n");
    return 0;
}

int bajaArtista(int idArtista) {
    FILE *buffer = fopen("Artistas.dat", "r+b");
    if (!buffer) return -1;
    Artista art;

    while (fread(&art, sizeof(Artista), 1, buffer) == 1) {
        if (art.IdArtista == idArtista && art.activo != 0) {
            art.activo = 0;
            fseek(buffer, -(long)sizeof(Artista), SEEK_CUR);
            fwrite(&art, sizeof(Artista), 1, buffer);
            fclose(buffer);
            printf("Se ha borrado el usuario correctamente.\n");
            return 1;
        }
    }
    fclose(buffer);
    printf("No se ha podido borrar el usuario.\n");
    return 0;

}

int reactivarUsuario(int idUsuario) {
    FILE *buffer = fopen("usuarios.bin", "r+b");
    if (!buffer) return -1;
    Usuario usr;

    while (fread(&usr, sizeof(Usuario), 1, buffer) == 1) {
        if (usr.idUsuario == idUsuario) {
            usr.activo = 1;
            fseek(buffer, -(long)sizeof(Usuario), SEEK_CUR);
            fwrite(&usr, sizeof(Usuario), 1, buffer);
            fclose(buffer);
            printf("Se ha reactivado el usuario correctamente.\n");
            return 1;
        }
    }
    fclose(buffer);
    printf("No se ha podido reactivar el usuario.\n");
    return 0;

}

int reactivarArtista(int idArtista) {
    FILE *buffer = fopen("Artistas.dat", "r+b");
    if (!buffer) return -1;
    Artista art;

    while (fread(&art, sizeof(Artista), 1, buffer) == 1) {
        if (art.IdArtista == idArtista) {
            art.activo = 1;
            fseek(buffer, -(long)sizeof(Artista), SEEK_CUR);
            fwrite(&art, sizeof(Artista), 1, buffer);
            fclose(buffer);
            printf("Se ha reactivado el artista correctamente.\n");
            return 1;
        }
    }
    fclose(buffer);
    printf("No se ha podido reactivar el artista.\n");
    return 0;

}

