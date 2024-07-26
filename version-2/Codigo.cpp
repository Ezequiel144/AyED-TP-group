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
    bool adherido;
};

unsigned cargandoDatos(Empresa[]);
void mostrandoVector(Empresa[], const int);
void escribiendoArchivoDeEmpresas(Empresa vect[], const int dim);
unsigned extrayendoDatos(Empresa[]);
void mostrandoVectorVentas(Venta[], const int);
void candtidadDeVentasDia(Venta[], Empresa[], const int, int[], int[]);
void mostrandoTotalventas(Empresa[], int[], const int, int[]);
void menorImporteTotal(int[], const int, Empresa[]);
void diassinventas(const int, Venta[], const int);
void separandoVentasAdheYNoAdhe(Venta[], const int, Venta[], Venta[], unsigned &, unsigned &);

int main()
{
    /*Definicion de variables*/
    const int dim = 500;
    /* unsigned codigoEmpresasAdheridas[dim]= {1111,3333,9999,5555,7777}; */
    Empresa vectEmpresas[dim];
    /*Ingreso de datos y estebleciendo la dimencion del vector*/
    unsigned dimRealVect = cargandoDatos(vectEmpresas);
    /* definiendoAdhesionEmpresas(vectEmpresas, dimRealVect, vectEmpresasAdheridas, vectEmpresasNoAdheridas, dimEmpAdheridas, dimEmpNoAdheridas); */
    cout << "-------------------------------------------------------" << endl;
    /* Mostrando las empresas ya cargadas en el vector de empresas Adheridas*/
    mostrandoVector(vectEmpresas, dimRealVect);
    cout << "-------------------------------------------------------" << endl;
    /* Escribe un archivo binario para todas las empresas(adheridas + no adheridas)*/
    escribiendoArchivoDeEmpresas(vectEmpresas, dimRealVect);

    /*punto 1) */
    /* leyendo archivo de las empresas */
    Empresa vectDatosArch[dim /*-> 500*/];
    unsigned dimVect = extrayendoDatos(vectDatosArch) - 1;
    int vectTotalImporte[dimVect] = {0};
    int vectTotalCantVentas[dimVect] = {0};
    cout << "-------------------------------------------------------" << endl;
    /* Importe total por dia  */
    Venta vectVentasEmpresas[dimVect * 3];
    Venta vectVentasEmpAdheridas[dim];
    Venta vectVentasEmpNoAdheridas[dim];
    unsigned dimVtaAdhe = 0;
    unsigned dimVtaNoAdhe = 0;

    candtidadDeVentasDia(vectVentasEmpresas, vectDatosArch, dimVect, vectTotalImporte, vectTotalCantVentas);
    cout << "-------------------------------------------------------" << endl;
    mostrandoVectorVentas(vectVentasEmpresas, dimVect * 3);

    separandoVentasAdheYNoAdhe(vectVentasEmpresas, dimVect * 3, vectVentasEmpAdheridas, vectVentasEmpNoAdheridas, dimVtaAdhe, dimVtaNoAdhe);
    /* mostrando el total de ventas de las empresas */
    /* cout << "-------------------------------------------------------" << endl;
    cout << "- Total de las empresas -" << endl;
    mostrandoTotalventas(vectDatosArch, vectTotalImporte, dimVect, vectTotalCantVentas); */

    cout << "-------------------------------------------------------" << endl;
    cout << "- Empresas Adheridas -" << endl;
    /* mostrandoVectorVentas(vectVentasEmpAdheridas, dimVtaAdhe); */
    for (int i = 0; i < dimVtaAdhe; i++)
    {
        /* for (int j = i + 1; j < dimVtaAdhe; j++)
        {
            if (vectVentasEmpAdheridas[i].importe != vectVentasEmpAdheridas[j].importe)
            {
                cout << "Codigo de empresa -> " << vectVentasEmpAdheridas[i].codigo <<"  "<< endl;
            }
        } */
       
    }

    cout << "- Empresas no Adheridas -" << endl;
    mostrandoVectorVentas(vectVentasEmpNoAdheridas, dimVtaNoAdhe);

    return 0;
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
    char valorAdherido[3];
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
        cout << "Esta adherido al HotSale? ";
        cin >> valorAdherido;
        cout << valorAdherido << endl;
        if (strcmp(valorAdherido, "si") == 0 || strcmp(valorAdherido, "SI") == 0)
        {
            vect[i].adherido = true;
        }
        else
        {
            vect[i].adherido = false;
        }
        if ((i + 1) % 3 == 0)
        {
            j++;
            contDia = 0;
        }
    }
}

unsigned extrayendoDatos(Empresa vectEmp[])
{
    FILE *lecturaArchBin = fopen("C:/Users/Ezequiel/Documents/UTN Buenos Aires/Algoy Estruc de datos 2024/TP/version-2/output/datos-de-empresas.dat", "rb");
    int cont = 0;
    if (!lecturaArchBin)
    {
        cout << "no se puede leer el archivo" << endl;
        return -1;
    }
    fseek(lecturaArchBin, 0, SEEK_SET);
    while (!feof(lecturaArchBin))
    {
        fread(&vectEmp[cont], sizeof(Empresa), 1, lecturaArchBin);
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
    /* char valorAdherido[3]; */
    cout << "- Ingrese datos de empresa -" << endl;
    cout << "Dato de empresa[" << cont + 1 << "]" << endl;
    cout << "Codigo de empresa: ";
    cin >> auxCode;
    while (auxCode != 0)
    {
        vect[cont].codigo = auxCode;
        cout << "Nombre de Empresa: ";
        cin >> vect[cont].nombre;
        /*cout << "Esta adherido al HotSale? ";
        cin >> valorAdherido;
        cout << valorAdherido << endl;
         if ( strcmp(valorAdherido, "si") == 0 || strcmp(valorAdherido, "SI") == 0)
        {
            vect[cont].adherido = true;
        }
        else
        {
            vect[cont].adherido = false;
        } */
        cont++;
        cout << "Dato de empresa[" << cont + 1 << "]" << endl;
        cout << "Codigo de empresa: ";
        cin >> auxCode;
    }
    return cont;
}

void separandoVentasAdheYNoAdhe(Venta vectVta[], const int dim, Venta vectVtaAdhe[], Venta vectVtaNoAdhe[], unsigned &dimVtaAdhe, unsigned &dimVtaNoAdhe)
{
    unsigned posAuxAdheridas = 0;   // posicion y dimencion que tendra al final el vector de empresas adheridas
    unsigned posAuxNoAdheridas = 0; // posicion y dimencion que tendra al final el vector de empresas no adheridas
    for (int i = 0; i < dim; i++)
    {
        if (vectVta[i].adherido == true)
        {
            vectVtaAdhe[posAuxAdheridas] = vectVta[i];
            posAuxAdheridas++;
        }
        else
        {
            vectVtaNoAdhe[posAuxNoAdheridas] = vectVta[i];
            posAuxNoAdheridas++;
        }
    }
    dimVtaAdhe = posAuxAdheridas;
    dimVtaNoAdhe = posAuxNoAdheridas;
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

void diassinventas(const int dimEmpresas, Venta ventas[], const int dimVentas)
{
    for (unsigned j = 0; j < dimVentas; j++)
    {
        if (ventas[j].cantVentas == 0)
        {
            cout << "Empresa: " << ventas[j].codigo << " | El dia: " << ventas[j].dia + 1 << " -> no tuvo ventas " << endl;
        }
    }
}
