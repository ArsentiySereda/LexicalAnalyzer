#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <iostream>
#include <fstream>
#include <string>
#include "HashTable.h"
#include "Token.h"

using namespace std;

class LexicalAnalyzer {
public:
    LexicalAnalyzer(const string& input, const string& output) {
        inputFile.open(input);
        outputFile.open(output);
    };
    ~LexicalAnalyzer() {};
    void analyzer();
    Token getNextLexeme();
    ifstream inputFile;
    ofstream outputFile;
    HashTable tokenList;
private:
    

    bool isOperator(char elem) const;
    bool isDelimiter(char elem) const;
    bool isWrongSymbol(char elem) const;

    
};

#endif
