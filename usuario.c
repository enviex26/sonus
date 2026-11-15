#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"
#include "registro.h"
#include "artista.h"
#include "usuario.h"

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
FILE *Abrirarchivo(char nombreArchivo[],char modo[])//no creo que haga falta esta funcion
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
        printf("Artista No Encontrado");
        return;
    }

    FILE *archivoAlbum=Abrirarchivo(nombreArchivoAlbum,"rb");
    if(archivoAlbum==NULL)
    {
        printf("Error al abrir archivo\n");
        return;
    }

    FILE *archivoCancion=Abrirarchivo(nombreArchivoCancion,"rb");
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
void verCancionesPorAlbum(const char nombreArchivoAlbum[],const char nombreArchivoCancion[])//void no necesita un return
{
    char albumBuscar[100];
    printf("Ingrese Album: ");
    fgets(albumBuscar,100,stdin);
    albumBuscar[strcspn(albumBuscar, "\n")] = '\0';

    FILE *archivoCancion=Abrirarchivo(nombreArchivoCancion,"rb");
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
    char idCancionBuscar[10];
    printf("Ingrese Cancion\n");
    fgets(idCancionBuscar,10,stdin);
    idCancionBuscar[strcspn(idCancionBuscar,"\n")]='\0';

    FILE *archivo=Abrirarchivo(nombreArchivoCancion,"rb");
    if(archivo==NULL)
    {
        printf("Error al Abrir Archivo\n");
        return;
    }

    Cancion leerCancion;
    encontrada->duracionSegundos=-1;

    while (fread(&leerCancion, sizeof(Cancion), 1, archivo) == 1)
    {
        if (strcmp(leerCancion.idCancion, idCancionBuscar) == 0)
        {
            *encontrada = leerCancion;
            return;
        }
    }
    fclose(archivo);
}
void infoDetalladaCancion(Cancion *encontrada,char nombreArchivoCancion[],char nombreArchivoCalificacion[])
{
    buscarCancionPorTitulo(encontrada,nombreArchivoCancion);
    mostrarCancion(*encontrada);

}
int registrarCalificacion(Cancion encontrada,char nombreArchivoCalificacion[])
{
    int nuevaPuntuacion = 0;
    printf("Ingrese Nueva Calificacion(1/5): ");
    scanf("%d",&nuevaPuntuacion);
    while(nuevaPuntuacion<1 || nuevaPuntuacion>5)
    {
        printf("Ingrese una Calificacion Correcta(1/5) \n");
        scanf("%d",&nuevaPuntuacion);
    }

    FILE *archivo=Abrirarchivo(nombreArchivoCalificacion,"a+b");
    if(archivo==NULL)
    {
        printf("Error al Abrir Archivo\n");
        return 0;
    }

    Calificacion leer;

    int coincide=0;
    while(fread(&leer,sizeof(Calificacion),1,archivo)==1)
    {
        if(strcmp(leer.idCancion, encontrada.idCancion) == 0)
        {
            leer.puntuacion=nuevaPuntuacion;
            fseek(archivo,-(long)sizeof(Calificacion),SEEK_CUR);
            fwrite(&leer,sizeof(Calificacion),1,archivo);
            return 1;
        }
    }
    Calificacion nuevaCalificacion;
    //agregar datos
    nuevaCalificacion.puntuacion=nuevaPuntuacion;
    fwrite(&leer,sizeof(Calificacion),1,archivo);
    return 1;

}
void CalificarCancion(char nombreArchivoCancion[],char nombreArchivoCalificacion[])
{
    Cancion encontrada;
    buscarCancionPorTitulo(&encontrada,nombreArchivoCancion);
    if(encontrada.duracionSegundos==-1)
    {
        printf("La cancion no fue Encontrada\n");
//        fclose(archivo); esto sobra, el archivo nunca se abrió
        return; //por que existe este return? <- para que no pase a la condicion de abajo supongo.
    }
    if(registrarCalificacion(encontrada,nombreArchivoCalificacion)==1)
    {
        //promedio
    }


}
