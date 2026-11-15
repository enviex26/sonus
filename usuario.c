#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"
#include "registro.h"
#include "artista.h"
#include "usuario.h"

void menu_usuario(char nickNameUsuario[])
{
    int opcion;
    printf("Ingrese Opcion: \n");
    printf("1.Ver Catalogo por Artista \n");
    printf("2.Ver Canciones por Album: \n");
    printf("3.Ver Informacion Detallada de Canción\n");
    printf("4.Calificar Canción\n");
    printf("5.Ver Mis Calificaciones\n");
    printf("0.Para Finalizar\n");
    scanf("%d",&opcion);
    while(opcion!=0)
    {
        switch(opcion)
        {
            case 1:
                {
                    verCatalogoporArtista("Artistas.dat", "Album.dat", "Canciones.dat");
                    break;
                }
            case 2:
                {
                    verCancionesPorAlbum("Album.dat", "Canciones.dat");
                    break;
                }
            case 3:
                {
                    infoDetalladaCancion("Canciones.dat", "Calificaciones.dat");
                    break;
                }
            case 4:
                {
                    calificarCancion("Canciones.dat", "Calificaciones.dat", nickNameUsuario);
                    break;
                }
            case 5:
                {
                    verMisCalificaciones("Calificaciones.dat", nickNameUsuario);
                    break;
                }
            default:
                {
                    printf("Opcion Incorrecta\n");

                }
            printf("Ingrese Opcion: \n");
            printf("1.Ver Catalogo por Artista \n");
            printf("2.Ver Canciones por Album: \n");
            printf("3.Ver Informacion Detallada de Canción\n");
            printf("4.Calificar Canción\n");
            printf("5.Ver Mis Calificaciones\n");
            printf("0.Para Finalizar\n");
            scanf("%d",&opcion);
        }
    }
}
Artista buscarArtistaPorNombre(char artistaBuscar[],const char nombreArchivo[])
{
    Artista noEncontrado;
    noEncontrado.IdArtista=-1;

    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo==NULL)
    {
        printf("Error al abrir archivo\n");
        return noEncontrado;
    }

    Artista leerArtista;
    while(fread(&leerArtista,sizeof(Artista),1,archivo)==1)
    {
        if(strcmp(artistaBuscar,leerArtista.nombre)==0)
           {
               fclose(archivo);
               return leerArtista;
           }
    }
    fclose(archivo);
    return noEncontrado;
}
void mostrarAlbum(Album alb)
{
    printf("ID Album: %s\n", alb.idAlbum);
    printf("Artista: %s\n", alb.artista.nombre);
    printf("Titulo: %s\n", alb.titulo);
    printf("Anio de Lanzamiento: %d\n", alb.anioLanzamiento);
    printf("Cantidad de Canciones: %d\n", alb.cantidadCanciones);
    printf("\n");
}
void mostrarCancion(Cancion can)
{
    printf("ID Cancion: %s\n", can.idCancion);
    printf("Titulo: %s\n", can.titulo);
    printf("Album: %s\n", can.idAlbum);
    printf("Artista: %s\n", can.idArtista);
    printf("Duracion: %d segundos\n", can.duracionSegundos);
    printf("Calificacion Promedio: %.2f / 5.0\n", can.calificacionPromedio);
    printf("\n");
}
void buscarCancionPorAlbum(FILE *archivoCancion,Cancion *encontrada,char idAlbum[])
{
    Cancion leerCancion;
    encontrada->duracionSegundos = -1;

    while (fread(&leerCancion, sizeof(Cancion), 1, archivoCancion) == 1)
    {
        if (strcmp(leerCancion.idAlbum, idAlbum) == 0)
        {
            *encontrada = leerCancion;
            return;
        }
    }
}
void verCatalogoporArtista(const char nombreArchivoArtistas[],const char nombreArchivoAlbum[],const char nombreArchivoCancion[])
{
    char artistaBuscar[50];
    printf("Ingrese artista: ");
    fgets(artistaBuscar,50,stdin);
    artistaBuscar[strcspn(artistaBuscar, "\n")] = '\0';

    Artista encontrado=buscarArtistaPorNombre(artistaBuscar,nombreArchivoArtistas);

    if(encontrado.IdArtista==-1)
    {
        printf("Artista No Encontrado\n");
        return;
    }

    FILE *archivoAlbum=fopen(nombreArchivoAlbum,"rb");
    if(archivoAlbum==NULL)
    {
        printf("Error al abrir archivo\n");
        return;
    }

    FILE *archivoCancion=fopen(nombreArchivoCancion,"rb");
    if(archivoCancion==NULL)
    {
        fclose(archivoAlbum);
        printf("Error al abrir archivo\n");
        return;
    }

    Album leerAlbum;
    while(fread(&leerAlbum,sizeof(Album),1,archivoAlbum)==1)
    {
        if(leerAlbum.artista.IdArtista==encontrado.IdArtista)
        {
            mostrarAlbum(leerAlbum);
            Cancion buscada;
            rewind(archivoCancion);
            buscarCancionPorAlbum(archivoCancion, &buscada, leerAlbum.idAlbum);
            if (buscada.duracionSegundos!=-1)
            {
                mostrarCancion(buscada);
            }
            else printf("Cancion no Encontrada\n");
        }
    }
    fclose(archivoCancion);
    fclose(archivoAlbum);
}
Album buscarAlbumTitulo(char albumBuscar[],char nombreArchivo[])
{
    Album noEncontrado;
    noEncontrado.cantidadCanciones=-1;
    FILE *archivo=fopen(nombreArchivo,"rb");
    if(archivo==NULL)
    {
        printf("Error al abrir archivo\n");
        return noEncontrado;
    }
    Album leerAlbum;
    while(fread(&leerAlbum,sizeof(Album),1,archivo)==1)
    {
        if(strcmp(albumBuscar,leerAlbum.titulo)==0)
        {
            fclose(archivo);
            return leerAlbum;
        }
    }
    fclose(archivo);
    return noEncontrado;
}
void verCancionesPorAlbum(const char nombreArchivoAlbum[],const char nombreArchivoCancion[])//void no necesita un return
{
    char albumBuscar[100];
    printf("Ingrese Album: ");
    fgets(albumBuscar,100,stdin);
    albumBuscar[strcspn(albumBuscar, "\n")] = '\0';

    FILE *archivoCancion=fopen(nombreArchivoCancion,"rb");
    if(archivoCancion==NULL)
    {
        printf("Error al abrir archivo\n");
        return;
    }
    Album albumEncontrado=buscarAlbumTitulo(albumBuscar,nombreArchivoAlbum);
    if(albumEncontrado.cantidadCanciones==-1)
    {
        printf("Album no Encontrado\n");
        fclose(archivoCancion);
        return;
    }

    Cancion leerCancion;
    int encontradas = 0;

    printf("Canciones:\n");
    while (fread(&leerCancion, sizeof(Cancion), 1, archivoCancion) == 1)
    {
        if (strcmp(leerCancion.idAlbum, albumEncontrado.idAlbum) == 0)
        {
            mostrarCancion(leerCancion);
            encontradas = 1;
        }
    }

    if (!encontradas)
    {
        printf("No hay canciones para este album.\n");
    }
    fclose(archivoCancion);
}
void buscarCancionPorTitulo(Cancion *encontrada,char nombreArchivoCancion[])
{
    char tituloBuscar[100];
    printf("Ingrese Cancion\n");
    fgets(tituloBuscar,100,stdin);
    tituloBuscar[strcspn(tituloBuscar,"\n")]='\0';

    FILE *archivo=fopen(nombreArchivoCancion,"rb");
    if(archivo==NULL)
    {
        printf("Error al Abrir Archivo\n");
        encontrada->duracionSegundos = -1;
        return;
    }

    Cancion leerCancion;
    encontrada->duracionSegundos=-1;

    while (fread(&leerCancion, sizeof(Cancion), 1, archivo) == 1)
    {
        if (strcmp(leerCancion.titulo, tituloBuscar) == 0)
        {
            *encontrada = leerCancion;
            fclose(archivo);
            return;
        }
    }
    fclose(archivo);
}
void infoDetalladaCancion(char nombreArchivoCancion[],char nombreArchivoCalificacion[])
{
    Cancion encontrada;
    buscarCancionPorTitulo(&encontrada, nombreArchivoCancion);
    if (encontrada.duracionSegundos == -1)
    {
        printf("Cancion no encontrada.\n");
        return;
    }
    mostrarCancion(encontrada);
}
int registrarCalificacion(Cancion encontrada,char nombreArchivoCalificacion[],const char nicknameUsuario[])
{
    int nuevaPuntuacion;
    printf("Ingrese Nueva Calificacion(1/5): ");
    scanf("%d",&nuevaPuntuacion);
    int totalRegistros = 1;

    while(nuevaPuntuacion>5 || nuevaPuntuacion<1)
    {
        printf("Ingrese una Calificacion Correcta(1/5) ");
        scanf("%d",&nuevaPuntuacion);
    }

    FILE *archivo=fopen(nombreArchivoCalificacion,"r+b");
    if(archivo==NULL)
    {
        archivo =fopen(nombreArchivoCalificacion, "w+b");
        if (archivo == NULL)
        {
            printf("Error al Abrir Archivo\n");
            return 0;
        }
    }

    Calificacion leer;

    while(fread(&leer,sizeof(Calificacion),1,archivo)==1)
    {
        totalRegistros++;
        if(strcmp(leer.idCancion, encontrada.idCancion) == 0 && strcmp(leer.nicknameUsuario,nicknameUsuario)==0)
        {
            leer.puntuacion=nuevaPuntuacion;
            fseek(archivo,-(long)sizeof(Calificacion),SEEK_CUR);
            fwrite(&leer,sizeof(Calificacion),1,archivo);
            fclose(archivo);
            return 1;
        }
    }
    fseek(archivo,0,SEEK_END);
    Calificacion nuevaCalificacion;
    nuevaCalificacion.idRegistroCal=totalRegistros;
    strcpy(nuevaCalificacion.nicknameUsuario, nicknameUsuario);
    strcpy(nuevaCalificacion.idCancion, encontrada.idCancion);
    nuevaCalificacion.puntuacion=nuevaPuntuacion;


    fwrite(&nuevaCalificacion,sizeof(Calificacion),1,archivo);
    fclose(archivo);
    return 1;
}
void calcularCantidadYSuma(Cancion encontrada,char nombreArchivo[],float *suma, int *cantidad)
{
    FILE *archivo = fopen(nombreArchivo, "rb");
    if(archivo==NULL)
    {
        printf("No fue posible abrir el Archivo\n");
        return;
    }

    Calificacion leer;
    *suma=0;
    *cantidad=0;

    while(fread(&leer,sizeof(Calificacion),1,archivo)==1)
    {

        if(strcmp(leer.idCancion, encontrada.idCancion) == 0)
        {
            (*suma)+=leer.puntuacion;
            (*cantidad)++;
        }
    }
    fclose(archivo);
}

