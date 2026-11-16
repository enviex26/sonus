#ifndef ARTISTA_H_INCLUDED
#define ARTISTA_H_INCLUDED
typedef struct stAlbum {
 int idAlbum;
 Artista artista;
 char titulo[100];
 int anioLanzamiento;
 int cantidadCanciones;
} Album;

typedef struct stCancion {
 int idCancion;
 char titulo[100];
 int idAlbum;
 int idArtista;
 int duracionSegundos;
 float calificacionPromedio;
} Cancion;

//----------PROTOTIPADOS---------//
int agregar_cancion(Cancion* c, int id_Artista_ing);
int buscar_id(int id_ingresado);
int generar_ID_cancion();
int corroborar_ID_cancion(int ID_ingresado);
#endif
