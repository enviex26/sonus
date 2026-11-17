#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED
#include "registro.h"

int menuLogin();
// -- FUNCIONES USUARIO --
int verificarUsuarioExiste(char filename[], char nickname[]);
int verificarContraseniaUsuario(char filename[], char contrasenia[], char nickname[]);
void inicioSesionUsuario(char* nickName);

// -- FUNCIONES ARTISTA --
int buscar_id_artista(char nickname[]);
int verificarArtistaExiste(char filename[], char nickname[]);
int verificarContraseniaArtista(char filename[], char contrasenia[], char nickname[]);
void inicioSesionArtista(int* id_log);


#endif // LOGIN_H_INCLUDED
