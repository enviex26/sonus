#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
int revisarPila(Pila p,int num);
void ingresarPaquetes(Pila *p)
{
    int num;
    char res='s';
    while(res=='s'||res=='S')
    {
        do
        {
            printf("ingrese codigo del producto\n");
            scanf("%d",&num);
            if(num<1000||3999<num)
                printf("codigo no valido intente de nuevo\n");
        }while(num<1000||3999<num);
        if(revisarPila(*p,num))
            apilar(p,num);
        printf("desea continuar?(S/N)\n");
        scanf(" %c",&res);
    }
}
int revisarPila(Pila p,int num)
{
    while(!pilavacia(&p))
    {
        if(desapilar(&p)==num)
            return 0;
    }
    return 1;
}
void agregarAArreglo(int arreglo[],int *cantidad,int dimension,int num);
void filtrarPaquetes(Pila *p,int fragiles[],int estadares[],int pesados[],int dimension,int *cantFra,int *cantEst,int *cantPes)
{
    int num;
    while(!pilavacia(p))
    {
        num=desapilar(p);
        if(num<2000)
        {
            agregarAArreglo(fragiles,cantFra,dimension,num);
        }
        else
            if(num<3000)
            {
                agregarAArreglo(estadares,cantEst,dimension,num);
            }
            else
                {
                    agregarAArreglo(pesados,cantPes,dimension,num);
                }
    }
}
void agregarAArreglo(int arreglo[],int *cantidad,int dimension,int num)
{
    int cambio=0,i=0,aux;
    while((*cantidad)<dimension&&cambio==0)
    {
        if(arreglo[i]==num)
            cambio=1;
        else
            if(num<arreglo[i])
            {
                aux=num;
                num=arreglo[i];
                arreglo[i]=aux;
            }
            else
                if(arreglo[i]==0)
                {
                    arreglo[i]=num;
                    (*cantidad)++;
                    cambio=1;
                }
        i++;
    }
}
int busquedaBinaria(int arreglo[],int cantidad,int buscando)
{
    int inf=0,sup=cantidad-1,medio;
    while(inf<=sup)
    {
        medio=(inf+sup)/2;
        if(arreglo[medio]==buscando)
            return medio;
        else
            if(arreglo[medio]<buscando)
                inf=medio+1;
            else
                sup=medio-1;
    }
    return -1;
}
void quitarYOrdenar(int arreglo[],int *cantidad,int posicion);
void despacharPaquete(int num,int fragiles[],int estandares[],int pesados[],int *cantFra,int *cantEst,int *cantPes)
{
    int posicion;
    char respuesta;
    if(num<2000)
        {
            posicion=busquedaBinaria(fragiles,*cantFra,num);
            if(posicion!=-1)
            {
                printf("paquete encontrado\n");
                printf("desea despacharlo?(S/N)\n");
                scanf(" %c",&respuesta);
                if(respuesta=='s'||respuesta=='S')
                    quitarYOrdenar(fragiles,cantFra,posicion);
            }
            else
                printf("paquete no encontrado\n");
        }
        else
            if(num<3000)
            {

                posicion=busquedaBinaria(estandares,*cantEst,num);
                if(posicion!=-1)
                {
                    printf("paquete encontrado\n");
                    printf("desea despacharlo?(S/N)\n");
                    scanf(" %c",&respuesta);
                    if(respuesta=='s'||respuesta=='S')
                        quitarYOrdenar(estandares,cantEst,posicion);
                }
                else
                    printf("paquete no encontrado\n");
            }
            else
                {
                    posicion=busquedaBinaria(pesados,*cantPes,num);
                    if(posicion!=-1)
                    {
                        printf("paquete encontrado\n");
                        printf("desea despacharlo?(S/N)\n");
                        scanf(" %c",&respuesta);
                        if(respuesta=='s'||respuesta=='S')
                            quitarYOrdenar(pesados,cantPes,posicion);
                    }
                    else
                        printf("paquete no encontrado\n");
                }
}
void quitarYOrdenar(int arreglo[],int *cantidad,int posicion)
{
    for(int i=posicion;i<(*cantidad-1);i++)
        arreglo[i]=arreglo[i+1];
    (*cantidad)--;
    arreglo[*cantidad]=0;
}
int buscarMayor(int arreglo[],int dimension)
{
    int i=1,mayor=arreglo[0];
    while(i<dimension&&arreglo[i]!=0)
        {
            if(mayor<arreglo[i])
            mayor=arreglo[i];
            i++;
        }
    return mayor;
}
void buscarMultiplos(int arreglo[],int multiploDeX[],int noMultiploDeX[],int X,int *cantMX,int *cantNMX,int dimension);
void clasificarPaquetes(int arreglo1[],int arreglo2[],int arreglo3[],int multiplosDeX[],int noMultiplosDeX[],int X,int dimension)
{
    int cantMX=0,cantNMX=0;
    buscarMultiplos(arreglo1,multiplosDeX,noMultiplosDeX,X,&cantMX,&cantNMX,dimension);
    buscarMultiplos(arreglo2,multiplosDeX,noMultiplosDeX,X,&cantMX,&cantNMX,dimension);
    buscarMultiplos(arreglo3,multiplosDeX,noMultiplosDeX,X,&cantMX,&cantNMX,dimension);
}
void buscarMultiplos(int arreglo[],int multiploDeX[],int noMultiploDeX[],int X,int *cantMX,int *cantNMX,int dimension)
{
    int i=0;
    while(i<dimension&&arreglo[i]!=0)
    {
        if(arreglo[i]%X==0)
        {
            multiploDeX[*cantMX]=arreglo[i];
            (*cantMX)++;
        }
        else
        {
            noMultiploDeX[*cantNMX]=arreglo[i];
            (*cantNMX)++;
        }
        i++;
    }
}
void mostrarArreglo(int arreglo[],int cantidad);
int main()
{
    Pila p;
    int fragiles[10]={0},estandares[10]={0},pesados[10]={0},dimension=10;
    int cantFra=0,cantEst=0,cantPes=0;
    inicpila(&p);
    ingresarPaquetes(&p);
    mostrar(&p);
    filtrarPaquetes(&p,fragiles,estandares,pesados,dimension,&cantFra,&cantEst,&cantPes);
    printf("FRAGILES: ");
    mostrarArreglo(fragiles,cantFra);
    printf("ESTANDARES: ");
    mostrarArreglo(estandares,cantEst);
    printf("PESADOS: ");
    mostrarArreglo(pesados,cantPes);
    printf("ingrese un numero a buscar\n");
    int buscar;
    scanf("%d",&buscar);
    despacharPaquete(buscar,fragiles,estandares,pesados,&cantFra,&cantEst,&cantPes);
    printf("FRAGILES: ");
    mostrarArreglo(fragiles,cantFra);
    printf("ESTANDARES: ");
    mostrarArreglo(estandares,cantEst);
    printf("PESADOS: ");
    mostrarArreglo(pesados,cantPes);
    int arreglo[10]={1,2,3,4,57,6,7,8,9,10};
    printf("el mayor del arreglo es %d\n",buscarMayor(arreglo,10));
    int multiplosDeX[10]={0},noMultiplosDeX[10]={0},X;
    printf("ingrese un numero para buscar sus multiplos\n");
    scanf("%d",&X);
    clasificarPaquetes(fragiles,estandares,pesados,multiplosDeX,noMultiplosDeX,X,10);
    mostrarArreglo(multiplosDeX,10);
    mostrarArreglo(noMultiplosDeX,10);
    return 0;
}
void mostrarArreglo(int arreglo[],int cantidad)
{
    for(int i=0;i<cantidad;i++)
        printf("%d ",arreglo[i]);
    printf("\n");
}
