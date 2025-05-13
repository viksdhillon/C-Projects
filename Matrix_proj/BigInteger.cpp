
/***
 * Vik Dhillon
 * vsdhillo
 * 2025 Winter CSE101 PA6
 * BigInteger.cpp
 * Program to write the BigInteger ADT
 ***/

#include <iostream>
#include <string>
#include <stdexcept>
#include "BigInteger.h"

const int power = 9;
const long base = 1000000000;

BigInteger::BigInteger()
{
    signum = 0;
    digits = List();
}

BigInteger::BigInteger(long x)
{
    if (x == 0)
    {
        signum = 0;
        digits = List();
    }
    else
    {
        if (x > 0)
        {
            signum = 1;
        }
        else
        {
            signum = -1;
        }
        long abs = std::abs(x);
        while (abs > 0)
        {
            if (signum == -1)
            {
                digits.insertAfter(-1 * (abs % base));
            }
            else
            {
                digits.insertAfter(abs % base);
            }
            abs /= base;
        }
    }
    //std::cout << digits << std::endl;
}

BigInteger::BigInteger(std::string s)
{
    if (s.length() <= 0)
    {
        throw std::length_error("BigInteger: BigInteger(std::string s): empty string");
    }
    int start = 0;
    int s_len;
    std::string result = "";
    digits.moveFront();
    if (s[0] == '-')
    {
        signum = -1;
        //s_len = s.substr(1).length();
        start = 1;
        //std::cout << "S: " << s << std::endl;
    }
    else if (s[0] == '+') {
        signum = 1;
        start = 1;
    }
    else
    {
        signum = 1;
        s_len = s.length();
    }
    while (start < s_len && s[start] == '0') {
        start++;

    }
    s = s.substr(start);
    s_len = s.length();
    int len = s.length() % power;
    //std::cout << "Print: " << len << std::endl;
    int count = 0;
    bool isZero = true;

    for (int i = 0; i < s_len; i++)
    {
        if ((count % power == 0 && count != 0) || (i == len && len != 0))
        {
            if (stol(result) != 0)
            {
                isZero = false;
            }
            digits.insertAfter(std::stol(result));
            digits.moveNext();
            result = "";
            count = 0;
        }
        count++;
        result += s[i];
        //std::cout << "reslt in func: " << result << std::endl;
    }
    //std::cout << "Result: " << std::stol(result) << std::endl;
    digits.insertAfter(stol(result));
    if (stol(result) != 0)
    {
        isZero = false;
    }
    digits.moveFront();
    if (isZero)
    {
        signum = 0;
    }
    // std:: cout << digits.to_string() << std::endl;
    // std:: cout << signum << std::endl;
}

BigInteger::BigInteger(const BigInteger &N)
{
    signum = N.signum;
    digits = List(N.digits);
}

int BigInteger::sign() const
{
    return signum;
}

int BigInteger::compare(const BigInteger &N) const
{
    if (signum > N.signum)
    {
        //std::cout << "fanum" << std::endl;
        return 1;
    }
    if (N.signum > signum)
    {
        return -1;
    }
    if (N.signum == 0 && signum == 0)
    {
        return 0;
    }

    if (digits.length() > N.digits.length())
    {
        return 1;
    }
    if (digits.length() < N.digits.length())
    {
        return -1;
    }

    List A = digits;
    List B = N.digits;
    A.moveFront();
    B.moveFront();
    long x;
    long y;
    while (A.position() < A.length())
    {
        x = A.moveNext();
        y = B.moveNext();
        if (x > y)
        {
            return 1;
        }
        else if (y > x)
        {
            return -1;
        }
        else
        {
            continue;
        }
    }
    return 0;
}

void BigInteger::makeZero()
{
    digits.clear();
    signum = 0;
}

void BigInteger::negate()
{
    if (signum == 0)
    {
        return;
    }
    else if (signum == 1)
    {
        signum = -1;
    }
    else
    {
        signum = 1;
    }
}
// std::string BigInteger::to_string()
// {
//    if (signum == 0)
//     {
//         return "0";
//     }
//     List A = digits;
//     std::string result = "";
//     std::string temp;
//     std::string append;  // Declare append without initialization
//     if (signum == -1)
//     {
//         result += "-";
//     }
    
