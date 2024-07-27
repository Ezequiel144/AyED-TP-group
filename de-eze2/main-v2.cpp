#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
}

void mayordiaventas(Venta vect[], int dim)
{
   int aux1 = 0, aux2 = 0, aux3 = 0, mayor = -1;
   int vecaux[] = {aux1, aux2, aux3};

   for (int i = 0; i < dim; i += 3) // Recorro el vector con i=0 inicialmente, despues le sumo 3 y asi sucesivamente para la suma de todas las cant de ventas de todos los dias 1.
   {
      if (vect[i].dia == 0)
         aux1 += vect[i].cantVentas;
      else if (vect[i].dia == 1)
         aux2 += vect[i].cantVentas;
      else if (vect[i].dia == 2)
         aux3 += vect[i].cantVentas;
   }

   for (int j = 0; j < 3; j++) // Recorro el vector para buscar el mayor de cant de ventas.
   {
      if (vecaux[j] > mayor)
         mayor = vecaux[j];
   }

   cout << "Dia/s con mas ventas:" << endl;
   for (int k = 0; k < 3; k++) // Se muestra los dias con mayor ventas.
   {
      if (mayor == vecuax[k])
         cout << "Dia " << k + 1 << "       Cantidad de ventas: " << vecaux[k] << endl;
   }
}
