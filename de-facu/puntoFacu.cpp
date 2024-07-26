#include <cstdio> //no la vimo en clase
#include <iostream>
#include <fstream> //no la vimo en clase
#include <string> //no la vimo en clase -> <string.h>
#include <limits> //no la vimo en clase

using namespace std;

const int NUMERO_EMPRESAS = 3; // Cantidad de empresas adheridas (Podemos cambiarlo despues).

fstream archivo; // Declaro variable archivo.

struct empresa{ // Info de cada empresa, que se lleva a un array, para despues ser sorteado.
  string nombre;
  int codigo;
  int recaudado; //importe
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
 
  cout << endl;
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
      cout << "Ingrese nombre de la empresa adherida: ";
      getline(cin, arrEmpresa[i].nombre);

      cout << "Ingrese codigo de la empresa: ";
      cin >> arrEmpresa[i].codigo;

      cout << "Ingrese dinero recaudado de la empresa: ";
      cin >> arrEmpresa[i].recaudado;

      cout << "Ingrese ventas realizadas por la empresa: ";
      cin >> arrEmpresa[i].ventas;

      /* cin.ignore(numeric_limits<streamsize>::max(), '\n'); */ // Tenia problemas con el buffer, esto lo limpia antes del próximo "cin".
    }
}

void mostrarStruct() // Hace "cout" del array de structs.
{
  for (int i = 0; i < NUMERO_EMPRESAS; i++)
  {
    archivo << "Codigo de empresa: " << arrEmpresa[i].codigo << endl;
    archivo << "Nombre de empresa: " << arrEmpresa[i].nombre << endl;
    archivo << "Recaudado de la empresa: " << arrEmpresa[i].recaudado << endl;
    archivo << "Ventas de la empresa: " << arrEmpresa[i].ventas << endl << endl;
  }
}

void cargarArchivo() // Crea archivo, y utiliza la función mostrarStruct() para imprimir la info de las empresas ordenadas.
{
  archivo.open("ImporteEmpresas.bin", ios::out); // C++
  //FILE * f = open("ImporteEmpresas.dat","rb"); 

  if (archivo.fail())
  {
    cout << "Error al intentar abrir el archivo";
    return;
  }  
  mostrarStruct();

  archivo.close();
}
