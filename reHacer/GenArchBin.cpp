#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

struct Empresas
{
    char nombre[50];
    int codigo;
};

int cargarDatos(Empresas[]);
void mostrandoVector(Empresas[], const int);
void creandoyEscribiendoArchivoBin(Empresas[], const int);

int main()
{
    const int dim = 500;
    Empresas vectEmp[dim];

    int dimVectEmpCargada = cargarDatos(vectEmp);

    mostrandoVector(vectEmp, dimVectEmpCargada);

    creandoyEscribiendoArchivoBin(vectEmp, dimVectEmpCargada);

    return 0;
}

void creandoyEscribiendoArchivoBin(Empresas emp[], const int dim)
{
    FILE *archBin = fopen("Datos-emp-adhe.dat", "wb");
    for (int i = 0; i < dim; i++)
    {
        fwrite(&emp[i], sizeof(Empresas), 1, archBin);
    }
}

void mostrandoVector(Empresas emp[], const int dim)
{
    for (int i = 0; i < dim; i++)
    {
        cout << "Codigo empresa -> " << emp[i].codigo << " | Nombre empresa -> " << emp[i].nombre << endl;
    }
}

int cargarDatos(Empresas emp[])
{

    int codigo = 0;
    int pos = 0;

    cout << "Codigo de empresa: ";
    cin >> codigo;
    while (codigo != 0)
    {
        emp[pos].codigo = codigo;
        cout << "Nombre de empresa: ";
        cin.ignore();
        cin.getline(emp[pos].nombre, 50);
        cout << "Codigo de empresa: ";
        cin >> codigo;
        pos++;
    }

    return pos;
}
