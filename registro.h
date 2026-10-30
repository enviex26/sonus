#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED
typedef struct stArtista {
    char idArtista[10];
    char nombre[50]; // Nombre pœblico del Artista
    char contrasenia[20]; // Para el login
    char generoPrincipal[30];
} Artista;

typedef struct stUsuario {
    char idUsuario[10]; // ID de cliente œnico
    char email[50];
    char contrasenia[20]; // Para el login
    char nickname[30];
} Usuario;


#endif // REGISTRO_H_INCLUDED
