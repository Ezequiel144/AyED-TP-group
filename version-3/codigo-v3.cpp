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

struct Venta
{
    unsigned dia;
    unsigned codigo;
    unsigned importe;
    unsigned cantVentas;
};

unsigned cargandoDatos(Empresa[]);
void mostrandoVector(Empresa[], const int);
void escribiendoArchivoDeEmpresas(Empresa vect[], const int dim);
unsigned extrayendoDatos(Empresa[], int[], unsigned &);
void mostrandoVectorVentas(Venta[], const int);
void candtidadDeVentasDia(Venta[], Empresa[], const int, int[], int[]);
void mostrandoTotalventas(Empresa[], int[], const int, int[],int [], const unsigned);
void menorImporteTotal(int[], const int, Empresa[]);
void diassinventas(Empresa[], const int, Venta[], const int);
void mostrandoEmpresasAdheridas(int[], const unsigned);
unsigned candtidadDeVentasDiaAdhe(Venta[], Venta[], const unsigned, int[], const unsigned);

int main()
{
    const int dim = 500;
    /* leyendo archivo de las empresas */
    Empresa vectDatosArch[dim /*-> 500*/];

    int codigoEmpAdheridas[dim];
    unsigned dimCodigoAdhe;

    unsigned dimVect = extrayendoDatos(vectDatosArch, codigoEmpAdheridas, dimCodigoAdhe) - 1;

    int vectTotalImporte[dimVect] = {0};
    int vectTotalCantVentas[dimVect] = {0};
    /* cout << " - Empresas adheridas al HotSale - " << endl;
    mostrandoEmpresasAdheridas(codigoEmpAdheridas, dimCodigoAdhe); */
    cout << "-------------------------------------------------------" << endl;
    /* Importe total por dia de todas las empresas*/
    Venta vectVentasEmpresas[dimVect * 3];
    candtidadDeVentasDia(vectVentasEmpresas, vectDatosArch, dimVect, vectTotalImporte, vectTotalCantVentas);


    //  separando las empresas que estan adherida el HotSale
    Venta vectVtasEmpAdhe[dimCodigoAdhe * 3];
    //candtidadDeVentasDia(vectVtasEmpAdhe, vectDatosArch, dimCodigoAdhe, vectTotalImporte, vectTotalCantVentas);
    unsigned dimVtaEmpAdhe = 0;// borrar

    cout << "-------------------------------------------------------" << endl;
    cout << " - Cantidad de ventas e importes por dia de todas las empresas - " << endl;
    mostrandoVectorVentas(vectVentasEmpresas, dimVect * 3);

    /* cout << "-------------------------------------------------------" << endl;
    cout << " - Cantidad de ventas e importes por dia de empresas adheridas al HotSale - " << endl;
    dimVtaEmpAdhe = candtidadDeVentasDiaAdhe(vectVentasEmpresas, vectVtasEmpAdhe, dimCodigoAdhe, codigoEmpAdheridas, dimCodigoAdhe);
 */


    /*punto-1 Informar por cada día de la promoción cantidad de ventas e importe total recaudado por cada empresa adheridas */
    cout << "-------------------------------------------------------" << endl;
    cout << "- Total de las empresas Adheridas -" << endl;
    mostrandoTotalventas(vectDatosArch, vectTotalImporte, dimVect, vectTotalCantVentas, codigoEmpAdheridas,dimCodigoAdhe);

    /* punto-2 */
    cout << "---------------------------------------------------------" << endl;
    cout << "- Dias que no se realizaron ventas de empresas adheridas al HotSale - " << endl;
    diassinventas(vectDatosArch, dimVect, vectVentasEmpresas, dimVect * 3);

    /*Punto 3) */
    /*Informar la o las empresas que recaudaron el menor importe total, informando también dicho importe*/
    cout << "---------------------------------------------------------" << endl;
    menorImporteTotal(vectTotalImporte, dimVect, vectDatosArch);

    return 0;
}

