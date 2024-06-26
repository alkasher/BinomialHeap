// binomial_heap.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "binomial_heap.hpp"
#include <iostream>

int main()
{
    BinomialHeap<int> heap(2);
    /*
    for (int i = 1; i < 100000; ++i) {
        heap.Insert(i);
        if (i % 1000 == 0) std::cout << i << " ";
    }
    */
    
    heap.Insert(11);
    heap.Insert(1);
    heap.Insert(3);
    heap.Insert(0);
    heap.Insert(6);
    heap.Insert(11);
    heap.Insert(12);
    heap.extractMin();
}

