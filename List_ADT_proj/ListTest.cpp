/***
* Vik Dhillon
* vsdhillo
* 2025 Winter CSE101 PA5
* ListTest.cpp
* Program to test the List ADT
***/
#include <iostream>
#include "List.h"
using namespace std;

int main() {
    //List L;
    // std::cout << "Before clear, List length: " << L.length() << std::endl;
    // //std::cout << "Before clear, List Back: " << L.back() << std::endl;
    // std::string r = L.to_string();
    // std::cout << r << std::endl;
    // L.eraseAfter();
    // L.insertAfter(5);
    // L.insertAfter(7);
    // L.insertAfter(3);
    // L.eraseAfter();
    // L.eraseAfter();
    // L.insertBefore(10);
    // //L.eraseBefore();
    // std::string s = L.to_string();
    // std::cout << s << std::endl;
    // std::cout << "After insert, List length: " << L.length() << std::endl;
    // std::cout << "Peek Next: " << L.peekNext() << std::endl;
    // std::cout << "Peek Prev: " << L.peekPrev() << std::endl;
//    L.insertBefore(1);
//    L.insertBefore(2);
//    L.insertBefore(3);
//    L.insertBefore(5);
//    L.insertBefore(12);
//    L.insertBefore(12);
//    std::string a = L.to_string();
//    std::cout << a << std::endl;
//    L.cleanup();
//    std::string r = L.to_string();
//    std::cout << r << std::endl;
//    L.movePrev();
//    L.eraseAfter();
//    std::cout << "After insert, List length: " << L.length() << std::endl;
//    L.findPrev(2);
//    L.eraseAfter();
//    std::cout << "After insert again, List length: " << L.length() << std::endl;
List A;
List B;
// A.insertAfter(1);
// A.insertAfter(2);
// A.insertAfter(3);
// A.insertAfter(1);
// A.insertAfter(2);
// A.insertAfter(1);
// A.cleanup();
A.insertAfter(2);
A.insertAfter(1);
B = A;
cout << "A: " << A.to_string() << endl;
cout << "B: " << B.to_string() << endl;

// A.insertAfter(3215);
// A.insertAfter(176);
// A.insertAfter(22);
// A.insertAfter(5);
// A.insertAfter(1);
// A.moveNext();
// A.moveNext();
// cout << A.to_string();

// A.eraseBefore();
// A.eraseBefore();
// A.moveNext();
// A.moveNext();
// A.moveNext();

// A.moveFront();
// A.moveNext();
// A.insertAfter(77);
// A.insertAfter(55);
// A.insertAfter(1);
// A.insertAfter(34);
// A.insertAfter(1);
// A.insertAfter(77);
// A.insertAfter(77);
// A.insertAfter(34);
// cout << "Rayhan:" << A.findNext(99) << endl;
// cout << "Rayhan pos:" << A.position() << endl;
return 0;


}