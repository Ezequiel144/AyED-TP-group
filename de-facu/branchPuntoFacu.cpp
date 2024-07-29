#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

const int NUMERO_EMPRESAS = 3; // Cantidad de empresas adheridas (Podemos cambiarlo despues).

FILE* archivo; // Declaro variable archivo.

struct empresa{ // Info de cada empresa, que se lleva a un array, para despues ser sorteado.
  string nombre;
  int codigo;
  int recaudado;
  int ventas;
}arrEmpresa[NUMERO_EMPRESAS];

void bubbleSort();

void rellenoDatos();

void mostrarStruct();

void cargarArchivo();

int main()
{
  rellenoDatos(); // Ingreso empresas .

  bubbleSort(); // Ordeno según código.
 
  cargarArchivo(); // Creo archivo con las empresas ordenadas.
 
  return 0;
}

void bubbleSort() // Función para ordenar las empresas por su código indentificador. 
{
  for (int i = 0; i < NUMERO_EMPRESAS - 1; i++)
    {
      for (int j = 0; j < NUMERO_EMPRESAS - 1 - i; j++)
      {
        if (arrEmpresa[j].codigo > arrEmpresa[j+1].codigo)
        {
          empresa temp = arrEmpresa[j];
          arrEmpresa[j] = arrEmpresa[j+1];
          arrEmpresa[j+1] = temp;
        }
      }
    }
}

void rellenoDatos() // Permite ingresar los datos de cada empresa, en formato struct.
{
  for (int i = 0; i < NUMERO_EMPRESAS; i++)
    {
      cout << endl << "Ingrese nombre de la empresa adherida: ";
      getline(cin, arrEmpresa[i].nombre); 

      cout << "Ingrese codigo de la empresa: ";
      cin >> arrEmpresa[i].codigo;
      cin.get();

      cout << "Ingrese dinero recaudado de la empresa: ";
      cin >> arrEmpresa[i].recaudado;
      cin.get();

      cout << "Ingrese ventas realizadas por la empresa: ";
      cin >> arrEmpresa[i].ventas;
      cin.get();
      
     // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Tenia problemas con el buffer, esto lo limpia antes del próximo "cin".
    }
}

void mostrarStruct() // Hace "cout" del array de structs.
{
  for (int i = 0; i < NUMERO_EMPRESAS; i++)
  {
    fwrite(&arrEmpresa[i].codigo, sizeof(int), 1, archivo);
    fwrite(&arrEmpresa[i].nombre, sizeof(string), 1, archivo);
    fwrite(&arrEmpresa[i].recaudado, sizeof(int), 1, archivo);
    fwrite(&arrEmpresa[i].ventas, sizeof(int), 1, archivo);

    fwrite()
  }
}

void cargarArchivo() // Crea archivo, y utiliza la función mostrarStruct() para imprimir la info de las empresas ordenadas.
{
  archivo = fopen("Importe.dat", "wb"); // Abre archivo binario.

  if (!archivo) // Si no lo puede abrir, devuelve error.
  {
    cout << "Error al intentar abrir el archivo"; // error archivo no encontrado...
    //exit(-1);
    return -1;
  }  
  mostrarStruct(); // Copia el struct ordenado al archivo binario.
}
