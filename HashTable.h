#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "Token.h"
#include <fstream>
using namespace std;
class HashTable {
public:
    HashTable() : tokenCount(0) {
        for (int i = 0; i < HASH_SIZE; ++i)
            tokens[i] = nullptr;
    }

    ~HashTable() {
        for (long long i = 0; i < HASH_SIZE; i++)
            delete tokens[i];
    }
    int tokenCount;
    void newToken(const Token& token);
    int hashFunction(const string& lexeme) const;
    void outTable(ofstream& outputFile);
    int getIndex(int i) {
        return tokens[i]->getIndex();
    }

private:
    static const int HASH_SIZE = 10000;  
    Token* tokens[HASH_SIZE];  
                  
};

#endif
 