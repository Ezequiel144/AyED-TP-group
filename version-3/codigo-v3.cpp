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
// void mostrandoVector(Empresa[], const int);
void escribiendoArchivoDeEmpresas(Empresa vect[], const int dim);
unsigned extrayendoDatos(Empresa[], int[], unsigned &);
void mostrandoVectorVentas(Venta[], const int);
void candtidadDeVentasDia(Venta[], Empresa[], const int, int[], int[]);
void mostrandoTotalventas(Empresa[], int[], const int, int[], int[], const unsigned);
// void mostrandoTotalventas(Empresa[], Venta[], int[], const int, int[]);
// void menorImporteTotal(int[], const int, Empresa[]);
void menorImporteTotal(unsigned[], const int, int[], const int);
void diassinventas(Venta[], const int);
// void mostrandoEmpresasAdheridas(int[], const unsigned);
void separandoEmpAdheridas(Venta[], Venta[], Venta[], int[], const int, const int, int &, int &);
/* unsigned candtidadDeVentasDiaAdhe(Venta[], Venta[], const unsigned, int[], const unsigned); */
void mayordiaventas(Venta[], int);
unsigned totalEmpresasAdhe(unsigned[], const int, Venta[], unsigned[]);

int main()
{
    const int dim = 500;
    /* leyendo archivo de las empresas */
    Empresa vectDatosArch[dim /*-> 500*/];

    /* Vector de codigos de empresas adheridas con su dimencion  */
    int codigoEmpAdheridas[dim];
    unsigned dimCodigoAdhe;

    unsigned dimVect = extrayendoDatos(vectDatosArch, codigoEmpAdheridas, dimCodigoAdhe) - 1;

    int vectTotalImporte[dimVect] = {0};
    int vectTotalCantVentas[dimVect] = {0};
    unsigned vectTotalImportAdhe[dimVect] = {0};
    cout << "-------------------------------------------------------" << endl;
    /* Importe total por dia de todas las empresas*/
    Venta vectVentasEmpresas[dimVect * 3];
    candtidadDeVentasDia(vectVentasEmpresas, vectDatosArch, dimVect, vectTotalImporte, vectTotalCantVentas);
    cout << "-------------------------------------------------------" << endl;
    cout << " - Separando en 2 vectores de empresas que estan adheridas al HotSale y las que NO - " << endl;
    // Separamos por vector las empresas adheridas de las que no
    Venta vectVtasEmpAdhe[dimCodigoAdhe * 3];               // usamos su dimencion a "dimCodigoAdhe" que nos da la cantidad de empresas y triplicado por los dias del hotsale(3)
    Venta vectVtasEmpNoAdhe[(dimVect - dimCodigoAdhe) * 3]; // su dimencion es la resta de "dimVect-dimCodigoAdhe", ya que "dimVect" es la dimencion del vector cuando se extrajo los datos del arhivo binario y "dimCodigoAdhe" es la dimencion de las empresas que se incorporaron al hot sale. por ultiimo lo multiplicamos por los 3 dias del HotSale
    int dimVtaAdhe = 0;                                     // indicara la posicion del vector de ventas de empresas adheridas
    int dimVtaNoAdhe = 0;                                   // indicara la posicion del vector de ventas de empresas no adheridas

    separandoEmpAdheridas(vectVentasEmpresas, vectVtasEmpAdhe, vectVtasEmpNoAdhe, codigoEmpAdheridas, dimVect, dimCodigoAdhe, dimVtaAdhe, dimVtaNoAdhe);

    cout << "-------------------------------------------------------" << endl;
    cout << " - Cantidad de ventas e importes por dia de todas las empresas - " << endl;
    mostrandoVectorVentas(vectVentasEmpresas, dimVect * 3);

    /* cout << "-------------------------------------------------------" << endl;
    cout << " - mostrando empresas adheridas al HotSale - " << endl;
    for (int i = 0; i < dimVtaAdhe; i++)
    {
        cout << vectVtasEmpAdhe[i].codigo << endl;
    } */

    /*punto-1 Informar por cada día de la promoción cantidad de ventas e importe total recaudado por cada empresa adheridas */
    cout << "-------------------------------------------------------" << endl;
    cout << "- Total de las empresas Adheridas -" << endl;
    // mostrandoTotalventas(vectDatosArch, vectTotalImporte, dimVect, vectTotalCantVentas, codigoEmpAdheridas, dimCodigoAdhe);
    unsigned vectTotalImportePrueba[dimVect] = {0};
    unsigned vectTotalCantVtaPrueba[dimVect] = {0};
    unsigned dimTotalImporte = 0;

    dimTotalImporte = totalEmpresasAdhe(vectTotalImportePrueba, dimVtaAdhe, vectVtasEmpAdhe, vectTotalCantVtaPrueba);

    /* punto-2 */
    cout << "---------------------------------------------------------" << endl;
    cout << "- Dias que no se realizaron ventas de empresas adheridas al HotSale - " << endl;
    diassinventas(vectVtasEmpAdhe, dimVtaAdhe);

    /*Punto-3 */
    /*Informar la o las empresas que recaudaron el menor importe total, informando también dicho importe*/
    cout << "---------------------------------------------------------" << endl;
    // enconetra cual es el menor importe total de las empresas adheridas
    unsigned menorImporte = vectTotalImportePrueba[0];

    menorImporteTotal(vectTotalImportePrueba, dimTotalImporte, codigoEmpAdheridas, dimCodigoAdhe);

    /*Punto-4*/
    cout << "---------------------------------------------------------" << endl;
    mayordiaventas(vectVtasEmpAdhe, dimVtaAdhe);
    /*Punto-5*/


    return 0;
}
/* funciones punto-5 */
void ordenamientoEmpresa() // Función para ordenar las empresas por su código indentificador. 
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


