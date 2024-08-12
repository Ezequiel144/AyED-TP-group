#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

// ----- struct -----
struct Empresas
{
    char nombre[50];
    int codigo;
};

struct Ventas
{
    int codigo;
    int dia;
    int importe;
};

// ----- prototipos -----

void diaMayorVenta(Ventas[][3], Empresas[], const int, const int, const int);
void menorImporteTotal(Ventas[][3], Empresas[], const int, const int, const int, int[]);
void diasSinVentas(Ventas[][3], Empresas[], const int, const int, const int);
bool busquedaDeEmpAdheridas(Ventas[][3], Empresas[], const int, int);
void totalImporteYCantidadVentas(Ventas[][3], Empresas[], const int, const int, const int, int[], int[]);
void mostrandoDatosMatrizEmp(Ventas[][3], const int, const int);
int cargandoDatosDeVentas(Ventas[][3], const int, const int);
int cargandoDatos(Empresas[]);
void mostrandoVectorEmp(Empresas[], const int);

int main()
{
    const int dim = 500;
    const int diaHotSale = 3;
    Empresas vectEmpAdhe[dim];
    Ventas matrizTodasLasEmp[dim][diaHotSale];

    int dimVectCarga = cargandoDatos(vectEmpAdhe); // Dimencion de vector de empresas adheridas

    cout << "--------------------------------------------" << endl;
    cout << "- Mostrando empresas adheridas - " << endl;
    mostrandoVectorEmp(vectEmpAdhe, dimVectCarga);

    cout << "--------------------------------------------" << endl;
    cout << "- Cargardo las ventas de empresas - " << endl;
    int dimCargaDeEmpresas = cargandoDatosDeVentas(matrizTodasLasEmp, dim, diaHotSale); // Dimencion de matriz de ventas → columna

    cout << "--------------------------------------------" << endl;
    cout << "- Mostrando las ventas del HotSale de todas las empresas - " << endl;
    mostrandoDatosMatrizEmp(matrizTodasLasEmp, dimCargaDeEmpresas, diaHotSale);

    // Punto 1.
    cout << "--------------------------------------------" << endl;
    cout << "- Importe total de empresas adheridas -" << endl;
    int importeTotal[dimCargaDeEmpresas] = {0};
    int cantidadVentasTotal[dimCargaDeEmpresas] = {0};
    totalImporteYCantidadVentas(matrizTodasLasEmp, vectEmpAdhe, dimCargaDeEmpresas, diaHotSale, dimVectCarga, importeTotal, cantidadVentasTotal);

    // Punto 2.
    cout << "--------------------------------------------" << endl;
    cout << "- Dias que no se realizaron ventas de empresas adheridas -" << endl;
    diasSinVentas(matrizTodasLasEmp, vectEmpAdhe, dimCargaDeEmpresas, dimVectCarga, diaHotSale);

    // Punto 3.
    cout << "--------------------------------------------" << endl;
    cout << "- Empresas que recaudaron el menor importe total -" << endl;
    menorImporteTotal(matrizTodasLasEmp, vectEmpAdhe, dimCargaDeEmpresas, dimVectCarga, diaHotSale, importeTotal);

    cout << "--------------------------------------------" << endl;
    cout << "- Mayor venta que hubo en los 3 dias por empresas -" << endl;
    diaMayorVenta(matrizTodasLasEmp, vectEmpAdhe, dimCargaDeEmpresas, dimVectCarga, diaHotSale);


    return 0;
}

// ----- funciones -----

void diaMayorVenta(Ventas matriz[][3], Empresas vectEmp[], const int dimMatriz, const int dimEmp, const int dia)
{
    int mayor = matriz[0][0].importe;
    int posJ = 0;
    for (int i = 0; i < dimMatriz; i++)
    {
        if (busquedaDeEmpAdheridas(matriz, vectEmp, dimEmp, i))
        {

            cout << "Codigo de empresa: " << matriz[i][0].codigo << endl;
            for (int j = 0; j < dia; j++)
            {
                if (matriz[i][j].importe > mayor)
                {
                    mayor = matriz[i][j].importe;
                    posJ = j;
                }
            }
            cout << "El dia " << matriz[i][posJ].dia << " tubo la mayor venta de " << matrizTodasLasEmp[i][posJ].importe << endl;
        }
    }
}

