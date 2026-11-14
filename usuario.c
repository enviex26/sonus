#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"
#include "registro.h"
#include "artista.h"

void menu_usuario()
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
                    //llamar funcion
                    break;
                }
            case 2:
                {
                    //llamar funcion
                    break;
                }
            case 3:
                {
                    //llamar funcion
                    break;
                }
            case 4:
                {
                    //llamar funcion
                    break;
                }
            case 5:
                {
                    //llamar funcion
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
FILE *Abrirarchivo(char nombreArchivo[],char modo[])
{
    FILE *archivo=fopen(nombreArchivo,modo);
    return archivo;
}
Artista buscarArtistaPorNombre(char artistaBuscar[],const char nombreArchivo[])
{
    Artista noEncontrado;
    noEncontrado.IdArtista=-1;

    FILE *archivo=Abrirarchivo(nombreArchivo,"rb");
    if(archivo==NULL)
    {
        printf("Error al abrir archivo\n");
        return noEncontrado;
    }

    Artista leerArtista;
    while(fread(&leerArtista,sizeof(Artista),1,archivo)==1)
    {
        if(strcmp(artistaBuscar,leerArtista.nickname)==0)
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
void buscarCancionPorTitulo(Cancion *cancionEncontrada,const char nombreArchivo[],char idAlbum[])
{
    FILE *archivo=Abrirarchivo(nombreArchivo,"rb");
    if(archivo==NULL)
    {
        printf("Error al abrir archivo\n");
        return;
    }

    Cancion leerCancion;
    while(fread(&leerCancion,sizeof(Cancion),1,archivo)==1)
    {
        if(strcmp(leerCancion.idAlbum, idAlbum) == 0)
        {
            *cancionEncontrada=leerCancion;
        }
    }
    fclose(archivo);
}
void verCatalogoporArtista(const char nombreArchivoArtistas[],const char nombreArchivoAlbum[],const char nombreArchivoCancion[])
{
    char artistaBuscar[30];
    printf("Ingrese artista: ");
    fgets(artistaBuscar,30,stdin);
    artistaBuscar[strcspn(artistaBuscar, "\n")] = '\0';

    Artista encontrado=buscarArtistaPorNombre(artistaBuscar,nombreArchivoArtistas);

    if(encontrado.IdArtista==-1)
    {
        printf("Artista No Encontrado");
        return;
    }

    FILE *archivoAlbum=Abrirarchivo(nombreArchivoAlbum,"rb");
    if(archivoAlbum==NULL)
    {
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
            buscarCancionPorTitulo(&buscada,nombreArchivoCancion,leerAlbum.idAlbum);
            if (buscada.duracionSegundos!=-1)
            {
                mostrarCancion(buscada);
            }
            else printf("Cancion no Encontrada\n");
        }
    }
    fclose(archivoAlbum);
}
Album buscarAlbumTitulo(char albumBuscar[],char nombreArchivo[])
{

    Album noEncontrado;
    noEncontrado.cantidadCanciones=-1;
    FILE *archivo=Abrirarchivo(nombreArchivo,"rb");
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
void buscarCancionPorAlbum(char nombreArchivo[])
{
    FILE *archivo=Abrirarchivo(nombreArchivo,"rb");
}
void verCancionesPorAlbum(const char nombreArchivoAlbum[],const char nombreArchivoCancion[])
{
    char albumBuscar[100];
    printf("Ingrese Album: ");
    fgets(albumBuscar,100,stdin);
    albumBuscar[strcspn(albumBuscar, "\n")] = '\0';



    FILE *archivoCancion=Abrirarchivo(nombreArchivoCancion,"rb");
    if(archivoCancion==NULL)
    {
        printf("Error al Abrir el Archivo\n");
        return;
    }

    Cancion leerCancion;
    int encontradas = 0;



    fclose(archivoCancion);
}

