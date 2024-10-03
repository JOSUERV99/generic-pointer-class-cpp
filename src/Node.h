#include "MPointer.h"

template <typename T>
class Node {
public:
    T* dato;
    MPointer<Node<T>> siguiente = MPointer<Node<T>>::New(nullptr);
    MPointer<Node<T>> anterior = MPointer<Node<T>>::New(nullptr);

    Node() {
        dato = nullptr;
    }

    Node(T valor) {
        dato = new T(); *dato = valor;
    }

    T obtenerValor() {
        return *dato;
    }

    MPointer<Node<T>>& obtenerSiguiente() {
        return siguiente;
    }

    MPointer<Node<T>>& obtenerAnterior() {
        return anterior;
    }

    void establecerValor(T _dato) {
        *dato = _dato;
    }

    void establecerSiguiente(MPointer<Node<T>>& _siguiente) {
        siguiente = _siguiente;
    }

    void establecerAnterior(MPointer<Node<T>>& _anterior) {
        anterior = _anterior;
    }
};
