#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED
typedef struct stArtista {
    int IdArtista;
    char nombre[50]; // Nombre publico del Artista
    char contrasenia[20]; // Para el login
    char generoPrincipal[30];
} Artista;

typedef struct stUsuario {
    int idUsuario; // ID de cliente œnico
    char email[50];
    char contrasenia[20]; // Para el login
    char nickname[30];
} Usuario;
//--------------PROTOTIPADOS----------------//
int corroborar_contrasenia(char c[], int dim);
int corroborrar_string_repetido(Usuario a[], int validos, char string_ingresado[]);
int generar_ID();
Usuario crear_usuario();
void menu_registro();


#endif // REGISTRO_H_INCLUDED
