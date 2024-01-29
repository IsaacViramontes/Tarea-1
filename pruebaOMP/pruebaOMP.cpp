#include <iostream>
#include <omp.h>

//N es la cantidad de elementos a manejar en los arreglos
#define N 2000

//chunk es el tamaño que tendran los pedazos de los arreglos para que cada hilo creado se encargue de esta cantidad de elementos
#define chunk 500

//mostrar permite manejar la cantidad de datos a imprimir
#define mostrar 10

//Se declara prototipo de funcion para imprimir los arreglos
void imprimeArreglo(float* d);

int main()
{
    std::cout << "Sumando arreglos en paralelo!\n";
    std::cout << "Cantidad de valores por arreglo: " << N << std::endl;
    std::cout << "Cantidad de valores por hilo: " << chunk << std::endl;
    std::cout << "Sumando arreglos en paralelo: " << mostrar << std::endl;

    //se declaran 3 arreglos: a, b y c, todos de tamaño N declarado anteriormente.
    //a y b seran arreglos con valores aleatorios
    //c va a representar la suma de los primeros dos arreglos
    float a[N], b[N], c[N];
    int i;
    for (i = 0; i < N; i++)
    {
        //Se asignan los valores de arreglo a de la siguiente manera:
        a[i] = i * 9;

        //Se asignan los valores de arreglo b de la siguiente manera: 
        b[i] = (i + 5) / 1.3;
    }

    int pedazos = chunk;

    #pragma omp parallel for \
    shared(a,b,c,pedazos) private(i) \
    schedule(static, pedazos) 

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];
    
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);
}

void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar; x++)
        std::cout << d[x] << " - ";

    std::cout << std::endl;
}