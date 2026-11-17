#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED
#include "registro.h"

int menuLogin(char sesionNickname[]);
// -- FUNCIONES USUARIO --
int verificarUsuarioExiste(char filename[], char nickname[]);
int verificarContraseniaUsuario(char filename[], char contrasenia[], char nickname[]);
int inicioSesionUsuario(char* nickName);

// -- FUNCIONES ARTISTA --
int buscar_id_artista(char nickname[]);
int verificarArtistaExiste(char filename[], char nickname[]);
int verificarContraseniaArtista(char filename[], char contrasenia[], char nickname[]);
int inicioSesionArtista(int *id_log, char nicknameSesion[]);


#endif // LOGIN_H_INCLUDED
