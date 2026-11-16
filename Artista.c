#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"
#include "registro.h"
#include "artista.h"
#include "usuario.h"

void menu_artista(int id_Artista_ing)
{
    int opcion;

    while(opcion!=0)
    {
        printf("Ingrese una opcion: \n");
        printf("1.Canciones. \n");
        printf("2.Albumes. \n");
        printf("0.Para Finalizar. \n");
        scanf("%d",&opcion);
        switch(opcion)
        {
        case 0:
            {
                return;
            }
            case 1:
                {

                    break;
                }

            case 2:
                {
                    char option;
                    printf("Ingrese una opcion: \n");
                    printf("a. Agregar Cancion. \n");
                    printf("b. Modificar Cancion (Solo tus canciones). \n");
                    scanf(" %c", &option);
                    switch(option)
                    {
                        case 'a':
                            {
                                Cancion c;
                                int exito=agregar_cancion(&c, id_Artista_ing);
                                if(exito==-1)
                                {
                                    printf("No se pudo ingresar la cancion.");
                                    return;
                                }
                                break;
                            }
                        case 'b':
                            {
                                modificar_cancion(id_Artista_ing);
                                break;
                            }
                        default:
                            {
                                printf("Opcion invalida.\n");
                                break;
                            }
                    }//Finaliza Switch Interno

                    //Primer Switch
                    break;
                }

            default:
                {
                    printf("Opcion Incorrecta\n");

                }
        }
    }
}
//-------FUNCIONES MODIFICAR CANCION--------//
void modificar_cancion(int id_logeado)
{
    mostrar_canciones_logeado(id_logeado);
    int id_ing;
    int encontrado=0;
    do{
     printf("Que cancion desea modificar? Ingrese el ID:  ");
    scanf("%i", &id_ing);
    encontrado=buscar_cancion_ID(id_ing,id_logeado);
    if(encontrado==-1)
    {
     printf("Error en la busqueda de la cancion.\n");
     return;
    }
    if(encontrado==0)
    {
     printf("Cancion no encontrada.\n");
    }
    }while(encontrado==0);

    int modificado=modificar_cancion_archivo(id_ing);

    if(modificado==-1)
    {
        printf("Error en la modificacion.\n");
        return;
    }
    if(modificado==0)
    {
        printf("Ningun cambio realizado.\n");
        return;
    }


}
int modificar_cancion_archivo(int id_ing)
{
    FILE*archivo=fopen("Canciones.dat","rb+");

    if(!archivo)return -1;

    Cancion aux;

    while(fread(&aux,sizeof(Cancion),1,archivo)==1)
    {
        if(aux.idCancion==id_ing)
        {
            int opcion=-1;
            int modificado=0;
            while(opcion!=0)
            {
                printf("Que desea cambiar?: \n");
                printf("1. Titulo. \n");
                printf("2. Duracion.\n");
                scanf("%d", &opcion);
                switch(opcion)
                {
                case 1:
                    {
                    printf("Ingrese el titulo nuevo: ");
                    scanf(" %99[^\n]", aux.titulo);
                    modificado=1;
                    break;
                    }
                case 2:
                    {
                    printf("Ingrese la duracion: \n");
                    scanf("%i", &aux.duracionSegundos);
                    modificado=1;
                    break;
                    }

                case 0:
                    {
                    break;
                    }
                default:
                    {
                     printf("Opcion invalida.\n");
                        break;
                    }
                }
                if(modificado==1)
                {
                    if(fseek(archivo,-(long)sizeof(Cancion),SEEK_CUR)==0)
                    {
                        int escrito=fwrite(&aux,sizeof(Cancion),1,archivo);
                        if(escrito!=1)
                        {
                            printf("ERROR en la escritura al archivo.\n");
                            fclose(archivo);
                            return -1;
                        }

                        printf("Cancion modificada con exito!");
                        fclose(archivo);
                        return 1;
                    }
                }

            }
        }
    }
    fclose(archivo);
    return 0;
}
int buscar_cancion_ID(int id_ing, int id_logeado)
{
    int encontrado=0;
    FILE*archivo=fopen("Canciones.dat","rb+");

    if(!archivo)
        return -1;
    Cancion aux;
    while(fread(&aux,sizeof(Cancion),1,archivo)==1)
    {
     if(aux.idCancion==id_ing)
     {
         encontrado=1;
         printf("Cancion encontrada! \n");
         if(aux.idArtista!=id_logeado)
         {
             printf("Usted no tiene permisos para editar esta cancion.");
             fclose(archivo);
             return -1;
         }
         return encontrado;
     }
    }

    fclose(archivo);
    return encontrado;
}
void mostrar_canciones_logeado(int id_logeado)
{
    FILE*archivo=fopen("Canciones.dat","rb");

    if(!archivo)
        return;

    Cancion aux;
    while(fread(&aux,sizeof(Cancion),1,archivo)==1)
    {
        if(aux.idArtista==id_logeado)
        mostrarCancion(aux);
    }
    fclose(archivo);
}
//-------FUNCIONES CREAR CANCION------------//
int agregar_cancion(Cancion* c, int id_Artista_ing)
{
    int repetido=0;
    if(generar_ID_cancion()==-1)
    {
        printf("ERROR en el ID.\n");
        return -1;
    }
    int exito=generar_ID_cancion();
    //-------------------//
    char titulo_ing [100];
     printf("Ingrese el titulo: ");
    scanf(" %99[^\n]", titulo_ing);
    //--------------------------//
    char opcion;
    int id_ingresado;
    int encontrado;
    do{
    printf("Ingrese el ID del album: ");
    scanf("%i", &id_ingresado);
    encontrado=buscar_id(id_ingresado);
    if(encontrado==-2)
    {
        printf("Error en la busqueda.\n");
        return -1;
    }
    if(encontrado==-1)
    {
        printf("Album no encontrado.\n");
    }

    printf("Desea ingresar la cancion a este album? s/n. \n");
    scanf(" %c", &opcion);

    if(opcion=='s'||opcion=='S')
    {
        exito=1;
    }

    }while((opcion!='s' && opcion!='S')||(encontrado==-1));

    int duracionSegundos;
    do{
    printf("Ingrese su duracion en segundos(Mayor a 40): ");
    scanf("%i", &duracionSegundos);
    }while (duracionSegundos<40);

    if(exito>-1)
    {
        c->idCancion= generar_ID_cancion();
        strcpy(c->titulo,titulo_ing);
        c->idAlbum=id_ingresado;
        c->idArtista=id_Artista_ing;
        c->duracionSegundos=duracionSegundos;
        c->calificacionPromedio=0.00;
    }

    printf("La ID de su cancion es: %i \n", c->idCancion);

    return 1;
}
int buscar_id(int id_ingresado)
{
    int encontrado=-1;

    FILE* archivo=fopen("Albumes.dat","rb");

    if(!archivo)
        return -2;

    Album aux;

    while(fread(&aux,sizeof(Album),1,archivo)==1)
    {
        if(aux.idAlbum==id_ingresado)
        {
            mostrarAlbum(aux);
            encontrado=1;
        }
    }

    fclose(archivo);
    return encontrado;
}
int generar_ID_cancion()
{
     int repetido=0;
    int nuevoID=0;

    int verificacion=0;
    FILE*archivo=fopen("Canciones.dat","rb");
    if(!archivo)
    {
        verificacion=crear_archivo("Canciones.dat");
        if(verificacion==-1)
        {
         printf("Error en la creacion del archivo.\n");
         return -1;
        }

    }
    if(verificacion==1)
    {
        printf("Archivo creado con exito!\n");
        archivo=fopen("Canciones.dat","rb");
        if(!archivo){
            printf("ERROR en la lectura del archivo.\n");
            return -1;
        }
    }

    fseek(archivo,0L,SEEK_END);
    long bytes=ftell(archivo);
    long cantidad=bytes/sizeof(Cancion);

    if(cantidad>0)
    {
    fseek(archivo,-(long)sizeof(Cancion),SEEK_END);
    Cancion aux;
    int leido= fread(&aux,sizeof(Cancion),1,archivo);
        if(leido!=1)
        {
            printf("ERROR, en la ultima lectura del archivo.\n");
            fclose(archivo);
            return -1;
        }
        nuevoID=(aux.idCancion);
            do{
               nuevoID= nuevoID + 1;
               repetido=corroborar_ID_cancion(nuevoID);

               if(repetido==-1)
               {
                 fclose(archivo);
                return-1;
               }


            }while(repetido==1);

    }
    if(cantidad<0)
        printf("ERROR, en la busqueda de archivos");

    fclose(archivo);

    return nuevoID;
}
int corroborar_ID_cancion(int ID_ingresado)
{
    int repetido=0;
    FILE*archivo=fopen("Canciones.dat","rb");
    if(!archivo)
    {
        printf("Error de apertura de archivo en el ID");
        return -1;
    }
    Cancion aux;
    while(fread(&aux,sizeof(Cancion),1,archivo)==1)
    {
        if(aux.idCancion==ID_ingresado)
            repetido=1;
    }

    fclose(archivo);
    return repetido;
}
