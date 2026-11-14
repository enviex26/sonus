#ifndef ARTISTA_H_INCLUDED
#define ARTISTA_H_INCLUDED
typedef struct stAlbum {
 char idAlbum[10];
 Artista artista;
 char titulo[100];
 int anioLanzamiento;
 int cantidadCanciones;
} Album;

typedef struct stCancion {
 char idCancion[10];
 char titulo[100];
 char idAlbum[10];
 char idArtista[10];
 int duracionSegundos;
 float calificacionPromedio;
} Cancion;


#endif
