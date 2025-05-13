/***
* Vik Dhillon
* vsdhillo
* 2025 Winter CSE101 PA6
* Arithmetic.cpp
* Client function for BigInteger
***/
#include "List.h"
#include "BigInteger.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char*argv[]) {
    if (argc != 3)
    {
        fprintf(stderr, "You must specify exactly 2 command line arguments!\n");
        return EXIT_FAILURE;
    }

    std::ifstream file(argv[1]);
    std::ofstream out(argv[2]);
    
    std::string l;
    std::getline(file, l);
    BigInteger A(l);
    std::getline(file, l);
    std::getline(file, l);
    BigInteger B(l);
    out << A << endl;
    out << endl;
    out << B << endl;
    out << endl;
    out << A.add(B) << endl;
    out << endl;
    out << A.sub(B) << endl;
    out << endl;
    out << A.sub(A) << endl;
    out << endl;

    BigInteger C("3");
    BigInteger D("2");
    out << (A.mult(C)).sub((B.mult(D))) << endl;
    out << endl;

    out << A.mult(B) << endl;
    out << endl;
    out << A.mult(A) << endl;
    out << endl;
    out << B.mult(B) << endl;
    out << endl;
    BigInteger E("9");
    BigInteger F("16");

    BigInteger Asq = A.mult(A);
    BigInteger Asq4 = Asq.mult(Asq);

    BigInteger Bsq = B.mult(B);
    BigInteger Bsq4 = Bsq.mult(Bsq);
    BigInteger Bsq5 = Bsq4.mult(B);
    out << (Asq4.mult(E)).add(Bsq5.mult(F)) << endl;
    file.close();
    out.close();
    return 0;
}