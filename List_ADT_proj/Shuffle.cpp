/***
* Vik Dhillon
* vsdhillo
* 2025 Winter CSE101 PA5
* Shuffle.cpp
* Client program for the List ADT
***/
#include"List.h"
using namespace std;
void shuffle(List& D) {
    int size = (D.length() / 2);
    if (D.length() % 2 == 0) {
        int oneHalf[size];
        int twoHalf[size];
        D.moveFront();
        int count = 0;
        int two_counter = 0;
        while (D.position() < D.length()) {
            if (count < size) {
                oneHalf[count] = D.moveNext();
            }
            else {
                twoHalf[two_counter] = D.moveNext();
                two_counter++;
            }
            count++;
        }

        D.clear();
        for (int i = size - 1; i >= 0; i--) {
            D.insertAfter(oneHalf[i]);
            D.insertAfter(twoHalf[i]);
        }
        //cout << "List: " << D.to_string() << endl;
    }
    else {
        int oneHalf[size];
        int twoHalf[size + 1];
        D.moveFront();
        int counter = 0;
        int two_count = 0;
        while (D.position() < D.length()) {
            if (counter < size) {
                oneHalf[counter] = D.moveNext();
            }
            else {
                twoHalf[two_count] = D.moveNext();
                two_count++;
            }
            counter++;
        }

        D.clear();
        D.insertAfter(twoHalf[size]);
        for (int i = size - 1; i >= 0; i--) {
            D.insertAfter(oneHalf[i]);
            D.insertAfter(twoHalf[i]);
        }
        
        //cout << "List: " << D.to_string() << endl;
    }

}


int main(int argc, char*argv[]) {
    if (argc != 2)
    {
        fprintf(stderr, "You must specify exactly 2 command line arguments!\n");
        return EXIT_FAILURE;
    }

    int result;
    result = stoi(argv[1]);
    if (result == 0) {
        return 0;
    }
    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;
    for (int i = 1; i <= result; i++) {
        List A;
        A.moveFront();
        for (int y = 0; y < i; y++) {
            A.insertAfter(y);
            A.moveNext();
        }
        List B;
        B = A;
        //cout << "A: " << A.to_string() << endl;
        //cout << "B: " << B.to_string() << endl;
        shuffle(A);
        //cout << "A: " << A.to_string() << endl;
        cout << endl;
        int count = 1;
        while (!(B.equals(A))) {
            shuffle(A);
            //cout << "A: " << A.to_string() << endl;
            count++;
        }
        cout << i << "               " << count << endl;
    }
    return 0;
}

