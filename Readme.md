# UTN FRBA - ALGORITMOS Y ESTRUCTURA DE DATOS TRABAJO PRÁCTICO 1 2024 – K1201

## Integrantes

1. Facundo

2. Ezequiel 1 :)

3. Brisa

4. Kamila

5. Ezequiel 2

## Objectivos:

El **objetivo** de este **trabajo práctico** es poner en práctica el concepto de Estructuras de control de flujo de un programa (secuencia, análisis de caso y repetición), como asimismo trabajar con tipos de datos simples y estructurados (arrays), con expresiones lógicas, asignación interna y externa. También usaremos flujos conocidos como “Archivos” y patrones algorítmicos de ordenamiento

## Contexto y requerimientos:

Se requiere una aplicación para realizar registro y estadísticas sobre el último Hot Sale en el que participan, como máximo, **500 empresas adheridas**

![](C:\Users\Ezequiel\AppData\Roaming\marktext\images\2024-07-19-18-45-08-image.png)

El ingreso de datos finaliza como el equipo decida

También se ingresan datos correspondientes a las ventas realizadas durante **los 3 días del Hot Sale**

![](C:\Users\Ezequiel\AppData\Roaming\marktext\images\2024-07-19-18-45-47-image.png)

El ingreso de datos finaliza como el equipo decida

## Realizar un programa para:

- Informar por cada día de la promoción cantidad de ventas e importe total recaudado por cada empresa adherida  

- Informar por cada empresa adherida, si corresponde, los días en que no realizaron ventas.  

- Informar la o las empresas que recaudaron el menor importe total, informando también dicho importe  

- Informar cuál de los tres días hubo más ventas  

- Generar el archivo “ImporteEmpresas.dat”, con un registro por cada empresa adherida, ordenado por código de empresa. Cada registro deberá tener código y nombre de la empresa y el importe total recaudado por sus ventas y la cantidad de ellas. El archivo debe estar ordenado por código de empresa.  

- Generar el archivo “SinAdhesion.dat”, con las ventas ingresadas de empresas que no estuvieron adheridos a la promoción

## Condiciones de entregar TP:

- Se debe entregar un .rar o un .zip que debe llevar el siguiente nombre: K1201-XXXX-TP1 Donde XXXX será el nombre que los miembros del equipo le asignen al grupo.  

- El archivo: K1201-XXXX-TP1 (.rar o .zip) corresponderá a una carpeta con los siguientes archivos, cuyos nombres deben tener el mismo nombre de la carpeta:  
  
  - Carátula indicando los integrantes del grupo.  
  
  - Instructivo (.pdf)  
  
  - Código (.cpp)  
  
  - Archivos adicionales  

- El instructivo comprende:  
  
  - Un instructivo de uso para el programa junto con capturas del programa funcionando.  
  
  - La justificación de cualquier decisión tomada a la hora de resolver el problema.

## Fecha límite de entrega: 28 de julio

- link de figma: 
  https://www.figma.com/board/9BImnWGTEmOq7Fi49unmZF/UTN-FRBA---ALGORITMOS-Y-ESTRUCTURA-DE-DATOS-TRABAJO-PR%C3%81CTICO-1-2024-%E2%80%93-K1201?node-id=0-1&t=xKTiOoxYdVIhAeha-1

## Documentacion

### Struct

```cpp
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
    unsigned cantVentas;
};
```

### Punto 1

**Problemas:** Informar por cada día de la promoción cantidad de ventas e importe total recaudado por cada empresa adherida

#### Solucion

Se lee el archivo binario ya creado, se extra los datos necesarios,por medio de una funcion ,al vector con el typo de dato **Empresa** y retornar la dimencion que tendra ese mismo vector.

Se declaran 2 vectores **enteros(int)**  inicializados en 0 para podes tener los importes totales e ventas totales de las empresas adheridas.

Se declara un vector de typo de dato **venta** con la dimencion igual a la del vector empresas, solo que sera **triplicada** por el motivo de que cada empresa adherida tendra 3 dias del **HotSale**, por ende si solo se sumaran al **HotSale** 3 empresas entonces seria cada empresas con sus 3 dias -> 3 empresas x 3 dias del **HotSale** = 12 dimencion del vector de typo **Venta**

```cpp
Empresa vectDatosArch[dim /*-> 500*/];
    unsigned dimVect = extrayendoDatos(vectDatosArch) - 1;
    int vectTotalImporte[dimVect] = {0};
    int vectTotalCantVentas[dimVect] = {0};
    cout << "-------------------------------------------------------" << endl;
    /* Importe total por dia  */
    Venta vectVentasEmpresas[dimVect * 3];
```

Lugo de tener todo declarado, se hace una funcion **candtidadDeVentasDia** que usara los parametros del vector de typo **Venta** con su dimencion, vector de typo **Empresa**, vector para el total del importe y vector para el total de cantidad de ventas.

Estas funcion te permite cargar la cantidad de ventas e importe por dia por cada empresa sin retornar nada

```cpp
 candtidadDeVentasDia(vectVentasEmpresas, vectDatosArch, dimVect, vectTotalImporte, vectTotalCantVentas);
```

Se mostrara por pantalla por medio de la funcion **mostrandoVectorVentas** el vector de typo **Ventas** con su dimencion

```cpp
mostrandoVectorVentas(vectVentasEmpresas, dimVect * 3);
```

Al final se usara una funcion **mostrandoTotalVentas** que que mostrara el importe total y la cantidad de ventas de los 3 dias por cada empresa.

```cpp
 cout << "- Total de las empresas -" << endl;
 mostrandoTotalventas(vectDatosArch, vectTotalImporte, dimVect, vectTotalCantVentas);
```

### punto 3

**Problema:** Informar la o las empresas que recaudaron el menor importe total, informando también dicho importe

#### Solucion

Se hace una funcion **menorImporteTotal** que usara el vector **vectTotalImporte**, su dimencion(**dimVect**) y el vector de donde se extrayeron los datos de las empresas **vectDatosArch**  

```cpp
menorImporteTotal(vectTotalImporte, dimVect, vectDatosArch);
```

la funcion no retornara nada(**void**), su tarea es encontrar la empresa con el menor importe total y si existen + de 1 empresa que tiene el mismo importe total, cumpliendo la condicion de que su importe es el menor de todos, se tendran que mostrar por pantalla esas empresas junto con su importe
