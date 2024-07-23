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
    unsigned cantVentas; /* Rehacerlo y modificar*/
};
/*
struct VentasTotalEmpresa{
    unsigned codigo;
    char nombre[30];
    unsigned dia;
    unsigned importe;
    unsigned cantVentas;
};
 */
unsigned cargandoDatos(Empresa[]);
void mostrandoVector(Empresa[], const int);
void escribiendoArchivoDeEmpresas(Empresa vect[], const int dim);
unsigned extrayendoDatos(Empresa[]);
void mostrandoVectorVentas(Venta[], const int);
void candtidadDeVentasDia(Venta[], Empresa[], const int, int[], int[]);
void mostrandoTotalventas(Empresa[], int[], const int,int[]);

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
    escribiendoArchivoDeEmpresas(vectEmpresas, dimRealVect);

    /* leyendo archivo de las empresas */
    Empresa vectDatosArch[dim /*-> 500*/];
    unsigned dimVect = extrayendoDatos(vectDatosArch) - 1;
    int vectTotalImporte[dimVect] = {0};
    int vectTotalCantVentas[dimVect] = {0};

    /* Importe total por dia  */
    Venta vectVentasEmpresas[dimVect * 3];
    candtidadDeVentasDia(vectVentasEmpresas, vectDatosArch, dimVect, vectTotalImporte, vectTotalCantVentas);
    cout << "-------------------------------------------------------" << endl;
    mostrandoVectorVentas(vectVentasEmpresas, dimVect * 3);
    /* mostrando el total de ventas de las empresas */
    cout << "-------------------------------------------------------" << endl;
    cout << "- Total de las empresas -" << endl;
    mostrandoTotalventas(vectDatosArch, vectTotalImporte, dimVect, vectTotalCantVentas);

    return 0;
}

void mostrandoTotalventas(Empresa vect[], int vectTotal[], const int dim, int vectTotalCantVentas[])
{
    for (int i = 0; i < dim; i++)
    {
        cout << "Nombre de empresa -> " << vect[i].nombre << " | Total de ventas: " << vectTotalCantVentas[i] << " | Importe total -> " << vectTotal[i] << endl;
    }
}

void candtidadDeVentasDia(Venta vect[], Empresa vectTwo[], const int dim, int vectTotalImporte[], int vectTotalCantVentas[])
{
    unsigned j = 0;
    unsigned contDia = 0;
    /* Venta vectVentasEmpresas[dim * 3]; */

    for (int i = 0; i < dim * 3; i++)
    {
        vect[i].codigo = vectTwo[j].codigo;
        cout << "Nombre de empresa: " << vectTwo[j].nombre << endl;
        vect[i].dia = contDia++;
        cout << "Dia: " << contDia << endl;
        cout << "Cantidad de ventas: ";
        cin >> vect[i].cantVentas;
        vectTotalCantVentas[j] += vect[i].cantVentas;
        cout << "Importe: ";
        cin >> vect[i].importe;
        vectTotalImporte[j] += vect[i].importe;
        if ((i + 1) % 3 == 0)
        {
            j++;
            contDia = 0;
        }
    }
}

unsigned extrayendoDatos(Empresa vect[])
{
    FILE *lecturaArchBin = fopen("C:/Users/Ezequiel/Documents/UTN Buenos Aires/Algoy Estruc de datos 2024/TP/output/datos-de-empresas.dat", "rb");
    int cont = 0;
    /* Empresa vectDatosArch[500]; */
    fseek(lecturaArchBin, 0, SEEK_SET);
    while (!feof(lecturaArchBin))
    {
        fread(&vect[cont], sizeof(Empresa), 1, lecturaArchBin);
        cont++;
    }
    return cont;
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

void mostrandoVectorVentas(Venta vect[], const int dim)
{
    /* cout << "Cantidad de empresas cargadas: " << dim << endl; */
    for (int i = 0; i < dim; i++)
    {
        cout << "Codigo de empresa -> " << vect[i].codigo << " | Dia -> " << vect[i].dia + 1 << " | Cantidad de ventas: " << vect[i].cantVentas << " | Importe -> " << vect[i].importe << endl;
    }
}