#pragma once
#include "LinkedList.hpp"
void test1() {
    std::cout << "test1";
    int* a = new int[4];
    for (int i = 0; i < 4; ++i) {
        a[i] = i;
    }
    LinkedList<int> list(a, 4);
    list.print();
    for (int i = 4; i < 7; ++i)
        list.push_back(i);
    list.print();
}

void test2() {
    std::cout << "test2\n";
    LinkedList<int> list;
    std::cout << "size " << list.size();
    list.push_back(5);
    list.print();
    std::cout << " head " << list.get_head() << " ";
    std::cout << "tail " << list.get_tail() << " ";
    std::cout << "size " << list.size();
    list.push_back(6);
    list.print();
    std::cout << " head " << list.get_head() << " ";
    std::cout << "tail " << list.get_tail() << " ";
    std::cout << "size " << list.size();
    list.push_back(8);
    list.print();
    std::cout << " head " << list.get_head() << " ";
    std::cout << "tail " << list.get_tail() << " ";
    std::cout << "size " << list.size();

}

void test3() {
    std::cout << "test3\n";
    LinkedList<int> list;
    list.insert(0,1);
    list.print();
    std::cout << " head " << list.get_head() << " ";
    std::cout << "tail " << list.get_tail() << " ";
    std::cout << "size " << list.size();
    list.insert(1, 0);
    list.print();
    std::cout << " head " << list.get_head() << " ";
    std::cout << "tail " << list.get_tail() << " ";
    std::cout << "size " << list.size();
    list.insert(0, 2);
    list.print();
    std::cout << " head " << list.get_head() << " ";
    std::cout << "tail " << list.get_tail() << " ";
    std::cout << "size " << list.size();
    list.insert(3, 4);
    list.print();
    std::cout << " head " << list.get_head() << " ";
    std::cout << "tail " << list.get_tail() << " ";
    std::cout << "size " << list.size();
    list.insert(3, 5);
    list.print();
    std::cout << " head " << list.get_head() << " ";
    std::cout << "tail " << list.get_tail() << " ";
    std::cout << "size " << list.size();
    list.insert(2, 6);
    list.print();
    std::cout << " head " << list.get_head() << " ";
    std::cout << "tail " << list.get_tail() << " ";
    std::cout << "size " << list.size();
    list.insert(5, 7);
    list.print();
    std::cout << " head " << list.get_head() << " ";
    std::cout << "tail " << list.get_tail() << " ";
    std::cout << "size " << list.size();
}

void test4() {
    std::cout << "test4";
    int* a = new int[10];
    for (int i = 0; i < 10; ++i) {
        a[i] = i;
    }
    LinkedList<int> list(a, 10);
    list.print();
    list.remove(9);
    list.print();
    list.remove(0);
    list.print();
    list.remove(1);
    list.print();
    list.remove(list.size()-2);
    list.print();
    list.remove(3);
    list.print();
    list.remove(3);
    list.print();
    list.remove(2);
    list.print();
    list.remove(2);
    list.print();
    list.remove(0);//list.remove(1);
    list.print();
    list.remove(0);
    list.print();
}

void test5() {
    std::cout << "test5  \n";
    int* a = new int[10];
    for (int i = 0; i < 10; ++i) {
        a[i] = i;
    }
   
    LinkedList<int> list(a, 10);
    const Element<int> k = list[0];
    for (int i = 0; i < 10; ++i) {
        std::cout << list[i];
        std::cout << '\n';
    }
    //list[5] = 3;
    //list[5] = 6; // this is not Exception!!! firstly, Element(6), thus diff = 0
                    //secondle list[5] = Element(6) and of course, our diff is bad
    std::cout << "\n\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << list[i];
        std::cout << '\n';
    }
    std::cout << list[5];
    //std::cout << list[5];
}

void test6() {
    std::cout << "test6 \n";
    int n = 8;//0 1 2 3 4 8+
    int* a = new int[n];
    for (int i = 0; i < n; ++i) {
        a[i] = i;
    }
    LinkedList<int> list(a, n);
    LinkedList<int> list2;
    list2 = list;
    list2.print();
}