/* ----- */
unsigned totalEmpresasAdhe(unsigned totalImport[], const int dimVta, Venta vtasEmpAdhe[], unsigned totalCantVta[])
{
    // hace los importes totales de cada empresa adherida
    unsigned posImporte = 0;
    for (int i = 0; i < dimVta; i += 3)
    {
        for (int j = i; j < (i + 3); j++)
        {
            totalImport[posImporte] += vtasEmpAdhe[j].importe;
            totalCantVta[posImporte] += vtasEmpAdhe[j].cantVentas;
        }
        posImporte++;
    }

    // muestra el importe total de cada empresa adherida por consola
    unsigned posAdhe = 0;
    for (unsigned h = 0; h < posImporte; h++)
    {
        cout << "Codigo de empresa -> " << vtasEmpAdhe[posAdhe].codigo << " | total cantidad de ventas -> " << totalCantVta[h] << " | Importe total -> " << totalImport[h] << endl;
        posAdhe += 3;
    }

    return posImporte;
}

void separandoEmpAdheridas(Venta vectVentasEmpresas[], Venta VtasEmpAdhe[], Venta VtasEmpNoAdhe[], int codigoEmpAdhe[], const int dimVect, const int dimCodigoEmpAdhe, int &dimAdhe, int &dimNoAdhe)
{
    int posAdhe = 0;   // indicara la posicion del vector de ventas de empresas adheridas
    int posNoAdhe = 0; // indicara la posicion del vector de ventas de empresas no adheridas
    bool var = false;

    for (int j = 0; j < dimVect * 3; j++)
    {
        // condicion que compara el "codigo de todas las empresas" con "el codigo de las adheridas" para sacar los vectores de ventas de las empreasas adheridas y las  no adheridas
        for (int k = 0; k < dimCodigoEmpAdhe; k++)
        {
            if (vectVentasEmpresas[j].codigo == codigoEmpAdhe[k])
            {
                VtasEmpAdhe[posAdhe] = vectVentasEmpresas[j]; // agregar al vector de eventas de empresas adheridas
                cout << "parte del vector ventas de empresas adherida -> " << vectVentasEmpresas[j].codigo << " | dia -> " << vectVentasEmpresas[j].dia << endl;

                posAdhe++;
            }
        }
    }
    for (int i = 0; i < dimVect * 3; i++)
    {
        for (int h = 0; h < dimCodigoEmpAdhe; h++)
        {
            if (vectVentasEmpresas[i].codigo == codigoEmpAdhe[h])
            {
                var = true;
            }
        }
        if (!var)
        {
            VtasEmpNoAdhe[posNoAdhe] = vectVentasEmpresas[i]; // agregar al vector de eventas de empresas adheridas
            cout << "parte del vector ventas de empresas no adherida -> " << vectVentasEmpresas[i].codigo << " | dia -> " << vectVentasEmpresas[i].dia << endl;
            posNoAdhe++;
        }
        var = false;
    }

    dimAdhe = posAdhe;
    dimNoAdhe = posNoAdhe;
}

