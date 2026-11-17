

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
