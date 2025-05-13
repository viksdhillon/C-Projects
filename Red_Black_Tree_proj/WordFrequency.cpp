/***
 * Vik Dhillon
 * vsdhillo
 * 2025 Winter CSE101 PA8
 * WordFrequency.cpp
 * Client file for the Dictionary ADT with RBT implementation
 ***/
#include<iostream>
#include<fstream>
#include<string>
#include "Dictionary.h"
using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){

   //int token_count, line_count;
   size_t begin = 0;
   size_t end = 0;
   ifstream in;
   ofstream out;
   string line;
   //string tokenBuffer;
   string token;
   //string delim = " "; 
   string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   Dictionary D;
   // open files for reading and writing 
   in.open(argv[1]);
   out.open(argv[2]);
   while (getline(in, line)) {
      begin = 0;
      end = 0;
      while (begin < line.length()) {
        begin = line.find_first_not_of(delim, end);
        if (begin == string::npos) {
            end = line.length();
            break;
        }
        end = line.find_first_of(delim, begin);
        token = line.substr(begin, end - begin);
        for (char &r: token) {
            r = tolower(r);
        }
        //cout << token << endl;
        //cout << D.contains(token) << endl;
        if (token.length() > 0) {
            if (D.contains(token)) {
                int &freq = D.getValue(token); 
                freq+=1;
                //cout << "YOOO" << endl;
                //cout << "Freq: " << freq << endl;
            }
            else {
                D.setValue(token, 1);
                //cout << "YO" << endl;
            }
          }
      }
   }


   out << D.to_string() << endl;
   //out << endl;
   //out << D.pre_string() << endl;

   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}