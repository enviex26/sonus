#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

typedef struct stCalificacion {
 char idRegistroCal[10];
 char nicknameUsuario[30];
 char idCancion[10];
 int puntuacion;
} Calificacion;


void menu_usuario(); // o sin parámetro si usás global/extern
FILE *Abrirarchivo(const char nombreArchivo[], char modo[]);
Artista buscarArtistaPorNombre(char artistaBuscar[], const char nombreArchivo[]);
void mostrarAlbum(Album alb);
void mostrarCancion(Cancion can);
void buscarCancionPorAlbum(FILE *archivoCancion, Cancion *encontrada, char idAlbum[]);
void verCatalogoporArtista(const char nombreArchivoArtistas[], const char nombreArchivoAlbum[], const char nombreArchivoCancion[]);
Album buscarAlbumTitulo(char albumBuscar[], char nombreArchivo[]);
void verCancionesPorAlbum(const char nombreArchivoAlbum[], const char nombreArchivoCancion[]);
void buscarCancionPorTitulo(Cancion *encontrada, char nombreArchivoCancion[]);
void infoDetalladaCancion(char nombreArchivoCancion[], char nombreArchivoCalificacion[]);
int registrarCalificacion(Cancion encontrada, char nombreArchivoCalificacion[], const char nicknameUsuario[]);
void calcularCantidadYSuma(Cancion encontrada, char nombreArchivo[], float *suma, int *cantidad);
float calcularPromedio(float suma, int cantidad);
void actualizarPromedioCancion(FILE *archivoCanciones, Cancion encontrada, float suma, int cantidad);
void calificarCancion(char nombreArchivoCancion[], char nombreArchivoCalificacion[],const char nickNameUsuario[]);
void mostrarCalificacion(Calificacion cal);
void verMisCalificaciones(const char nombreArchivoCalificacion[], const char nickNameUsuario[]);

#endif
