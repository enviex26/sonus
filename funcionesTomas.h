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