void menorImporteTotal(Ventas matriz[][3], Empresas vectEmp[], const int dimMatriz, const int dimEmp, const int dia, int importeTotal[])
{
    int menor = importeTotal[0];
    for (int i = 0; i < dimMatriz; i++)
    {
        if (busquedaDeEmpAdheridas(matriz, vectEmp, dimEmp, i))
        {
            for (int j = 0; j < dia; j++)
            {
                if (importeTotal[i] < menor)
                {
                    menor = importeTotal[i];
                }
            }
        }
    }

    for (int i = 0; i < dimMatriz; i++)
    {
        if (menor == importeTotal[i])
        {
            cout << "Codigo de empresa -> " << matriz[i][0].codigo << " | importe total -> " << importeTotal[i] << endl;
        }
    }
}

void diasSinVentas(Ventas matriz[][3], Empresas vectEmp[], const int dimMatriz, const int dimEmp, const int dia)
{
    for (int i = 0; i < dimMatriz; i++)
    {
        if (busquedaDeEmpAdheridas(matriz, vectEmp, dimEmp, i))
        {
            cout << "Codigo empresa: " << matriz[i][0].codigo << endl;
            for (int j = 0; j < dia; j++)
            {
                if (matriz[i][j].importe == 0)
                {
                    cout << " Dia -> " << matriz[i][j].dia << ",  sin ventas" << endl;
                }
            }
            /* if (matriz[i][2].importe != 0)
            {
                cout << " Todos lo dias hubo venta " << endl;
            } */
        }
    }
}

bool busquedaDeEmpAdheridas(Ventas matriz[][3], Empresas vectEmpAdhe[], const int dimCarga, int i)
{
    bool condicionDeComparar = false;
    for (int k = 0; k < dimCarga; k++)
    {
        if (matriz[i][0].codigo == vectEmpAdhe[k].codigo)
        {
            condicionDeComparar = true;
        }
    }
    return condicionDeComparar;
}

void totalImporteYCantidadVentas(Ventas matrizVtas[][3], Empresas vectEmpAdhe[], const int dimEmpresas, const int dia, const int dimVectCarga, int importeTotal[], int cantidadVentasTotal[])
{
    /* int importeTotal[dimEmpresas] = {0};
    int cantidadVentasTotal[dimEmpresas] = {0}; */

    for (int i = 0; i < dimEmpresas; i++)
    {
        if (busquedaDeEmpAdheridas(matrizVtas, vectEmpAdhe, dimVectCarga, i))
        {
            for (int j = 0; j < dia; j++)
            {

                if (matrizVtas[i][j].importe != 0)
                {
                    cantidadVentasTotal[i]++;
                }
                importeTotal[i] += matrizVtas[i][j].importe;
            }
        }
    }

    for (int i = 0; i < dimEmpresas; i++)
    {
        if (importeTotal[i] != 0)
        {
            cout << "Importe total -> " << importeTotal[i] << " | Cantidad de ventas -> " << cantidadVentasTotal[i] << endl;
        }
    }
}

void mostrandoDatosMatrizEmp(Ventas matrizVtas[][3], const int dim, const int dia)
{
    for (int i = 0; i < dim; i++)
    {
        cout << "Codigo de empresa: " << matrizVtas[i][0].codigo << endl;
        for (int j = 0; j < dia; j++)
        {
            cout << "dia -> " << matrizVtas[i][j].dia << " | importe -> " << matrizVtas[i][j].importe << endl;
        }
    }
}

int cargandoDatosDeVentas(Ventas matrizVtas[][3], const int dim, const int dia)
{
    int pos = 0;
    for (pos = 0; pos < dim; pos++)
    {
        cout << "Codigo de empresa: ";
        cin >> matrizVtas[pos][0].codigo;
        if (matrizVtas[pos][0].codigo == 0)
        {
            break;
        }
        for (int j = 0; j < dia; j++)
        {
            matrizVtas[pos][j].dia = j + 1;
            cout << "dia: " << matrizVtas[pos][j].dia << endl;
            cout << "importe: ";
            cin >> matrizVtas[pos][j].importe;
        }
    }
    return pos;
}

void mostrandoVectorEmp(Empresas vect[], const int dim)
{
    for (int i = 0; i < dim - 1; i++)
    {
        cout << "Codigo de empresa: " << vect[i].codigo << " | Nombre de empresa: " << vect[i].nombre << endl;
    }
}

int cargandoDatos(Empresas vect[])
{
    FILE *archLectura = fopen("C:/Users/Ezequiel/Documents/UTN Buenos Aires/Algoy Estruc de datos 2024/TP/reHacer/output/Datos-emp-adhe.dat", "rb");
    int pos = 0;
    while (!feof(archLectura))
    {
        fread(&vect[pos], sizeof(Empresas), 1, archLectura);
        pos++;
    }
    return pos;
}