#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"
#include "registro.h"
#include "artista.h"
#include "usuario.h"
#include "extras.h"
#include "menus.h"
#include "reportes.h"


Album *ordenadosPorAnio(char nombreArchivo[],int *validos)//el arreglo tiene todos los albumes ingresados ordenados por anio
{
    FILE *buffer=fopen(nombreArchivo,"rb");
    if(buffer==NULL)
    {
        return NULL;
    }
    int dimension=10;
    Album *arreglo=malloc(10*sizeof(Album));
    Album album,aux;
    while(fread(&album,sizeof(Album),1,buffer))
    {
        for(int i=0;i<(*validos);i++)
        {
            if(album.anioLanzamiento>arreglo[i].anioLanzamiento)
            {
                aux=arreglo[i];
                arreglo[i]=album;
                album=aux;
            }
        }
        if((*validos)==dimension)
        {
            Album *temporal=realloc(arreglo,(dimension+10)*sizeof(Album));
            if(temporal==NULL)
            {
                return NULL;
            }
            arreglo=temporal;
            dimension+=10;
        }
        arreglo[*validos]=album;
        (*validos)++;
    }
    fclose(buffer);
    return arreglo;
}

Cancion *arregloTop(char nombreArchivo[],int *validos)//arreglo con un maximos de las 10 mejores canciones, digo maximo por si se ingresan menos de 10
{
    FILE *buffer=fopen(nombreArchivo,"rb");
    if(buffer==NULL)
    {
        return NULL;
    }
    Cancion *arreglo=malloc(10*sizeof(Cancion));
    Cancion cancion,aux;
    while(fread(&cancion,sizeof(Cancion),1,buffer))
    {
        for(int i=0;i<(*validos);i++)
        {
            if(arreglo[i].calificacionPromedio<cancion.calificacionPromedio)
            {
                aux=arreglo[i];
                arreglo[i]=cancion;
                cancion=aux;
            }
        }
        if((*validos)<10)
        {
            arreglo[*validos]=cancion;
            (*validos)++;
        }
    }
    if((*validos)<10)
    {
        Cancion *temporal=realloc(arreglo,(*validos)*sizeof(Cancion));
        if(temporal==NULL)
        {
            return NULL;
        }
        arreglo=temporal;
    }
    fclose(buffer);
    return arreglo;
}

int cantidadCalificacionesCancion(char archivoCalificaciones[],int idCancionBuscar)//cantidad calificaciones de una cancion
{
    FILE *buffer=fopen(archivoCalificaciones,"rb");
    if(buffer==NULL)
    {
        return 0;
    }
    int cantidad=0;
    Calificacion calificacion;
    while(fread(&calificacion,sizeof(Calificacion),1,buffer))
    {
        if(calificacion.idCancion==idCancionBuscar)
        {
            cantidad++;
        }
    }
    fclose(buffer);
    return cantidad;
}

int cantidadCalificacionesArtista(char archivoCanciones[],char archivoCalficaciones[],int IdArtista)//regresa la cantidad de calificaciones de un artista
{
    FILE *buffer=fopen(archivoCanciones,"rb");
    if(buffer==NULL)
    {
        return 0;
    }
    int suma=0;
    Cancion cancion;
    while(fread(&cancion,sizeof(Cancion),1,buffer))
    {
        if(cancion.idArtista==IdArtista)
        {
            suma=suma+cantidadCalificacionesCancion(archivoCalficaciones,cancion.idCancion);
        }
    }
    fclose(buffer);
    return suma;
}


int artistaConMasCalificaciones(char archivoArtistas[],char archivoCanciones[],char archivoCalificaciones[],Artista *topCalificado)
{
    FILE *buffer = fopen(archivoArtistas, "rb");

    if(buffer == NULL || topCalificado == NULL)
    {
        if(buffer != NULL)
            fclose(buffer);

        return 0;
    }

    Artista artista, mejor;

    if(fread(&mejor, sizeof(Artista), 1, buffer) != 1)
    {
        fclose(buffer);
        return 0;
    }

    int masCalificaciones = cantidadCalificacionesArtista(
        archivoCanciones,
        archivoCalificaciones,
        mejor.IdArtista
    );

    while(fread(&artista, sizeof(Artista), 1, buffer) == 1)
    {
        int calificaciones = cantidadCalificacionesArtista(
            archivoCanciones,
            archivoCalificaciones,
            artista.IdArtista
        );

        if(calificaciones > masCalificaciones)
        {
            mejor = artista;
            masCalificaciones = calificaciones;
        }
    }

    *topCalificado = mejor;

    fclose(buffer);
    return 1;
}



int usurioConMasCalificaciones(char archivoUsuarios[],char archivoCalificaciones[],Usuario *masCalificaciones)
{
    FILE *buffer = fopen(archivoUsuarios, "rb");

    if(buffer == NULL || masCalificaciones == NULL)
    {
        if(buffer != NULL)
            fclose(buffer);

        return 0;
    }

    Usuario usuario, mejor;

    if(fread(&mejor, sizeof(Usuario), 1, buffer) != 1)
    {
        fclose(buffer);
        return 0;
    }

    int cantidadMejor = cantidadCalificacionesUsurio(
        archivoCalificaciones,
        mejor.nickname
    );

    while(fread(&usuario, sizeof(Usuario), 1, buffer) == 1)
    {
        int cantidad = cantidadCalificacionesUsurio(
            archivoCalificaciones,
            usuario.nickname
        );

        if(cantidad > cantidadMejor)
        {
            cantidadMejor = cantidad;
            mejor = usuario;
        }
    }

    *masCalificaciones = mejor;

    fclose(buffer);
    return 1;
}


int cantidadCalificacionesUsurio(char archivoCalificaciones[],char nicknameBuscar[])//regresa la cantidad de calificaciones que hizo un usuario
{
    FILE *buffer=fopen(archivoCalificaciones,"rb");
    if(buffer==NULL)
    {
        return 0;
    }
    Calificacion calificacion;
    int contador=0;
    while(fread(&calificacion,sizeof(Calificacion),1,buffer))
    {
        if(strcmp(calificacion.nicknameUsuario,nicknameBuscar)==0)
        {
            contador++;
        }
    }
    fclose(buffer);
    return contador;
}
