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
void menu_artista(int id_Artista_ing);
//-------MODIFICAR CANCION--------//
void modificar_cancion(int id_logeado);
int modificar_cancion_archivo(int id_ing);
int buscar_cancion_ID(int id_ing, int id_logeado);
void mostrar_canciones_logeado(int id_logeado);
//-------NUEVA CANCION------------//
int agregar_cancion(Cancion* c, int id_Artista_ing);
int buscar_id(int id_ingresado);
int generar_ID_cancion();
int corroborar_ID_cancion(int ID_ingresado);
#endif
