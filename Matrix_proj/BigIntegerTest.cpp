/***
* Vik Dhillon
* vsdhillo
* 2025 Winter CSE101 PA6
* BigIntegerTest.cpp
* Test file for the BigInteger ADT
***/
#include "BigInteger.h"
using namespace std;

int main()
{
    BigInteger A = BigInteger("12543253");
    BigInteger B = BigInteger("45542353526");
    // cout << "A: " << A.to_string() << endl;
    // cout << "B: " << B.to_string() << endl;
    // cout << "A sign: " << A.sign() << endl;
    // cout << "B sign: " << B.sign() << endl;
    BigInteger C;
    // cout << "Compare: " << A.compare(B) << endl;
    // cout << "To string: " << A.to_string() << endl;
    cout << "A: " << A << endl;
    cout << "B: " << B << endl;
    
    C = A.mult(B);
    cout << "Added: " << C << endl;
    cout << "Sign: " << C.sign() << endl;
    return 0;
}