//     A.moveFront();
//     while (A.position() < A.length())
//     {
//         temp = std::to_string(A.moveNext());
//         append = "";  // Reset append at the start of each loop iteration

//         if (temp.length() < power)
//         {
//             int add = power - temp.length();
//             for (int i = 0; i < add; i++)
//             {
//                 append += "0";
//             }
//             append += temp;
//             temp = append;
//         }
//         result += temp;
//     }
//     return result;
// }
std::string BigInteger::to_string() {
    if (signum == 0) {
        return "0";
    }

    List A = digits;
    std::string result = "";
    std::string temp;
    
    if (signum == -1) {
        result += "-";
    }

    A.moveFront();
    
    // Print first digit without leading zeros
    if (A.position() < A.length()) {
        result += std::to_string(A.moveNext()); // First number prints normally
    }

    // Print remaining digits, zero-padded to `power`
    while (A.position() < A.length()) {
        temp = std::to_string(A.moveNext());
        while (temp.length() < power) {  // Pad with leading zeros if needed
            temp = "0" + temp;
        }
        result += temp;
    }

    return result;
}

// HELPERS
void negateList(List &L)
{
    L.moveFront();
    while (L.position() < L.length())
    {
        L.setBefore(-1 * L.moveNext());
    }
}

void sumList(List &S, List A, List B, int sgn)
{

    S.clear();
    //S.moveFront();
    A.moveBack();
    B.moveBack();
    long y;
    //int x;
    long z;
    long a;
    long b;
    std::cout << "B to string: " << B.to_string() << std::endl;
    while ((A.position() > 0) && (B.position() > 0))
    {
        //std::cout << "A to string: " << A.to_string() << std::endl;
        //std::cout << "SIGN IN SUM: " << sgn << std::endl;
        a = A.movePrev();
        b = B.movePrev();
        //std::cout << "A in while: " << a << std::endl;
        //std::cout << "B in while: " << b << std::endl;
        y = a + (sgn * b);

        //std::cout << "HERE 1: " << y << std::endl;
        S.insertAfter(y);
        //S.movePrev();
    }

    while (A.position() > 0)
    {
        //std::cout << "A to string fsad: " << A.peekPrev() << std::endl;
        //x = A.movePrev();
        //std::cout << "CRASH OUT 2: " << x << std::endl;
        S.insertAfter(A.movePrev());
        //S.movePrev();
    }

    while (B.position() > 0)
    {
        z = (sgn * B.movePrev());
        //std::cout << "HERE 3: " << z << std::endl;
        S.insertAfter(z);
        //S.movePrev();
    }
}

int normalizeList(List &L)
{
    //std::cout << "After normalization: ";
    // L.moveFront();
    // while (L.position() < L.length()) {
    //     std::cout << L.moveNext() << " ";
    // }
    // std::cout << std::endl;
    L.moveBack();
    long x;
    int sign = 1;
    long carry = 0;
    while (L.position() > 0)
    {
        x = L.movePrev();
        x += carry;
        //std::cout << "X first: " << x << std::endl;
        if (x >= base)
        {
            //std::cout << "ooofh" << std::endl;
            carry = x / base;
            //std::cout << "CARRY:" << carry << std::endl;
            x = x % base;
        }
        else if (x < 0 && L.position() > 0)
        {
            carry = -1;
            x += base;
        }
        else
        {
            carry = 0;
        }
        //std::cout << "X: " << x << std::endl;
        L.setAfter(x);
    }

    if (carry > 0)
    {
        L.moveFront();
        L.insertAfter(carry);
    }

    while (L.length() > 1 && L.front() == 0)
    {
        L.moveFront();
        L.eraseAfter();
    }

    L.moveFront();
    if (L.length() > 0 && L.front() < 0)
    {
        //std::cout << "YO YO" << std::endl;
        //std::cout << "fdaslkjf" << std::endl;
        negateList(L);
        normalizeList(L);
        return -1;
    }

    if ((L.length() == 0) || (L.front() == 0 && L.length() == 1))
    {
        return 0;
    }
    //std::cout << "L string: " << L << std::endl;
    //std::cout << "CRASH OUT 4: " << sign << std::endl;
    return sign;
}

void shiftList(List &L, int p)
{
    L.moveBack();
    for (int i = 0; i < p; i++)
    {
        L.insertAfter(0);
    }
}

