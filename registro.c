#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "registro.h"

void menu_registro()
{
    int option=-1;
    printf("Que tipo de usuario desea registrar\n");
    printf("0. Salir\n");
    printf("1. Usuario\n");
    printf("2. Artista\n");
    scanf("%d", &option);

        switch (option)
        {
        case 1:
            {
                int capacidad=1;
                int validos = 0;
                Usuario *usuarios=NULL;
                usuarios=crear_arreglo_din(capacidad);

                if(!usuarios)
                    return;

            if(validos==capacidad)
            {
            usuarios=redimensionar_arr(usuarios,&capacidad);
                if(validos==capacidad)
                {
                    printf("Error al redimensionar el arreglo!");
                    return;
                }
            }

            if(validos<capacidad)
            {
                if(crear_usuario(usuarios,&validos)==-1)
                {
                    printf("ERROR en la creacion de usuario.");
                    free(usuarios);
                    usuarios=NULL;
                    return;
                }
            }

            int exito= dumpearUsuariosABin("usuarios.bin",&usuarios[validos-1]);
            if(exito==-1){
                printf("Error a pasar el usuario al archivo.");
                free(usuarios);
                usuarios=NULL;
                return;
            }
            free(usuarios);
            usuarios=NULL;
            break;
        }
        case 2:
            {
            Artista b;
            int exito=cargar_artista(&b);
            if(exito==-1)
                return;

            exito=0;
            exito=pasar_artista_a_archivo(b);
            if(exito!=1)
            {
                printf("Error al pasar al archivo.\n");
                return;
            }
            else
            {
                printf("Artista registrado, bienvenido a Sonus.\n");
            }
            mostrar_artistas();
            break;
            }

        }
}
//-------------------REGISTRO ARTISTA-------------------------//
void mostrar_artista(Artista b)
{
    printf("-------------------\n");
    printf("Nombre: %s \n",b.nombre);
    printf("Genero: %s \n",b.generoPrincipal);
    printf("Nickname: %s \n",b.nickname);
    printf("ID: %i \n",b.IdArtista);
    printf("--------------------\n");
}
void mostrar_artistas()
{
    FILE*archivo=fopen("artistas.bin","rb");
    if(!archivo)
        return;
    Artista aux;
    while(fread(&aux,sizeof(Artista),1,archivo)==1)
    {
        mostrar_artista(aux);
    }
    fclose(archivo);
}
int pasar_artista_a_archivo(Artista b)
{
    FILE* archivo=fopen("artistas.bin","ab");
     if(archivo != NULL)
    {
        fwrite(&b, sizeof(Artista), 1, archivo);
        fclose(archivo);
        return 1;
    }
    return -1;
}
int cargar_artista(Artista *b)
{
    int repetido=0;
    if(generar_ID_artista()==-1)
    {
        printf("ERROR en el ID.\n");
        return -1;
    }
    b->IdArtista= generar_ID_artista();
    //--------------------------//
    do{
     printf("Ingrese su nombre: ");
    scanf(" %49[^\n]", b->nombre);
    repetido=corroborar_string_Art(b->nombre);
    if(repetido==-1)
    {
        printf("Error en la busqueda de repetidos.");
        return -1;
    }
    }while(repetido==1);
    //--------------------------//
    do{
    printf("Ingrese su contrasenia: ");
    scanf(" %19s", b->contrasenia);
    }while(corroborar_contrasenia(b->contrasenia, (int)strlen(b->contrasenia))==0);
    //--------------------------//
    printf("Genero identificado: ");
    scanf(" %29[^\n]", b->generoPrincipal);
    //--------------------------//
    do{
    printf("Ingrese su nickname: ");
    scanf(" %29[^\n]", b->nickname);
    repetido=corroborar_string_Art(b->nickname);
    if(repetido==-1)
    {
        printf("Error en la busqueda de repetidos.");
        return -1;
    }
    }while (repetido==1);


    printf("Artista creado!\n");
    printf("Su ID es: %i \n", b->IdArtista);

    return 1;
}
int corroborar_string_Art(char string_ingresado[])
{
    int repetido=0;
    FILE*archivo=fopen("artistas.bin","rb");
    if(!archivo)
        return -1;
    Artista aux;

    while(fread(&aux,sizeof(Artista),1,archivo)==1)
    {
        if(strcmp(aux.nickname,string_ingresado)==0)
        {
            repetido=1;
            break;
        }

        if(strcmp(aux.nombre,string_ingresado)==0)
        {
            repetido=1;
            break;
        }
    }

    if(repetido==1)
        printf("Campo ingresado ya existente!\n");

    fclose(archivo);
    return repetido;
}
int generar_ID_artista()
{
     int repetido=0;
    int nuevoID=0;

    int verificacion=0;
    FILE*archivo=fopen("artistas.bin","rb");
    if(!archivo)
    {
        verificacion=crear_archivo("artistas.bin");
        if(verificacion==-1)
        {
         printf("Error en la creacion del archivo.\n");
         return -1;
        }

    }
    if(verificacion==1)
    {
        printf("Archivo creado con exito!\n");
        archivo=fopen("artistas.bin","rb");
        if(!archivo){
            printf("ERROR en la lectura del archivo.");
            return -1;
        }
    }

    fseek(archivo,0L,SEEK_END);
    long bytes=ftell(archivo);
    long cantidad=bytes/sizeof(Artista);

    if(cantidad>0)
    {
    fseek(archivo,-(long)sizeof(Artista),SEEK_END);
    Artista aux;
    int leido= fread(&aux,sizeof(Artista),1,archivo);
        if(leido!=1)
        {
            printf("ERROR, en la ultima lectura del archivo");
            fclose(archivo);
            return -1;
        }
        nuevoID=(aux.IdArtista);
            do{
               nuevoID= nuevoID + 1;
               repetido=corroborar_ID_artista(nuevoID);

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

int corroborar_ID_artista(int ID_ingresado)
{
    int repetido=0;
    FILE*archivo=fopen("artistas.bin","rb");
    if(!archivo)
    {
        printf("Error de apertura de archivo en el ID");
        return -1;
    }
    Artista aux;
    while(fread(&aux,sizeof(Artista),1,archivo)==1)
    {
        if(aux.IdArtista==ID_ingresado)
            repetido=1;
    }

    fclose(archivo);
    return repetido;
}
Artista* crear_arr_din(int capacidad)
{
    return malloc(sizeof(Artista)*capacidad);
}

//-------------------REGISTRO USUARIO-------------------------//
Usuario* redimensionar_arr(Usuario usuarios[],int* capacidad)
{
    Usuario* temp;
    int nueva_capacidad=(*capacidad)+1;
    temp=realloc(usuarios,sizeof(Usuario)*nueva_capacidad);
    if(temp)
    {
     usuarios=temp;
     (*capacidad)++;
     return temp;
    }
    else
    {
        printf("Error al redimensionar el archivo");
        return usuarios;
    }
}
Usuario* crear_arreglo_din(int capacidad)
{
    Usuario *usuarios=NULL;
    usuarios=malloc(sizeof(Usuario)*capacidad);
    if(!usuarios)
    {
        printf("ERROR de espacio en memoria\n");
        return NULL;
    }
    return usuarios;
}

int crear_usuario(Usuario usuarios[], int *validos)
{
    Usuario a;
    int repetido=0;
    a.idUsuario = generar_ID();
    //--------------------------//
    do{
    printf("Ingrese el nickname: ");
    scanf("%29s", a.nickname);
    repetido=corroborar_string_repetido(a.nickname);
    if(repetido==-1)
        return -1;
    }while(repetido==1);
    while(getchar()!='\n');
    //----------------------------//
    do{
    printf("Ingrese su contrasenia: ");
    scanf("%19s", a.contrasenia);
    }while(corroborar_contrasenia(a.contrasenia, (int)strlen(a.contrasenia))==0);
    //----------------------------------//
    do{
    printf("Ingrese su mail: ");
    scanf("%49s", a.email);
    repetido=corroborar_string_repetido(a.email);
    if(repetido==-1)
        return -1;
    }while(repetido==1);
    //----------------------------------//
     if(a.idUsuario==-1)
        return -1;

    printf("Cargado correctamente!\n");
    printf("Su ID es: %d\n", a.idUsuario);

    usuarios[*validos]=a;
    (*validos)++;
    return 1;
}

int generar_ID()
{
    int repetido=0;
    int nuevoID=0;
    int error=0;
    int verificacion=0;
    FILE*archivo=fopen("usuarios.bin","rb");
    if(!archivo)
    {
        verificacion=crear_archivo("usuarios.bin");
        if(verificacion==1)
            printf("Archivo creado con exito!");
        if(verificacion==-1)
            error=verificacion;
    }

    if(error==-1)
    {
        printf("ERROR con la creacion del archivo.");
        return -1;
    }

    if(verificacion==1)
    {
        archivo=fopen("usuarios.bin","rb");
        if(!archivo){
            printf("ERROR en la lectura del archivo.");
            return -1;
        }
    }

    fseek(archivo,0L,SEEK_END);
    long bytes=ftell(archivo);
    long cantidad=bytes/sizeof(Usuario);

    if(cantidad>0)
    {
    fseek(archivo,-(long)sizeof(Usuario),SEEK_END);
    Usuario aux;
    int leido= fread(&aux,sizeof(Usuario),1,archivo);
        if(leido!=1)
        {
            printf("ERROR, en la ultima lectura del archivo");
            fclose(archivo);
            return -1;
        }
        nuevoID=(aux.idUsuario);
            do{
               nuevoID++;
               repetido=corroborar_ID(nuevoID);

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
int corroborar_ID(int ID_ingresado)
{
    int repetido=0;
    FILE*archivo=fopen("usuarios.bin","rb");
    if(!archivo)
    {
        printf("Error de apertura de archivo en el ID");
        return -1;
    }
    Usuario aux;
    while(fread(&aux,sizeof(Usuario),1,archivo)==1)
    {
        if(aux.idUsuario==ID_ingresado)
            repetido=1;
    }

    fclose(archivo);
    return repetido;
}

int crear_archivo(char *nombre_archivo)
{

 FILE*archivo=fopen(nombre_archivo,"ab");
 if(!archivo)
    return -1;

fclose(archivo);
 return 1;
}

int corroborar_string_repetido(char string_ingresado[])
{
    int repetido=0;
    FILE*archivo=fopen("usuarios.bin","rb");
    if(!archivo)
        return -1;
    Usuario aux;
    while(fread(&aux,sizeof(Usuario),1,archivo)==1)
    {
        if(strcmp(aux.email, string_ingresado)==0)
        {
            repetido=1;
            break;
        }

        if(strcmp(aux.nickname,string_ingresado)==0)
        {
            repetido=1;
            break;
        }
    }
    if(repetido==1)
        printf("Campo ingresado ya existente!");
    fclose(archivo);
    return repetido;
}

int corroborar_contrasenia(char c[], int dim)
{
 int flag=0;

    for(int i=0;i<dim;i++)
     {
         if(isupper(c[i]) != 0) {
            flag = 1;
         }
     }

    if(flag!=1)
    printf("Su contrasenia debe tener minimo una mayuscula.\n");

 return flag;
}

int dumpearUsuariosABin(char *filename, Usuario *user)
{
    FILE *buffer = fopen(filename, "ab");
    bufferError(buffer);

    if(!buffer)
        return -1;

    if(fwrite(user, sizeof(Usuario), 1, buffer)!=1)
    {
      fclose(buffer);
      return -1;
    }

    fclose(buffer);
    return 1;
}

int bufferError(FILE *file) {
    if(!file) return -1;
}
