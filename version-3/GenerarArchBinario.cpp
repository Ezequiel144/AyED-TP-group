#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

struct Empresa
{
    unsigned codigo;
    char nombre[30];
    bool adherido;
};

void escribiendoArchivoDeEmpresas(Empresa[], const int);
unsigned cargandoDatos(Empresa[]);
void mostrandoVector(Empresa[], const int);
void mostrandoEmpresasAdheridas(Empresa[], const int);

int main()
{
    const int dim = 500;
    Empresa vectEmpresas[dim];
    /*Ingreso de datos y estebleciendo la dimencion del vector*/
    unsigned dimRealVect = cargandoDatos(vectEmpresas);
    cout << "-------------------------------------------------------" << endl;
    /* Mostrando las empresas ya cargadas en el vector */
    mostrandoVector(vectEmpresas, dimRealVect);
    //Mostrando las empresas Adheridas
    cout << "-------------------------------------------------------" << endl;
    cout << " - Empresas adheridas al HotSale - " << endl;
    mostrandoEmpresasAdheridas(vectEmpresas,dimRealVect);
    /* Escribe un archivo binario */
    escribiendoArchivoDeEmpresas(vectEmpresas, dimRealVect);

    return 0;
}

void mostrandoEmpresasAdheridas(Empresa vect[], const int dim)
{
    for (int i = 0; i < dim; i++)
    {
        if (vect[i].adherido)
        {
            cout << "Codigo de empresa -> " << vect[i].codigo << " | Nombre de empresa -> " << vect[i].nombre << endl;
        }
    }
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
    char valorAdherido[3];
    cout << "- Ingrese datos de empresa -" << endl;
    cout << "Dato de empresa[" << cont + 1 << "]" << endl;
    cout << "Codigo de empresa: ";
    cin >> auxCode;
    while (auxCode != 0)
    {
        vect[cont].codigo = auxCode;
        cout << "Nombre de Empresa: ";
        cin >> vect[cont].nombre;
        cout << "Esta adherisa al HotSale? ";
        cin >> valorAdherido;
        if (strcmp(valorAdherido, "si") == 0 || strcmp(valorAdherido, "SI") == 0)
        {
            vect[cont].adherido = true;
        }
        else
        {
            vect[cont].adherido = false;
        }
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
        cout << "Codigo de empresa -> " << vect[i].codigo << " | Nombre de empresa -> " << vect[i].nombre << " | HotSale? -> " << vect[i].adherido << endl;
    }
}
