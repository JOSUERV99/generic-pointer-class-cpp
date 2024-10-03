#include <iostream>
#include "MPointer.h"
#include "ListaDoblementeEnlazada.h"
#include <thread>
#include <chrono>

using namespace std;

void demoRecolectorBasura()
{
  MPointer<int> ptr1 = MPointer<int>::New();
  MPointer<int> ptr2 = MPointer<int>::New();
  MPointer<int> ptr3 = MPointer<int>::New();
  MPointer<int> ptr4 = MPointer<int>::New();

  *ptr1 = 10;
  *ptr2 = 20;
  ptr3 = 30;
  ptr4 = 40;

  cout << "MPointers creados inicialmente con valores:" << endl;
  cout << "Valor en ptr1: " << *ptr1 << endl;
  cout << "Valor en ptr2: " << *ptr2 << endl;
  cout << "Valor en ptr3: " << *ptr3 << endl;
  cout << "Valor en ptr4: " << *ptr4 << endl;

  this_thread::sleep_for(chrono::seconds(5));

  ptr1 = nullptr;
  ptr2 = nullptr;

  cout << "\nDespués de 5 segundos, ptr1 y ptr2 se establecen en nullptr:" << endl;
  cout << "Valor en ptr3: " << *ptr3 << endl;
  cout << "Valor en ptr4: " << *ptr4 << endl;

  this_thread::sleep_for(chrono::seconds(10));

  cout << "\nDespués de 10 segundos, el recolector de basura debería haber limpiado ptr1 y ptr2 si no existen otras referencias." << endl;
  cout << "Valor en ptr3: " << *ptr3 << endl;
  cout << "Valor en ptr4: " << *ptr4 << endl;

  ptr3 = nullptr;
  ptr4 = nullptr;

  delete MPointerGC::instancia;
}

void demoListaDobleEnlazada()
{
  ListaDoblementeEnlazada<int> lista;

  lista.agregarAlFinal(10);
  lista.agregarAlFinal(20);
  lista.agregarAlFinal(30);
  lista.agregarAlInicio(5);
  lista.agregarAlInicio(1);

  cout << "Lista en orden ascendente: ";
  lista.imprimirHaciaAdelante();

  lista.intercambiar(1, 0);
  cout << "Lista después del intercambio (index 1, index 0): ";
  lista.imprimirHaciaAdelante();

  lista.intercambiar(3, 2);
  cout << "Lista después del intercambio (index 3, index 2): ";
  lista.imprimirHaciaAdelante();
}

void demoOrdenamientoBurbuja()
{
  ListaDoblementeEnlazada<int> lista;
  lista.agregarAlFinal(10);
  lista.agregarAlFinal(5);
  lista.agregarAlFinal(20);
  lista.agregarAlFinal(15);

  cout << "Lista antes de ordenar (burbuja): ";
  lista.imprimirHaciaAdelante();

  lista.bubbleSort();

  cout << "Lista después de ordenar (burbuja): ";
  lista.imprimirHaciaAdelante();
}

void demoOrdenamientoInsercion()
{
  ListaDoblementeEnlazada<int> lista;
  lista.agregarAlFinal(8);
  lista.agregarAlFinal(3);
  lista.agregarAlFinal(12);
  lista.agregarAlFinal(6);

  cout << "Lista antes de ordenar (inserción): ";
  lista.imprimirHaciaAdelante();

  lista.insertionSort();

  cout << "Lista después de ordenar (inserción): ";
  lista.imprimirHaciaAdelante();
}

void demoOrdenamientoQuickSort()
{
  ListaDoblementeEnlazada<int> lista;
  lista.agregarAlFinal(25);
  lista.agregarAlFinal(10);
  lista.agregarAlFinal(30);
  lista.agregarAlFinal(5);

  cout << "Lista antes de ordenar (quicksort): ";
  lista.imprimirHaciaAdelante();

  lista.quickSort();

  cout << "Lista después de ordenar (quicksort): ";
  lista.imprimirHaciaAdelante();
}

int main()
{
  int opcion = 0;

  while (opcion != 6)
  {
    cout << "\n--- Menú de Demos ---" << endl;
    cout << "1. Demo Recolector de Basura" << endl;
    cout << "2. Demo Uso de Lista Doblemente Enlazada" << endl;
    cout << "3. Demo Ordenamiento Burbuja" << endl;
    cout << "4. Demo Ordenamiento Inserción" << endl;
    cout << "5. Demo Ordenamiento Quicksort" << endl;
    cout << "6. Salir" << endl;
    cout << "Seleccione una opción: ";
    cin >> opcion;

    switch (opcion)
    {
    case 1:
      demoRecolectorBasura();
      break;
    case 2:
      demoListaDobleEnlazada();
      break;
    case 3:
      demoOrdenamientoBurbuja();
      break;
    case 4:
      demoOrdenamientoInsercion();
      break;
    case 5:
      demoOrdenamientoQuickSort();
      break;
    case 6:
      cout << "Saliendo del programa..." << endl;
      break;
    default:
      cout << "Opción no válida. Intente de nuevo." << endl;
      return 0;
    }
    return 0;
  }

  return 0;
}
