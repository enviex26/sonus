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
//--------------ARTISTAS----------------//
int corroborar_ID_artista(int ID_ingresado);
int generar_ID_artista();
int corroborar_string_Art(char string_ingresado[]);
int cargar_artista(Artista *b);
int pasar_artista_a_archivo(Artista b);
void mostrar_artistas();

//--------------USUARIOS----------------//
int corroborar_contrasenia(char c[], int dim);
int corroborar_string_repetido(char string_ingresado[]);
int generar_ID();
int crear_usuario(Usuario usuarios[], int *validos);
void menu_registro();
int dumpearUsuariosABin(char *filename, Usuario *user);
int bufferError(FILE *file);
Usuario* redimensionar_arr(Usuario usuarios[],int* capacidad);
Usuario* crear_arreglo_din(int capacidad);
int crear_archivo(char *nombre_archivo);
int corroborar_ID(int ID_ingresado);



#endif // REGISTRO_H_INCLUDED