float calcularPromedio(float suma, int cantidad)
{
    if (cantidad <= 0)
    {
        return 0;
    }
    return suma/(float)cantidad;
}
void actualizarPromedioCancion(FILE *archivoCanciones,Cancion encontrada,float suma, int cantidad)
{

    Cancion leerCancion;
    rewind(archivoCanciones);
    while (fread(&leerCancion, sizeof(Cancion), 1, archivoCanciones) == 1)
    {
        if (strcmp(leerCancion.idCancion, encontrada.idCancion) == 0)
        {
            leerCancion.calificacionPromedio=calcularPromedio(suma,cantidad);
            fseek(archivoCanciones,-(long)sizeof(Cancion),SEEK_CUR);
            fwrite(&leerCancion,sizeof(Cancion),1,archivoCanciones);
            return;
        }
    }
}

void calificarCancion(char nombreArchivoCancion[],char nombreArchivoCalificacion[],const char nickNameUsuario[])
{
    Cancion encontrada;
    buscarCancionPorTitulo(&encontrada,nombreArchivoCancion);
    if(encontrada.duracionSegundos==-1)
    {
        printf("La cancion no fue Encontrada\n");
        return;
    }
    if(registrarCalificacion(encontrada,nombreArchivoCalificacion,nickNameUsuario)==1)
    {
        float suma;
        int cantidad;
        calcularCantidadYSuma(encontrada,nombreArchivoCalificacion,&suma,&cantidad);

        FILE *archivoCanciones=fopen(nombreArchivoCancion,"r+b");
        if(archivoCanciones==NULL)
        {
            printf("No fue Posible abrir el Archivo\n");
            return;
        }

        actualizarPromedioCancion(archivoCanciones,encontrada,suma,cantidad);
        fclose(archivoCanciones);
    }
}

void mostrarCalificacion(Calificacion cal)
{
    printf("ID Calificacion: %s\n", cal.idRegistroCal);
    printf("Usuario: %s\n", cal.nicknameUsuario);
    printf("Cancion: %s\n", cal.idCancion);
    printf("Puntuacion: %d / 5\n", cal.puntuacion);
    printf("\n");
}

void verMisCalificaciones(const char nombreArchivoCalificacion[], const char nickNameUsuario[])
{
    FILE *archivo = fopen(nombreArchivoCalificacion, "rb");
    if (archivo == NULL)
    {
        printf("No fue posible abrir el archivo de calificaciones\n");
        return;
    }

    Calificacion leer;
    int encontradas = 0;

    while (fread(&leer, sizeof(Calificacion), 1, archivo) == 1)
    {
        if (strcmp(leer.nicknameUsuario, nickNameUsuario) == 0)
        {
            mostrarCalificacion(leer);
            encontradas = 1;
        }
    }

    if (encontradas==0)
    {
        printf("Aun no tenes calificaciones registradas.\n");
    }
    fclose(archivo);
}
