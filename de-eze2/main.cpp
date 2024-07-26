#include <iostream>
#include <stdio.h>
#include <string.h>


using namespace std;

struct Auxventas
{
    int dia;
    int cantvent;
};

int main()
{
}

void mayordiaventas (Venta vect[], int dimvec*3)
{
    int aux1=0, aux2=0, aux3=0, mayor=-1, largo=0;
    Auxventas vec[3];
    //int array[3] = {0,0,0}

    for(int i=0; i<dimvec*3/*15*/; i+=3) // Recorro el vector con i=0 inicialmente, despues le sumo 3 y asi sucesivamente para la suma de todas las cant de ventas de todos los dias 1.
    {
        aux1+=vect[i].cantVentas;
        //array[i] += vect[i].cantVentas;
    }

    for(int j=1; j<dimvec*3; j+=3) // Recorro el vector con j=1 inicialmente, despues le sumo 3 y asi sucesivamente para la suma de todas las cant de ventas de todos los dias 2.
    {
        aux2+=vect[j].cantVentas;
    }

    for(int k=2; k<dimvec*3; k+=3) // Recorro el vector con k=2 inicialmente, despues le sumo 3 y asi sucesivamente para la suma de todas las cant de ventas de todos los dias 3.
    {
        aux3+=vect[k].cantVentas;
    }

    for (int h = 0; h < dim/*15*/; h++)
    {
        if(vect[h].dia === 0 /*0 -> dia 1*/){
            aux1 += vect[h].cantvent
        }else if(){

        }
    }
    

   /*  for(int m=0; m<3; m++)
    {
        vec[m].dia=m+1;        // Le asigno numeros a los dias.
    } */
    vec[0].cantvent=aux1;      // Le asigno las cantidad de ventas por cada dia.
    vec[1].cantvent=aux2;
    vec[2].cantvent=aux3;

    for(int l=0; l<3; l++)     // Recorro el vector para buscar el mayor de cant de ventas.
    {
       if(vec[l].cantvent>mayor)
       {
           mayor=vec[l].cantvent;
       }
    }

    cout << "Dia/s con mas ventas:" << endl;
    for (int p=0; p<3; p++)    //Se muestra los dias con mayor ventas.
    {
        if(mayor==vec[p].cantvent)
           cout << "Dia " << vec[p].dia + 1<< "       Cantidad de ventas: " << vec[p].cantvent << endl;
    }

}



































