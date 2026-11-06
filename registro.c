#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "registro.h"

void menu_registro()
{
    int option=-1;
    int capacidad=1;
    int validos = 0;
    Usuario *usuarios=NULL;
    usuarios=crear_arreglo_din(capacidad);

    if(!usuarios)
        return -1;

   while(option != 0){
    printf("Que tipo de usuario desea registrar\n");
    printf("0. Salir\n");
    printf("1. Usuario\n");
    printf("2. Artista\n");
    scanf("%d", &option);

        switch (option)
        {
        case 1:
            if(validos==capacidad)
            {
            usuarios=redimensionar_arr(usuarios,&capacidad);
            }

            if(validos<capacidad)
            {
                crear_usuario(usuarios,&validos);
            }
            dumpearUsuariosABin("usuarios.bin",&usuarios[validos-1]);


            break;

        }
    }

    free(usuarios);
    usuarios=NULL;
}
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
void crear_usuario(Usuario usuarios[], int *validos)
{
    Usuario a;
    //--------------------------//
    do{
    printf("Ingrese el nickname: ");
    scanf("%29s", a.nickname);
    }while(corroborrar_string_repetido(usuarios,*validos,a.nickname)!=0);
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
    }while(corroborrar_string_repetido(usuarios,*validos,a.email)!=0);
    //----------------------------------//
    a.idUsuario = generar_ID();
    printf("Cargado correctamente!\n");
    printf("Su ID es: %d\n", a.idUsuario);

    usuarios[*validos]=a;
    (*validos)++;
}
int generar_ID()
{
  static int ID = 0000;
  return ++ID;
}

int corroborrar_string_repetido(Usuario a[], int validos, char string_ingresado[])
{
    int repetido=0;

    for(int i=0;i<validos;i++)
        {
        if(strcmp(a[i].email, string_ingresado)==0)
            repetido=1;
        }

        if(repetido==1)
        printf("El campo ingresado ya existe\n");

        for(int i=0;i<validos;i++)
        {
        if(strcmp(a[i].nickname,string_ingresado)==0)
            repetido=1;
        }

        if(repetido==1)
        printf("El campo ingresado ya existe\n");


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

void dumpearUsuariosABin(char *filename, Usuario *user) {
    FILE *buffer = fopen(filename, "ab");
    bufferError(buffer);

    if(!buffer)
        return;

    fwrite(user, sizeof(Usuario), 1, buffer);

    fclose(buffer);
}

void bufferError(FILE *file) {
    if(!file) return;
}
