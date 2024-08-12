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
void escribiendoArchivoDeEmpresas(Empresa vect[], const int dim);
unsigned extrayendoDatos(Empresa[], int[], unsigned &);
void mostrandoVectorVentas(Venta[], const int);
void candtidadDeVentasDia(Venta[], Empresa[], const int, int[], int[]);
void mostrandoTotalventas(Empresa[], int[], const int, int[], int[], const unsigned);
void menorImporteTotal(unsigned[], const int, int[], const int);
void diassinventas(Venta[], const int);
void separandoEmpAdheridas(Venta[], Venta[], Venta[], int[], const int, const int, int &, int &);
void mayordiaventas(Venta[], int);
unsigned totalEmpresasAdhe(unsigned[], const int, Venta[], unsigned[]);
void ordenamientoEmpresa(Empresa[], const int, unsigned[]);
void cargarArchivo(Empresa[], unsigned[], unsigned[], const int, int[], const int, unsigned[]);
void generarArchivoSinAdhesion(Venta [], const int);

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

    /*punto-1 Informar por cada día de la promoción cantidad de ventas e importe total recaudado por cada empresa adheridas */
    cout << "-------------------------------------------------------" << endl;
    cout << "- Total de las empresas Adheridas -" << endl;
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
    // encontra cual es el menor importe total de las empresas adheridas

    menorImporteTotal(vectTotalImportePrueba, dimTotalImporte, codigoEmpAdheridas, dimCodigoAdhe);

    /*Punto-4*/
    cout << "---------------------------------------------------------" << endl;
    mayordiaventas(vectVtasEmpAdhe, dimVtaAdhe);
    /*Punto-5*/
    cout << "---------------------------------------------------------" << endl;
    unsigned posOrdenamiento[dimVect] = {0};
    ordenamientoEmpresa(vectDatosArch, dimVect, posOrdenamiento);
    cargarArchivo(vectDatosArch, vectTotalImportePrueba, vectTotalCantVtaPrueba, dimVect, codigoEmpAdheridas, dimCodigoAdhe, posOrdenamiento);
    /*Punto-6*/
    generarArchivoSinAdhesion(vectVtasEmpNoAdhe, dimVtaNoAdhe);

    return 0;
}

/* funciones punto-1 */
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
/* ----- */
/* funciones punto-2 */
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
/* funciones punto-3 */
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
            cout << "La empresa que tuvo el menor importe total es -> " << codigoEmpAdhe[i] << " , con el importe de -> " << menorImporte << endl;
        }
    }
}
/* ----- */
/* funciones punto-4 */
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
/* ----- */
/* funciones punto-5 */
void ordenamientoEmpresa(Empresa vectEmpAdhe[], const int dimEmpAdhe, unsigned posOrdenamiento[]) // Función para ordenar las empresas por su código indentificador.
{
    Empresa temp;
    unsigned aux;
    unsigned auxPosicionOrd[dimEmpAdhe] = {0};

    for (int k = 0; k < dimEmpAdhe; k++)
    {
        auxPosicionOrd[k] = k;
    }

    for (int i = 0; i < dimEmpAdhe - 1; i++)
    {
        for (int j = 0; j < dimEmpAdhe - 1 - i; j++)
        {
            if (vectEmpAdhe[j].codigo > vectEmpAdhe[j + 1].codigo)
            {
                temp = vectEmpAdhe[j];
                vectEmpAdhe[j] = vectEmpAdhe[j + 1];
                vectEmpAdhe[j + 1] = temp;

                aux = auxPosicionOrd[j];
                auxPosicionOrd[j] = auxPosicionOrd[j + 1];
                auxPosicionOrd[j + 1] = aux;
            }
        }
    }
    posOrdenamiento = auxPosicionOrd;
}
void cargarArchivo(Empresa vectEmp[], unsigned importeTotal[], unsigned cantVtasTotal[], const int dimEmp, int codigoEmpAdheridas[], const int dimCodigoEmpAdhe, unsigned posOrdenamiento[]) // Crea archivo, y utiliza la función mostrarStruct() para imprimir la info de las empresas ordenadas.
{
    FILE *archivo = fopen("ImporteEmpresas.dat", "wb"); // Abre archivo binario.

    if (!archivo) // Si no lo puede abrir, devuelve error.
    {
        cout << "Error al intentar abrir el archivo"; // error archivo no encontrado...
        return;
    }
    int posImporteCantVts = 0;
    for (int i = 0; i < dimEmp; i++)
    {
        for (int j = 0; j < dimCodigoEmpAdhe; j++)
        {
            if (vectEmp[i].codigo == codigoEmpAdheridas[j])
            {
                fwrite(&vectEmp[i].codigo, sizeof(unsigned), 1, archivo);
                fwrite(&vectEmp[i].nombre, sizeof(char[30]), 1, archivo);
                fwrite(&cantVtasTotal[/* posImporteCantVts */ posOrdenamiento[i]], sizeof(unsigned), 1, archivo);
                fwrite(&importeTotal[/* posImporteCantVts */ posOrdenamiento[i]], sizeof(unsigned), 1, archivo);
                posImporteCantVts++;
            }
        }
    }
    fclose(archivo);
}
/* ----- */
/* funciones punto-6 */
void generarArchivoSinAdhesion(Venta vectVentas[], const int dimVtas)
{
    FILE *archivo = fopen("SinAdhesion.dat", "wb");
    if (!archivo)
    {
        cout << "Error al abrir el archivo SinAdhesion.dat" << endl;
        return;
    }

    for (int i = 0; i < dimVtas; i++)
    {
        fwrite(&vectVentas[i], sizeof(Venta), 1, archivo);
    }
    fclose(archivo);
    cout << "Archivo SinAdhesion.dat generado exitosamente." << endl;
}
/* ----- */

/* Extraccion, muestras y separacion de datos iniciales*/
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
    FILE *lecturaArchBin = fopen("/datos-de-empresas.dat", "rb");
    int cont = 0;
    unsigned i = 0;
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
    for (int i = 0; i < dim; i++)
    {
        cout << "Codigo de empresa -> " << vect[i].codigo << " | Dia -> " << vect[i].dia + 1 << " | Cantidad de ventas: " << vect[i].cantVentas << " | Importe -> " << vect[i].importe << endl;
    }
}
