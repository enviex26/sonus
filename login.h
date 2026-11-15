#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED
#include "registro.h"

void inicioSesion();
int verificarUsuarioExiste(char filename[], char nickname[]);
int verificarContrasenia(char filename[], char contrasenia[], char nickname[]);
void menuInicioSesion();

#endif // LOGIN_H_INCLUDED
