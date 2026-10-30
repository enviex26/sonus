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
    printf("Ingrese el ID: ");
    scanf("%s", idArtista);
    printf("Ingrese el nombre: ");
    fgets(nombre,50,stdin);
    while(getchar()!='\n');
    do{
    printf("Ingrese su contrasenia: ");
    scanf("%s", contrasenia);
    }while(corroborar_contrasenia(contrasenia)==1)

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
 return flag;
}
