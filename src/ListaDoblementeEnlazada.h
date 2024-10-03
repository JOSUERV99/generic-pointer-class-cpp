#include "Node.h"
#include "MPointer.h"
#include <iostream>

template <typename T>
class ListaDoblementeEnlazada
{
private:
    MPointer<Node<T>> cabeza = MPointer<Node<T>>::New(nullptr);
    MPointer<Node<T>> cola = MPointer<Node<T>>::New(nullptr);
    int tamaño = 0;

public:
    ListaDoblementeEnlazada()
    {
    }

    ~ListaDoblementeEnlazada()
    {
    }

    int obtenerTamaño()
    {
        return tamaño;
    }

    void agregarAlInicio(T valor)
    {
        MPointer<Node<T>> nuevoNodo = MPointer<Node<T>>::New(valor);
        if (!cabeza)
        {
            cabeza = nuevoNodo;
            cola = nuevoNodo;
        }
        else
        {
            nuevoNodo->establecerSiguiente(cabeza);
            cabeza->establecerAnterior(nuevoNodo);
            cabeza = nuevoNodo;
        }
        tamaño++;
    }

    void agregarAlFinal(T valor)
    {
        MPointer<Node<T>> nuevoNodo = MPointer<Node<T>>::New(valor);
        if (!cola)
        {
            cabeza = nuevoNodo;
            cola = nuevoNodo;
        }
        else
        {
            nuevoNodo->establecerAnterior(cola);
            cola->establecerSiguiente(nuevoNodo);
            cola = nuevoNodo;
        }
        tamaño++;
    }

    void eliminarEnCabeza()
    {
        if (!cabeza)
            return;
        MPointer<Node<T>> temporal = cabeza;
        cabeza = cabeza->siguiente;
        MPointer<Node<T>> nulo = MPointer<Node<T>>::New(nullptr);
        if (cabeza)
        {
            cabeza->establecerAnterior(nulo);
        }
        else
        {
            cola = nulo;
        }
        tamaño--;
    }

    MPointer<Node<T>> obtenerNodoEnIndice(int indice)
    {
        MPointer<Node<T>> actual = MPointer<Node<T>>::New(nullptr);
        actual = cabeza;
        int indiceActual = 0;
        while (actual && indiceActual < indice)
        {
            actual = actual->obtenerSiguiente();
            indiceActual++;
        }
        return actual;
    }

    void intercambiar(int indice1, int indice2)
    {
        if (indice1 == indice2)
            return;

        MPointer<Node<T>> nodo1 = obtenerNodoEnIndice(indice1);
        MPointer<Node<T>> nodo2 = obtenerNodoEnIndice(indice2);

        if (nodo1 && nodo2)
        {
            T valorTemporal = nodo1->obtenerValor();
            T valorTemporal2 = nodo2->obtenerValor();
            nodo1->establecerValor(valorTemporal2);
            nodo2->establecerValor(valorTemporal);
        }
    }

    void imprimirHaciaAdelante()
    {
        MPointer<Node<T>> actual = MPointer<Node<T>>::New(nullptr);
        actual = cabeza;
        while (actual)
        {
            std::cout << actual->obtenerValor() << " ";
            actual = actual->obtenerSiguiente();
        }
        std::cout << std::endl;
    }

    void imprimirHaciaAtrás()
    {
        MPointer<Node<T>> actual = MPointer<Node<T>>::New(nullptr);
        actual = cola;
        while (actual)
        {
            std::cout << actual->obtenerValor() << " ";
            actual = actual->obtenerAnterior();
        }
        std::cout << std::endl;
    }

    void bubbleSort()
    {
        if (!cabeza)
            return;

        bool intercambiado = false;
        MPointer<Node<T>> actual = MPointer<Node<T>>::New(nullptr);

        do
        {
            intercambiado = false;
            actual = cabeza;

            while (actual->obtenerSiguiente())
            {
                if (actual->obtenerValor() > actual->obtenerSiguiente()->obtenerValor())
                {

                    T temp = actual->obtenerValor();
                    actual->establecerValor(actual->obtenerSiguiente()->obtenerValor());
                    actual->obtenerSiguiente()->establecerValor(temp);

                    intercambiado = true;
                }
                actual = actual->obtenerSiguiente();
            }
        } while (intercambiado);
    }

    void insertionSort()
    {
        if (!cabeza)
            return;

        MPointer<Node<T>> ordenado = MPointer<Node<T>>::New(nullptr);
        MPointer<Node<T>> actual = MPointer<Node<T>>::New(nullptr);

        ordenado = cabeza;
        actual = cabeza->obtenerSiguiente();

        while (actual)
        {
            T clave = actual->obtenerValor();
            MPointer<Node<T>> anterior = MPointer<Node<T>>::New(nullptr);
            anterior = actual->obtenerAnterior();

            while (anterior && anterior->obtenerValor() > clave)
            {
                anterior->obtenerSiguiente()->establecerValor(anterior->obtenerValor());
                anterior = anterior->obtenerAnterior();
            }

            if (anterior)
            {
                anterior->obtenerSiguiente()->establecerValor(clave);
            }
            else
            {
                cabeza->establecerValor(clave);
            }

            actual = actual->obtenerSiguiente();
        }
    }

    MPointer<Node<T>> particionar(int bajo, int alto)
    {
        MPointer<Node<T>> altoNode = MPointer<Node<T>>::New(nullptr);
        altoNode = obtenerNodoEnIndice(alto);
        T pivote = altoNode->obtenerValor();

        int i = bajo - 1;

        for (int j = bajo; j < alto; j++)
        {
            MPointer<Node<T>> jNode = MPointer<Node<T>>::New(nullptr);
            jNode = obtenerNodoEnIndice(j);

            if (jNode->obtenerValor() <= pivote)
            {
                i++;
                MPointer<Node<T>> iNode = MPointer<Node<T>>::New(nullptr);
                iNode = obtenerNodoEnIndice(i);

                T temp = iNode->obtenerValor();
                iNode->establecerValor(jNode->obtenerValor());
                jNode->establecerValor(temp);
            }
        }

        i++;
        MPointer<Node<T>> iNode = MPointer<Node<T>>::New(nullptr);
        iNode = obtenerNodoEnIndice(i);

        T temp = iNode->obtenerValor();
        iNode->establecerValor(altoNode->obtenerValor());
        altoNode->establecerValor(temp);

        return iNode;
    }

    void ordenamientoRapidoRecursivo(int bajo, int alto)
    {
        if (bajo < alto)
        {
            MPointer<Node<T>> p = MPointer<Node<T>>::New(nullptr);
            p = particionar(bajo, alto);

            int pIndex = bajo;
            while (obtenerNodoEnIndice(pIndex) != p)
            {
                pIndex++;
            }

            ordenamientoRapidoRecursivo(bajo, pIndex - 1);
            ordenamientoRapidoRecursivo(pIndex + 1, alto);
        }
    }

    void quickSort()
    {
        int listSize = obtenerTamaño();
        if (listSize > 1)
        {
            ordenamientoRapidoRecursivo(0, listSize - 1);
        }
    }
};
