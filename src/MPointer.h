#ifndef MPOINTER_H
#define MPOINTER_H

#include <iostream>
#include <stdexcept>

#include "MPointerGC.h"

template <typename T>
class MPointer
{
private:
    T *ptr;
    int id;

    explicit MPointer(T *p) : ptr(p), id(MPointerGC::getInstance().registrarPuntero(p)) {}

    explicit MPointer(std::nullptr_t) : ptr(nullptr), id(-1) {}

public:
    static MPointer<T> New()
    {
        return MPointer<T>(new T());
    }

    static MPointer<T> New(T valor)
    {
        MPointer<T> nuevoPuntero = MPointer<T>(new T());
        *nuevoPuntero.ptr = valor;
        return nuevoPuntero;
    }

    static MPointer<T> New(std::nullptr_t)
    {
        return MPointer<T>(nullptr);
    }

    static MPointer<T> New(MPointer<T> &otro)
    {
        return MPointer<T>(otro);
    }

    T &operator*()
    {
        return *ptr;
    }

    T *operator&()
    {
        return ptr;
    }

    T *operator->() const
    {
        return ptr;
    }

    operator bool() const
    {
        return ptr != nullptr;
    }

    MPointer &operator=(std::nullptr_t)
    {
        if (ptr)
        {
            MPointerGC::getInstance().decrementarContadorReferencias(id);
            ptr = nullptr;
        }
        return *this;
    }

    MPointer(const MPointer &otro) : ptr(new T(*otro.ptr)), id(otro.id)
    {
        MPointerGC::getInstance().incrementarContadorReferencias(id);
    }

    MPointer<T> &operator=(T valor)
    {
        *ptr = valor;
        return *this;
    }

    MPointer &operator=(const MPointer &otro)
    {
        if (this->id == -1 || !this->ptr)
        {
            ptr = otro.ptr;
            id = otro.id;
            return *this;
        }

        if (this != &otro)
        {
            if (ptr)
            {
                MPointerGC::getInstance().decrementarContadorReferencias(id);
            }

            ptr = otro.ptr;
            id = otro.id;
            MPointerGC::getInstance().incrementarContadorReferencias(id);
        }
        return *this;
    }

    int obtenerId() const
    {
        return id;
    }

    ~MPointer()
    {
        if (ptr)
        {
            MPointerGC::getInstance().decrementarContadorReferencias(id);
        }
    }
};

#endif
