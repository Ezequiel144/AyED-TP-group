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

void cargandoEmpNoAdhe(Ventas[][3], Empresas[], const int, const int, const int);
void creandoGuardandoArchBin(Ventas[][3], Empresas[], int[], int[], const int, const int);
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

    // Punto 4.
    cout << "--------------------------------------------" << endl;
    cout << "- Mayor venta que hubo en los 3 dias por empresas -" << endl;
    diaMayorVenta(matrizTodasLasEmp, vectEmpAdhe, dimCargaDeEmpresas, dimVectCarga, diaHotSale);

    // Punto 5.
    cout << "--------------------------------------------" << endl;
    cout << "- Ventas ordenadas y guardandolo en un archivo ImporteEmpresas.dat -" << endl;

    // mostrandoDatosMatrizEmp(matrizTodasLasEmp, dimCargaDeEmpresas, diaHotSale);

    creandoGuardandoArchBin(matrizTodasLasEmp, vectEmpAdhe, cantidadVentasTotal, importeTotal, dimCargaDeEmpresas, dimVectCarga);

    // Punto 6.
    cout << "--------------------------------------------" << endl;
    cout << "- Creando y guardando dato de empresas no adheridas al archivo SinAhdesion.dat -" << endl;
    cargandoEmpNoAdhe(matrizTodasLasEmp,vectEmpAdhe,dimCargaDeEmpresas,dimVectCarga,diaHotSale);
    return 0;
}

// ----- funciones -----
void cargandoEmpNoAdhe(Ventas matriz[][3], Empresas vectEmp[], const int dimMatriz, const int dimEmp, const int dia)
{
    FILE *escribirArch = fopen("SinAhdesion.dat", "wb");
    for (int i = 0; i < dimMatriz; i++)
    {
        if (!busquedaDeEmpAdheridas(matriz, vectEmp, dimEmp, i))
        {
            cout << "Codigo de empresa -> " << matriz[i][0].codigo << endl;
            fwrite(&matriz[i][0].codigo, sizeof(int), 1, escribirArch);
            for (int j = 0; j < dia; j++)
            {
                cout << " dia -> " << matriz[i][j].dia << " | importe -> " << matriz[i][j].importe << endl;
                fwrite(&matriz[i][j].dia, sizeof(int), 1, escribirArch);
                fwrite(&matriz[i][j].importe, sizeof(int), 1, escribirArch);
            }
        }
    }
}

void creandoGuardandoArchBin(Ventas matriz[][3], Empresas vectEmp[], int cantidadVentasTotal[], int importeTotal[], const int dimMatriz, const int dimEmp)
{
    FILE *escribirArch = fopen("ImporteEmpresas.dat", "wb");

    for (int i = 0; i < dimMatriz; i++)
    {
        if (busquedaDeEmpAdheridas(matriz, vectEmp, dimEmp, i))
        {
            fwrite(&matriz[i][0].codigo, sizeof(int), 1, escribirArch);
            // cout << matriz[i][0].codigo << endl;
            for (int k = 0; k < dimEmp; k++)
            {
                if (matriz[i][0].codigo == vectEmp[k].codigo)
                {
                    fwrite(&vectEmp[k].nombre, sizeof(int), 1, escribirArch);
                    // cout << vectEmp[k].nombre << endl;
                }
            }
        }
        fwrite(&cantidadVentasTotal[i], sizeof(int), 1, escribirArch);
        fwrite(&importeTotal[i], sizeof(int), 1, escribirArch);
        // cout << cantidadVentasTotal[i] << endl;
        // cout << importeTotal[i] << endl;
    }
}

void ordenamientoDecreciente(Ventas matriz[][3], const int dimMatriz)
{
    Ventas aux;
    for (int i = 0; i < dimMatriz - 1; i++)
    {
        for (int j = i + 1; j < dimMatriz; j++)
        {
            if (matriz[i][0].codigo < matriz[j][0].codigo)
            {
                aux = matriz[i][0];
                matriz[i][0] = matriz[j][0];
                matriz[j][0] = aux;
            }
        }
    }
}

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
                    // cout << "posicion de dias " << j << endl;
                    posJ = j;
                }
            }
            cout << "El dia " << matriz[i][posJ].dia + 1 << " tubo la mayor venta de " << matriz[i][posJ].importe << endl;
            mayor = matriz[i][0].importe;
        }
    }
}
// arreglar
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
    { // arreglar
        if (menor != importeTotal[i])
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
                    cout << " Dia -> " << matriz[i][j].dia + 1 << ",  sin ventas" << endl;
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
            cout << "dia -> " << matrizVtas[i][j].dia + 1 << " | importe -> " << matrizVtas[i][j].importe << endl;
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
            matrizVtas[pos][j].dia = j;
            cout << "dia: " << matrizVtas[pos][j].dia << endl;
            cout << "importe: ";
            cin >> matrizVtas[pos][j].importe;
        }
    }

    // Ordenando la matriz de forma decreciente(mayor - menor)
    ordenamientoDecreciente(matrizVtas, dim);

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