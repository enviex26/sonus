#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"
#include "registro.h"
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
FILE *Abrirarchivo(char nombreArchivo[])
{
    FILE *archivo=fopen(nombreArchivo,"r+b");
    return archivo;
}
Artista buscarPorNombre(FILE *archivo,char artistaBuscar[])
{
    Artista leerArtista;
    while(fread(&leerArtista,sizeof(Artista),1,archivo)==1)
    {
        if(strcmp(artistaBuscar,leerArtista.nombre)==0)
           {
               return leerArtista;
           }
    }
    Artista noEncontrado;
    noEncontrado.IdArtista=-1;
    return noEncontrado;
}
void mostrarAlbumes(Artista p)
{

}
void verCatalogoporArtista(const char nombreArchivo[])
{
    char artistaBuscar[50];
    printf("Ingrese artista: ");
    fgets(artistaBuscar,50,stdin);
    FILE *archivo=Abrirarchivo(nombreArchivo);
    if(archivo==NULL)
    {
        printf("Error al abrir archivo\n");
        return;
    }
    Artista encontrado=buscarPorNombre(archivo,artistaBuscar);
    if(encontrado.IdArtista==-1)
    {
        printf("Artista No Encontrado");
        return;
    }
    mostrarAlbumes(encontrado);
}
