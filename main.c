#include <stdio.h>
#include <stdlib.h>
#include "registro.h"
#include "login.h"
#include "extras.h"
#include "menus.h"

int main(void){
    char sesionNickname[30] = "";
    int option = 1;

    while(option) {
        if (sesionNickname[0] == '\0') {
            option = menuInicial(sesionNickname);
        } else {
            option = menuSesionIniciada(sesionNickname);
        }
    }
    return 0;
}
