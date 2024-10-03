#include <gtest/gtest.h>
#include "MPointer.h"
#include "ListaDoblementeEnlazada.h"

class MPointerTest : public testing::Test
{
};

class ListaDoblementeEnlazadaTest : public testing::Test
{
};

TEST(MPointerTest, AsignacionBasica)
{
    MPointer<int> puntero = MPointer<int>::New();
    *puntero = 10;
    ASSERT_EQ(*puntero, 10);
}

TEST(ListaDoblementeEnlazadaTest, ProbarTamanio)
{
    ListaDoblementeEnlazada<int> lista;
    lista.agregarAlFinal(1);
    lista.agregarAlFinal(2);
    lista.agregarAlFinal(3);
    ASSERT_EQ(lista.obtenerTamaño(), 3);
}

TEST(ListaDoblementeEnlazadaTest, BubbleSort)
{
    ListaDoblementeEnlazada<int> lista;
    lista.agregarAlFinal(3);
    lista.agregarAlFinal(1);
    lista.agregarAlFinal(2);
    lista.bubbleSort();
    ASSERT_EQ(lista.obtenerNodoEnIndice(0)->obtenerValor(), 1);
    ASSERT_EQ(lista.obtenerNodoEnIndice(1)->obtenerValor(), 2);
    ASSERT_EQ(lista.obtenerNodoEnIndice(2)->obtenerValor(), 3);
}

TEST(ListaDoblementeEnlazadaTest, QuickSort)
{
    ListaDoblementeEnlazada<int> lista;
    lista.agregarAlFinal(3);
    lista.agregarAlFinal(1);
    lista.agregarAlFinal(2);
    lista.quickSort();
    ASSERT_EQ(lista.obtenerNodoEnIndice(0)->obtenerValor(), 1);
    ASSERT_EQ(lista.obtenerNodoEnIndice(1)->obtenerValor(), 2);
    ASSERT_EQ(lista.obtenerNodoEnIndice(2)->obtenerValor(), 3);
}

TEST(ListaDoblementeEnlazadaTest, InsertionSort)
{
    ListaDoblementeEnlazada<int> lista;
    lista.agregarAlFinal(3);
    lista.agregarAlFinal(1);
    lista.agregarAlFinal(2);
    lista.insertionSort();
    ASSERT_EQ(lista.obtenerNodoEnIndice(0)->obtenerValor(), 1);
    ASSERT_EQ(lista.obtenerNodoEnIndice(1)->obtenerValor(), 2);
    ASSERT_EQ(lista.obtenerNodoEnIndice(2)->obtenerValor(), 3);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}