
#include<iostream>
#include<fstream>
#include<sstream>
#include "Lexer.h"
using namespace std;

int main(int argc, char* argv[]) {
    // check command line arguments
    if (argc != 2) {
        cout << "usage: " << argv[0] << " input_file" << endl;
        return 1;
    }

    // open file
    string fileName = argv[1];
    ifstream input(fileName);
    if (!input.is_open()) {
        cout << "File " << fileName << " could not be found or opened." << endl;
        return 1;
    }
    stringstream buffer;
    buffer << input.rdbuf();
    string line = buffer.str();

    Lexer* lexer = new Lexer();
    lexer->Run(line);
    //lexer->EndOfFile();
    cout << lexer->toString();
    delete lexer;

    return 0;
}
