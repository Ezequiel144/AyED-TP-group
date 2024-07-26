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
void ingresarVentas(Venta ventas[], unsigned &numVentas);
void generarArchivoSinAdhesion(const Empresa empresas[], unsigned numEmpresas, const Venta ventas[], unsigned numVentas);

int main()
{
    const int dim = 500;
    const int DIAS = 3;
    Empresa vectEmpresas[dim];
    Venta ventas[dim * DIAS];
    
    unsigned dimRealVect = cargandoDatos(vectEmpresas);
    unsigned numVentas = 0;

    cout << "-------------------------------------------------------" << endl;
    
    /* Mostrando las empresas ya cargadas en el vector */
    mostrandoVector(vectEmpresas, dimRealVect);

    /* Escribe un archivo binario */
    escribiendoArchivoDeEmpresas(vectEmpresas,dimRealVect);

    cout << "-------------------------------------------------------" << endl;
    
    /*Ingresa las ventas de las empresas indistintamente si es adherida o no*/
    ingresarVentas(ventas, numVentas);

    /* Generar archivo SinAdhesion.dat */
    generarArchivoSinAdhesion(vectEmpresas, dimRealVect, ventas, numVentas);
    
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

void ingresarVentas(Venta ventas[], unsigned &numVentas) 
{
    while (true) {
        Venta venta;
        cout << "Ingrese día de la venta (1, 2, o 3, 0 para finalizar): ";
        cin >> venta.dia;
        if (venta.dia == 0) break;
        cout << "Ingrese código de empresa: ";
        cin >> venta.codigo;
        cout << "Ingrese importe de la venta: ";
        cin >> venta.importe;
        ventas[numVentas++] = venta;
    }
}

void generarArchivoSinAdhesion(const Empresa empresas[], unsigned numEmpresas, const Venta ventas[], unsigned numVentas) 
{
    FILE *archivo = fopen("SinAdhesion.dat", "wb");
    if (!archivo) {
        cerr << "Error al abrir el archivo SinAdhesion.dat." << endl;
        return;
    }

    for (unsigned i = 0; i < numVentas; i++) {
        bool adherida = false;
        
        for (unsigned j = 0; j < numEmpresas; j++) {
            if (ventas[i].codigo == empresas[j].codigo) {
                adherida = true;
                break;
            }
        }
        
        if (!adherida) {
            fwrite(&ventas[i], sizeof(Venta), 1, archivo);
        }
    }

    fclose(archivo);
    cout << "Archivo SinAdhesion.dat generado exitosamente." << endl;
}