#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED
typedef struct stArtista {
    int IdArtista; // ID unico
    char nombre[50]; // Nombre publico del Artista
    char contrasenia[20]; // Para el login
    char generoPrincipal[30];
    char nickname[30];
} Artista;

typedef struct stUsuario {
    int idUsuario; // ID de cliente unico
    char email[50];
    char contrasenia[20]; // Para el login
    char nickname[30];
} Usuario;
//--------------PROTOTIPADOS----------------//
int corroborar_contrasenia(char c[], int dim);
int corroborrar_string_repetido(Usuario a[], int validos, char string_ingresado[]);
int generar_ID();
void crear_usuario(Usuario usuarios[], int *validos);
Usuario* crear_arreglo_din(int capacidad);
void menu_registro();
void dumpearUsuariosABin(char *filename, Usuario *user);
void bufferError(FILE *file);


#endif // REGISTRO_H_INCLUDED