void scalarMultList(List &L, ListElement m)
{
    //std::cout << "MULT M: " << m << std::endl;
    L.moveFront();
    int x = 0;
    while (L.position() < L.length())
    {
        x = L.moveNext();
        L.setBefore(x * m);
    }
}

BigInteger BigInteger::add(const BigInteger &N) const
{
    BigInteger sum;
    int sign;
    // int s;
    if (N.signum == 0)
    {
        return *this;
    }
    if (signum == 0)
    {
        return N;
    }

    if (N.signum == signum)
    {
        sign = 1;
        sum.signum = 1;
        sumList(sum.digits, digits, N.digits, sign);
    } 
    else
    {
        if (signum > N.signum)
        {
            BigInteger copy(N);
            copy.signum = 1;
            if ((*this).compare(copy) == 1)
            {
                sum.signum = 1;
            }
            else if ((*this).compare(copy) == -1)
            {
                sum.signum = -1;
            }
            else
            {
                sum.signum = 0;
            }
        }
        else
        {
            BigInteger copy(*this);
            copy.signum = 1;
            if ((copy).compare(N) == 1)
            {
                sum.signum = -1;
            }
            else if ((copy).compare(N) == -1)
            {
                sum.signum = 1;
            }
            else
            {
                sum.signum = 0;
            }
        }

        sign = -1;
        sumList(sum.digits, digits, N.digits, sign);
    }
    normalizeList(sum.digits);
    //std::cout << "SUM: " << sum << std::endl;
    // sum.signum = normalizeList(sum.digits);
    if (N.signum == -1 && signum == -1)
    {
        sum.signum = -1;
    }
    //std::cout << "Digits string: " << sum.digits << std::endl;
    return sum;
}

BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger diff = N;
    diff.negate();
    return (*this).add(diff);
}

BigInteger BigInteger::mult(const BigInteger &N) const {
    if (signum == 0 || N.signum == 0) {
        return BigInteger();
    }
    BigInteger product;
    product.signum = signum * N.signum;
    
    List ND = N.digits;
    List D = digits;
    List temp = D;
    List prev;
    int shift = 0;
    ND.moveBack();
    while (ND.position() > 0) {
        scalarMultList(temp, ND.movePrev());
        //std::cout << "temp: " << temp.to_string() << std::endl;
        shiftList(temp, shift);
        //std::cout << "Product dig 1: " << product.digits.to_string() << std::endl;
        prev = product.digits;
        //std::cout << "Prev: " << prev.to_string() << std::endl;
        sumList(product.digits, temp, prev, 1);
        //std::cout << "Product dig 2: " << product.digits.to_string() << std::endl;
        normalizeList(product.digits);
        //std::cout << "Product dig 2 After Normalize: " << product.digits.to_string() << std::endl;
        temp = D;
        shift++;
    }
    return product;
}

//OPERATORS

std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    stream << N.to_string();
    return stream;
}

bool operator==(const BigInteger &A, const BigInteger &B) {
    if (A.compare(B) == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool operator<(const BigInteger &A, const BigInteger &B) {
    if (A.compare(B) == -1) {
        return true;
    }
    else {
        return false;
    }
}


bool operator<=(const BigInteger &A, const BigInteger &B) {
    if (A.compare(B) <= 0) {
        return true;
    }
    else {
        return false;
    }
}
    
   
bool operator>(const BigInteger &A, const BigInteger &B) {
    if (A.compare(B) == 1) {
        return true;
    }
    else {
        return false;
    }
}

  
bool operator>=(const BigInteger &A, const BigInteger &B) {
    if (A.compare(B) >= 0) {
        return true;
    }
    else {
        return false;
    }
}

   
BigInteger operator+(const BigInteger &A, const BigInteger &B) {
    return A.add(B);
}

  
BigInteger operator+=(BigInteger &A, const BigInteger &B) {
    A = A.add(B);
    return A;
}

   
BigInteger operator-(const BigInteger &A, const BigInteger &B) {
    return A.sub(B);
}

   
BigInteger operator-=(BigInteger &A, const BigInteger &B) {
    A = A.sub(B);
    return A;
}

   
BigInteger operator*(const BigInteger &A, const BigInteger &B) {
    return A.mult(B);
}

   
BigInteger operator*=(BigInteger &A, const BigInteger &B) {
    A = A.mult(B);
    return A;
}

