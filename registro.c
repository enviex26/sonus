#include "registro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void menu_registro()
{
    int opcion;

    printf("Que tipo de usuario desea registrar\n");
    printf("0. Salir\n");
    printf("1. Usuario\n");
    printf("2. Artista\n");

    while(opcion){
        switch (opcion)
        {
        case 0:
            return 0;

        case 1:
            crear_usuario();
            break;

        }

    }

}
Usuario crear_usuario(){
    //---------------------------------//

    //--------------------------//
    printf("Ingrese el nombre: ");
    fgets(nombre,50,stdin);
    while(getchar()!='\n');
    //----------------------------//
    do{
    printf("Ingrese su contrasenia: ");
    scanf("%s", contrasenia);
    }while(corroborar_contrasenia(contrasenia)==1)
    //----------------------------------//
    do{
    printf("Ingrese el nickname: ");
    scanf("%s", nickname);
    }while(corroborrar_string_repetido(usuarios,validos,nickname)!=0);
    //----------------------------------//
    do{
    printf("Ingrese su mail: ");
    scanf("%s", email);
    }while(corroborrar_string_repetido(usuarios,validos,email)!=0);
    //----------------------------------//


}
int corroborrar_string_repetido(Usuario a[], int validos, char string_ingresado[])
{
    repetido=0;

    for(int i=0;i<validos;i++)
        {
        if(strcmp(usuarios[i].,Id_ingresado)==0)
            repetido=1;
        }

        if(repetido==1)
        printf("El campo ingresado ya existe");


    return repetido;
}
int corroborar_contrasenia(char c[], int dim)
{
 int flag=0;

 do{
    for(int i=0;i<dim;i++)
     {
         if(isupper(c[i]) != 0) {
            flag = 1;
         }
     }
    if(flag!=1)
    printf("Su contrasenia debe tener minimo una mayuscula.\n");
    }
    while(flag!=0);

 return flag;
}
