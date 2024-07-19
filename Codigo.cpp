#include <iostream>
#include <stdio.h>

using namespace std;

struct Empresa
{
    unsigned codigo;
    char nombre[30];
};

struct Venta
{
    unsigned dia;
    unsigned codigo;
    unsigned importe;
};

unsigned cargandoDatos(Empresa[]);
void mostrandoVector(Empresa[], const int);
void escribiendoArchivoDeEmpresas(Empresa vect[], const int dim);

int main()
{
    /*Definicion de variables*/
    const int dim = 500;
    Empresa vectEmpresas[dim];
    /*Ingreso de datos y estebleciendo la dimencion del vector*/
    unsigned dimRealVect = cargandoDatos(vectEmpresas);
    cout << "-------------------------------------------------------" << endl;
    /* Mostrando las empresas ya cargadas en el vector */
    mostrandoVector(vectEmpresas, dimRealVect);
    /* Escribe un archivo binario */
    escribiendoArchivoDeEmpresas(vectEmpresas,dimRealVect);
    
    return 0;
}

void escribiendoArchivoDeEmpresas(Empresa vect[], const int dim)
{
    FILE *archEscribir = fopen("datos-de-empresas.dat", "wb");
    for (int i = 0; i < dim; i++)
    {
        fwrite(&vect[i], sizeof(Empresa), 1, archEscribir);
    }
    fclose(archEscribir);
}

unsigned cargandoDatos(Empresa vect[])
{
    unsigned cont = 0;
    unsigned auxCode;
    cout << "- Ingrese datos de empresa -" << endl;
    cout << "Dato de empresa[" << cont + 1 << "]" << endl;
    cout << "Codigo de empresa: ";
    cin >> auxCode;
    while (auxCode != 0)
    {
        vect[cont].codigo = auxCode;
        cout << "Nombre de Empresa: ";
        cin >> vect[cont].nombre;
        cont++;
        cout << "Dato de empresa[" << cont + 1 << "]" << endl;
        cout << "Codigo de empresa: ";
        cin >> auxCode;
    }
    return cont;
}

void mostrandoVector(Empresa vect[], const int dim)
{
    cout << "Cantidad de empresas cargadas: " << dim << endl;
    for (int i = 0; i < dim; i++)
    {
        cout << "Codigo de empresa -> " << vect[i].codigo << " | Nombre de empresa -> " << vect[i].nombre << endl;
    }
}