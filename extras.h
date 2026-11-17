#ifndef EXTRAS_H_INCLUDED
#define EXTRAS_H_INCLUDED
#include "registro.h"

void limpiarConsola();
void esperarLimpieza(int segundos);
void mostrarUsuario(Usuario usuario);
void mostrarUsuarios();
void mostrarArtista(Artista b);
void mostrarArtistas();
int bajaUsuario(int idUsuario);
int bajaArtista(int idArtista);
int reactivarArtista(int idArtista);
int reactivarUsuario(int idUsuario);

#endif // EXTRAS_H_INCLUDED
