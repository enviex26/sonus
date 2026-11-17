void menu_reportes()
{
    int opcion;
    limpiarConsola();
    printf("-----------------\n");
    printf("Menu Principal (Reportes)\n");
    printf("-----------------\n");
    printf("Ingrese Opcion: \n");
    printf("0.Salir\n");
    printf("1.Ver Catalogo por Artista \n");
    printf("2.Ver Canciones por Album: \n");
    printf("3.Ver Informacion Detallada de Canci—n\n");
    printf("4.Calificar Canci—n\n");
    printf("5.Ver Mis Calificaciones\n");


    scanf("%d",&opcion);
    while(opcion!=0)
    {
        switch(opcion)
        {
            case 1:
                {
                    canciones=Cancion *arregloTop(char nombreArchivo[],int *validos);
                    break;
                }
            case 2:
                {
                    Album *ordenadosPorAnio(char nombreArchivo[],int *validos);
                    break;
                }
            case 3:
                {
                    int artistaConMasCalificaciones(char archivoArtistas[],char archivoCanciones[],
                                                    char archivoCalificaciones[],Artista *topCalificado);

                    break;
                }
            case 4:
                {
                    int cantidadCalificacionesArtista(char archivoCanciones[],char archivoCalficaciones[]
                                                      ,char nombreArtista[]);

                    break;
                }
            case 5:
                {
                    int cantidadCalificacionesCancion(char archivoCalificaciones[],char idCancionBuscar[]);
                    break;
                }
            default:
                {
                    printf("Opcion Incorrecta\n");

                }
        }
    }
}
Album *ordenadosPorAnio(char nombreArchivo[],int *validos)//el arreglo tiene todos los albumes ingresados ordenados por anio
{
    FILE *buffer=fopen(nombreArchivo,"rb");
    if(buffer==NULL)
    {
        return NULL;
    }
    int dimension=10;
    Album *arreglo=malloc(10*sizeof(Album));
    Album album,aux;
    while(fread(&album,sizeof(Album),1,buffer))
    {
        for(int i=0;i<(*validos);i++)
        {
            if(album.anioLanzamiento>arreglo[i].anioLanzamiento)
            {
                aux=arreglo[i];
                arreglo[i]=album;
                album=aux;
            }
        }
        if((*validos)==dimension)
        {
            Album *temporal=realloc(arreglo,(dimension+10)*sizeof(Album));
            if(temporal==NULL)
            {
                return NULL;
            }
            arreglo=temporal;
            dimension+=10;
        }
        arreglo[*validos]=album;
        (*validos)++;
    }
    free(canciones);
    canciones=NULL;
    fclose(buffer);
    return arreglo;
}

Cancion *arregloTop(char nombreArchivo[],int *validos)//arreglo con un maximos de las 10 mejores canciones, digo maximo por si se ingresan menos de 10
{
    FILE *buffer=fopen(nombreArchivo,"rb");
    if(buffer==NULL)
    {
        return NULL;
    }
    Cancion *arreglo=malloc(10*sizeof(Cancion));
    Cancion cancion,aux;
    while(fread(&cancion,sizeof(Cancion),1,buffer))
    {
        for(int i=0;i<(*validos);i++)
        {
            if(arreglo[i].calificacionPromedio<cancion.calificacionPromedio)
            {
                aux=arreglo[i];
                arreglo[i]=cancion;
                cancion=aux;
            }
        }
        if((*validos)<10)
        {
            arreglo[*validos]=cancion;
            (*validos)++;
        }
    }
    if((*validos)<10)
    {
        Cancion *temporal=realloc(arreglo,(*validos)*sizeof(Cancion));
        if(temporal==NULL)
        {
            return NULL;
        }
        arreglo=temporal;
    }
    fclose(buffer);
    return arreglo;
}

int cantidadCalificacionesCancion(char archivoCalificaciones[],char idCancionBuscar[])//cantidad calificaciones de una cancion
{
    FILE *buffer=fopen(archivoCalificaciones,"rb");
    if(buffer==NULL)
    {
        return 0;
    }
    int cantidad=0;
    Calificacion calificacion;
    while(fread(&calificacion,sizeof(Calificacion),1,buffer))
    {
        if(strcmp(calificacion.idCancion,idCancionBuscar)==0)
        {
            cantidad++;
        }
    }
    fclose(buffer);
    return cantidad;
}

int cantidadCalificacionesArtista(char archivoCanciones[],char archivoCalficaciones[],char nombreArtista[])//regresa la cantidad de calificaciones de un artista
{
    FILE *buffer=fopen(archivoCanciones,"rb");
    if(buffer==NULL)
    {
        return 0;
    }
    int suma=0;
    Cancion cancion;
    while(fread(&cancion,sizeof(Cancion),1,buffer))
    {
        if(strcmp(cancion.nombreArtista,nombreArtista)==0)
        {
            suma=suma+cantidadCalificacionesCancion(archivoCalficaciones,cancion.idCancion);
        }
    }
    fclose(buffer);
    return suma;
}

int artistaConMasCalificaciones(char archivoArtistas[],char archivoCanciones[],char archivoCalificaciones[],Artista *topCalificado)//puntero indica al artista ccon mas calificaciones
{
    FILE *buffer=fopen(archivoArtistas,"rb");
    if(buffer==NULL)
    {
        return 0;
    }
    Artista artista,mejor;
    fread(&mejor,sizeof(Artista),1,buffer);
    int calificaciones,masCalificaciones=cantidadCalificacionesArtista(archivoCanciones,archivoCalificaciones,mejor.nombre);
    while(fread(&artista,sizeof(Artista),1,buffer))
    {
        calificaciones=cantidadCalificacionesArtista(archivoCanciones,archivoCalificaciones,artista.nombre);
        if(calificaciones>masCalificaciones)
        {
            mejor=artista;
            masCalificaciones=calificaciones;
        }
    }
    *topCalificado=mejor;
    fclose(buffer);
    return 1;
}

int usurioConMasCalificaciones(char archivoUsuarios[],char archivoCalificaciones[],Usuario *masCalificaciones)//el puntero es donde va el usuario con mas calificaciones
{
    FILE *buffer=fopen(archivoUsuarios,"rb");
    if(buffer==NULL)
    {
        return 0;
    }
    Usuario ususrio,mejor;
    int cantidad,cantidadMejor;
    fread(&mejor,sizeof(Usuario),1,buffer);
    cantidadMejor=cantidadCalificacionesUsurio(archivoCalificaciones,mejor.nickname);
    while(fread(&ususrio,sizeof(Usuario),1,buffer))
    {
        cantidad=cantidadCalificacionesUsurio(archivoCalificaciones,ususrio.nickname);
        if(cantidad>cantidadMejor)
        {
            cantidadMejor=cantidad;
            mejor=ususrio;
        }
    }
    *masCalificaciones=mejor;
    fclose(buffer);
    return 1;//necesitaba el int 1 para saber si se pudo ingresar al archivo
}

int cantidadCalificacionesUsurio(char archivoCalificaciones[],char nicknameBuscar[])//regresa la cantidad de calificaciones que hizo un usuario
{
    FILE *buffer=fopen(archivoCalificaciones,"rb");
    if(buffer==NULL)
    {
        return 0;
    }
    Calificacion calificacion;
    int contador=0;
    while(fread(&calificacion,sizeof(Calificacion),1,buffer))
    {
        if(strcmp(calificacion.nicknameUsuario,nicknameBuscar)==0)
        {
            contador++;
        }
    }
    fclose(buffer);
    return contador;
}
