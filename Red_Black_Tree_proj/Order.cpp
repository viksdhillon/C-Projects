/***
 * Vik Dhillon
 * vsdhillo
 * 2025 Winter CSE101 PA8
 * Order.cpp
 * Client program for the Dictionary ADT from pa7
 ***/
#include "Dictionary.h"
#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "You must specify exactly 3 command line arguments!\n");
        return EXIT_FAILURE;
    }

    std::ifstream file(argv[1]);
    std::ofstream out(argv[2]);

    Dictionary D;
    std::string l;
    int line = 1;
    while (getline(file, l))
    {
        D.setValue(l, line);
        line++;
    }

    out << D.to_string() << endl;

    out << endl;

    out << D.pre_string() << endl;

    out.close();
    file.close();

    return 0;
}