unsigned candtidadDeVentasDiaAdhe(Venta vectVta[], Venta vectVtaAdhe[], const unsigned dim, int vectCodego[], const unsigned dimCodigo)
{
    unsigned l = 0;
    for (unsigned j = 0; j < dim * 3; j++)
    {
        for (unsigned k = 0; k < dimCodigo; k++)
        {
            if (vectVta[j].codigo == vectCodego[k])
            {
                vectVtaAdhe[l] = vectVta[j];
                cout << "Codigo de empresa -> " << vectVta[j].codigo << " | dia -> " << vectVta[j].dia + 1 << " | cant ventas -> " << vectVta[j].cantVentas << " | importe -> " << vectVta[j].importe << endl;
                l++;
            }
        }
    }
    return l;
}

void menorImporteTotal(int vectImport[], const int dim, Empresa vectDato[])
{
    int menorImporte = vectImport[0];
    for (int i = 0; i < dim; i++)
    {
        if (menorImporte > vectImport[i])
        {
            menorImporte = vectImport[i];
        }
    }

    for (int j = 0; j < dim; j++)
    {
        if (vectImport[j] == menorImporte)
        {
            cout << "La empresa que tubo el menor importe total es -> " << vectDato[j].nombre << ",con el importe de -> " << menorImporte << endl;
        }
    }
}

void mostrandoTotalventas(Empresa vect[], int vectTotal[], const int dim, int vectTotalCantVentas[],int codigoEmpAdheridas[], const unsigned dimCodigoAdhe)
{
    /* for (int i = 0; i < dim; i++)
    {
        cout << "Nombre de empresa -> " << vect[i].nombre << " | Total de ventas: " << vectTotalCantVentas[i] << " | Importe total -> " << vectTotal[i] << endl;
    } */

    for (unsigned i = 0; i < dim; i++)
    {
        for (unsigned j = 0; j < dimCodigoAdhe; j++)
        {
            if(vect[i].codigo == codigoEmpAdheridas[j]){
                cout << "Nombre de empresa -> " << vect[i].nombre << " | Total de ventas: " << vectTotalCantVentas[i] << " | Importe total -> " << vectTotal[i] << endl;
            }
        }
        
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

unsigned extrayendoDatos(Empresa vect[], int codigoAdhe[], unsigned &dimCodigoAshe)
{
    FILE *lecturaArchBin = fopen("C:/Users/Ezequiel/Documents/UTN Buenos Aires/Algoy Estruc de datos 2024/TP/version-3/output/datos-de-empresas.dat", "rb");
    int cont = 0;
    unsigned i = 0;
    /* Empresa vectDatosArch[500]; */
    fseek(lecturaArchBin, 0, SEEK_SET);
    while (!feof(lecturaArchBin))
    {
        fread(&vect[cont], sizeof(Empresa), 1, lecturaArchBin);
        if (vect[cont].adherido == true)
        {
            codigoAdhe[i] = vect[cont].codigo;
            i++;
        }
        cont++;
    }
    dimCodigoAshe = i;
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

void mostrandoVectorVentas(Venta vect[], const int dim)
{
    /* cout << "Cantidad de empresas cargadas: " << dim << endl; */
    for (int i = 0; i < dim; i++)
    {
        cout << "Codigo de empresa -> " << vect[i].codigo << " | Dia -> " << vect[i].dia + 1 << " | Cantidad de ventas: " << vect[i].cantVentas << " | Importe -> " << vect[i].importe << endl;
    }
}

void diassinventas(Empresa empresa[], const int dimEmpresas, Venta ventas[], const int dimVentas)
{
    for (unsigned j = 0; j < dimVentas; j++)
    {
        if (ventas[j].cantVentas == 0)
        {
            cout << "Empresa: " << ventas[j].codigo << " | El dia: " << ventas[j].dia + 1 << " -> no tuvo ventas " << endl;
        }
    }
}

void mostrandoEmpresasAdheridas(int vectCodigo[], const unsigned dim)
{
    for (unsigned i = 0; i < dim; i++)
    {
        cout << "Codigo de empresa -> " << vectCodigo[i] << endl;
    }
}