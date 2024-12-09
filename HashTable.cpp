#include <iostream>
#include "HashTable.h"
using namespace std;

void SpaceVizualizer(int a, ofstream& outputFile) {
    while (a > 0) {
        outputFile << " ";
        a--;
    }
}

int HashTable::hashFunction(const string& lexeme) const {
    int hash = 0;
    for (char elem : lexeme)
        hash = (hash * 31 + elem) % HASH_SIZE;
    return hash;
}
void HashTable::newToken(const Token& token) {
    int hash = hashFunction(token.lexeme);

    if (tokens[hash] == nullptr) {
        tokens[hash] = new Token(token.type, token.lexeme, tokenCount, hash);
        tokenCount++;
    }
    else {
        if (tokens[hash]->lexeme == token.lexeme)
            return;

        int newHash = (hash + 1) % HASH_SIZE;
        while (tokens[newHash] != nullptr) {
            newHash = (newHash + 1) % HASH_SIZE;
        }
        tokens[newHash] = new Token(token.type, token.lexeme, tokenCount, newHash);
        tokenCount++;
    }
}
void HashTable::outTable(ofstream& outputFile) {
    for (int i = 0; i < HASH_SIZE; i++) {
        Token* token = new Token();
        for (int j = 0; j < HASH_SIZE; j++) {
            if (tokens[j] == nullptr)
                continue;

            if (i == getIndex(j)) {
                token = tokens[j];
                break;
            }
        }
        if (token->type != TokenType::UNKNOWN && token->type != TokenType::ERROR) {
            string tokenType = token->getType();
            outputFile << " " << tokenType;
            SpaceVizualizer(10 - tokenType.size(), outputFile);
            outputFile << "|  " << token->lexeme;
            SpaceVizualizer(10 - token->lexeme.size(), outputFile);
            outputFile << "| " << token->hash << endl;
        }   
    }
    outputFile << endl;
    for (int i = 0; i < HASH_SIZE; i++) {
        Token* token = tokens[i];
        if (tokens[i] != nullptr && token->type == TokenType::ERROR) {
            outputFile << " " << "ERROR";
            SpaceVizualizer(5, outputFile);
            outputFile << "|  " << token->lexeme;
            SpaceVizualizer(10 - token->lexeme.size(), outputFile);
            outputFile << "| " << token->hash << endl;
        }
    }
} 