void menorImporteTotal(unsigned importTotal[], const int dimImporteTotal, int codigoEmpAdhe[], const int dimCodigoEmpAdhe)
{
    // enconetra cual es el menor importe total de las empresas adheridas
    unsigned menorImporte = importTotal[0];
    for (unsigned k = 0; k < dimImporteTotal; k++)
    {
        if (menorImporte > importTotal[k])
        {
            menorImporte = importTotal[k];
        }
    }

    for (unsigned i = 0; i < dimCodigoEmpAdhe; i++)
    {
        if (importTotal[i] == menorImporte)
        {
            cout << "La empresa que tubo el menor importe total es -> " << codigoEmpAdhe[i] << " , con el importe de -> " << menorImporte << endl;
        }
    }
}

void mayordiaventas(Venta vect[], int dim)
{
    int aux1 = 0, aux2 = 0, aux3 = 0, mayor = -1;
    int vecaux[3] = {0};

    for (int i = 0; i < dim; i++) // Recorro el vector con i=0 inicialmente, despues le sumo 3 y asi sucesivamente para la suma de todas las cant de ventas de todos los dias 1.
    {
        if (vect[i].dia == 0)
        {
            aux1 += vect[i].cantVentas;
        }
        else if (vect[i].dia == 1)
        {
            aux2 += vect[i].cantVentas;
        }
        else if (vect[i].dia == 2)
        {
            aux3 += vect[i].cantVentas;
        }
    }

    vecaux[0] = aux1;
    vecaux[1] = aux2;
    vecaux[2] = aux3;
    /*
        cout << "aux1: " << aux1 << endl;
        cout << "aux2: " << aux2 << endl;
        cout << "aux3: " << aux3 << endl; */

    for (int j = 0; j < 3; j++) // Recorro el vector para buscar el mayor de cant de ventas.
    {
        if (vecaux[j] > mayor)
            mayor = vecaux[j];
    }

    cout << "Dia/s con mas ventas:" << endl;
    for (int k = 0; k < 3; k++) // Se muestra los dias con mayor ventas.
    {
        if (mayor == vecaux[k])
            cout << "Dia -> " << k + 1 << " | Cantidad de ventas -> " << vecaux[k] << endl;
    }
}

void mostrandoTotalventas(Empresa vect[], int vectTotal[], const int dim, int vectTotalCantVentas[], int codigoEmpAdheridas[], const unsigned dimCodigoAdhe)
{

    for (unsigned i = 0; i < dim; i++)
    {
        for (unsigned j = 0; j < dimCodigoAdhe; j++)
        {
            if (vect[i].codigo == codigoEmpAdheridas[j])
            {
                cout << "Nombre de empresa -> " << vect[i].nombre << " | Total de ventas: " << vectTotalCantVentas[i] << " | Importe total -> " << vectTotal[i] << endl;
            }
        }
    }
}

void candtidadDeVentasDia(Venta vect[], Empresa vectTwo[], const int dim, int vectTotalImporte[], int vectTotalCantVentas[])
{
    unsigned j = 0;
    unsigned contDia = 0;
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
    fclose(lecturaArchBin);
    return cont;
}

void mostrandoVectorVentas(Venta vect[], const int dim)
{
    /* cout << "Cantidad de empresas cargadas: " << dim << endl; */
    for (int i = 0; i < dim; i++)
    {
        cout << "Codigo de empresa -> " << vect[i].codigo << " | Dia -> " << vect[i].dia + 1 << " | Cantidad de ventas: " << vect[i].cantVentas << " | Importe -> " << vect[i].importe << endl;
    }
}

void diassinventas(Venta ventas[], const int dimVentas)
{
    for (unsigned j = 0; j < dimVentas; j++)
    {
        if (ventas[j].cantVentas == 0)
        {
            cout << "Empresa: " << ventas[j].codigo << " | El dia: " << ventas[j].dia + 1 << " -> no tuvo ventas " << endl;
        }
    }
}
