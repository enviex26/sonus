#ifndef REPORTES_H_INCLUDED
#define REPORTES_H_INCLUDED
#include "artista.h"
void menu_reportes();
int cantidadCalificacionesUsurio(char archivoCalificaciones[],char nicknameBuscar[]);
int usurioConMasCalificaciones(char archivoUsuarios[],char archivoCalificaciones[],Usuario *masCalificaciones);
int artistaConMasCalificaciones(char archivoArtistas[],char archivoCanciones[],char archivoCalificaciones[],Artista *topCalificado);
int cantidadCalificacionesArtista(char archivoCanciones[],char archivoCalficaciones[],int IdArtista);
int cantidadCalificacionesCancion(char archivoCalificaciones[],int idCancionBuscar);
Cancion *arregloTop(char nombreArchivo[],int *validos);
Album *ordenadosPorAnio(char nombreArchivo[],int *validos);
#endif // REPORTES_H_INCLUDED
