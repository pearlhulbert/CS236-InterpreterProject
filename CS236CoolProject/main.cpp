
#include<iostream>
#include<fstream>
#include<sstream>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
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
    //cout << lexer->toString() << endl;
    vector<Token*> newInput = lexer->getInputTokens();
    Parser* data = new Parser(newInput);
    data->parseAll();
    DataLogProgram* datalogP = data->getDataLog();
    Interpreter* interpreter = new Interpreter(datalogP);
    //cout << data->toString();
    interpreter->interpret();
    //cout << interpreter->toString();
    delete lexer;
    delete data;
    return 0;
}
