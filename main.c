#include <stdio.h>
#include <stdlib.h>
#include "registro.h"
#include "login.h"


int main(void){
    menu_registro();
    Usuario *usuarios = NULL;
    int capacidad=0;
    int validos=0;
    usuarios = cargar_arregloDin(usuarios,&capacidad,&validos);

}
