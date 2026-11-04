int generarIdAlbum(char nombreArchivo[])
{
    FILE *buffer=fopen(nombreArchivo,"rb");
    if(buffer==NULL)
    {
        return -1;
    }
    fseek(buffer,-(long)sizeof(Album),SEEK_END);
    Album album;
    fread(&album,sizeof(Album),1,buffer);
    static int contador=0;
    if(contador==0)
    {
        contador+=album.idAlbum;
    }
    fclose(buffer);
    return contador++;
}
