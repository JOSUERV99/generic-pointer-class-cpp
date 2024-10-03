#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <map>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>

class MPointerGC
{
private:
    struct Nodo
    {
        int id;
        void *ptr;
        int contadorReferencias;
        Nodo *siguiente;

        Nodo(int id, void *ptr) : id(id), ptr(ptr), contadorReferencias(1), siguiente(nullptr) {}
    };

    Nodo *cabeza;

    int idActual;
    std::mutex mtx;
    std::thread hiloGC;
    bool detenerHilo;
    bool terminado = false;

    MPointerGC() : cabeza(nullptr), idActual(0), detenerHilo(false)
    {
        hiloGC = std::thread(&MPointerGC::bucleGC, this);
    }

    void limpiezaFinal()
    {
        std::lock_guard<std::mutex> bloqueo(mtx);

        int eliminados = 0;
        Nodo *actual = cabeza;
        while (actual)
        {
            Nodo *siguiente = actual->siguiente;
            delete actual->ptr;
            delete actual;
            actual = siguiente;
            eliminados++;
        }
        cabeza = nullptr;
        std::cout << "Eliminados: " << eliminados << std::endl;
    }

    void bucleGC()
    {
        while (!detenerHilo)
        {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            recolectarBasura();
        }
    }

    void recolectarBasura()
    {

        Nodo *actual = cabeza;
        Nodo *anterior = nullptr;

        int eliminados = 0;
        while (actual)
        {
            if (actual->contadorReferencias == 0)
            {
                // lo quita de la lista
                if (anterior)
                {
                    anterior->siguiente = actual->siguiente;
                }
                else
                {
                    cabeza = actual->siguiente;
                }
                delete actual->ptr; // lo borra de memoria
                eliminados++; // aumenta la cantidad de borrados
                Nodo *temp = actual;
                actual = actual->siguiente;
                delete temp; // borrar el espacio donde se encontraba
            }
            else
            {
                anterior = actual;
                actual = actual->siguiente;
            }
        }

        std::cout << "Basura recolectada: " << eliminados << std::endl;
    }

public:
    static MPointerGC *instancia; // singleton, solo existe una instancia del recolector de basura

    ~MPointerGC()
    {
        detenerHilo = true;
        if (hiloGC.joinable())
        {
            hiloGC.join();
        }
    }

    static MPointerGC &getInstance()
    {
        if (!instancia)
        {
            instancia = new MPointerGC();
        }
        return *instancia;
    }

    int registrarPuntero(void *ptr)
    {
        std::lock_guard<std::mutex> bloqueo(mtx);
        int id = idActual++;

        Nodo *nuevoNodo = new Nodo(id, ptr);
        nuevoNodo->siguiente = cabeza;
        cabeza = nuevoNodo;

        return id;
    }

    void incrementarContadorReferencias(int id)
    {
        std::lock_guard<std::mutex> bloqueo(mtx);

        Nodo *actual = cabeza;
        while (actual)
        {
            if (actual->id == id)
            {
                ++actual->contadorReferencias;
                return;
            }
            actual = actual->siguiente;
        }
    }

    void decrementarContadorReferencias(int id)
    {
        std::lock_guard<std::mutex> bloqueo(mtx);

        Nodo *actual = cabeza;
        while (actual)
        {
            if (actual->id == id)
            {
                --actual->contadorReferencias;
                return;
            }
            actual = actual->siguiente;
        }
    }
};

MPointerGC *MPointerGC::instancia = nullptr;

#endif
