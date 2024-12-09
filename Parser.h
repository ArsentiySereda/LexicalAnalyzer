
#include "Node.h"
#include "LexicalAnalyzer.h"
#include "HashTable.h"
#include <iostream>
#include <string>
using namespace std;

class Parser {
private:
    
    Token currentToken;  
    void getNextToken(); 

    void Start(Node& n);
    void Program(Node& n);
    void End(Node& n);
    void Descriptions(Node& n);
    void Operators(Node& n);
    void Descr(Node& n);
    void VarList(Node& n);
    void Op(Node& n);
    void Expr(Node& n);
    void SimpleExpr(Node& n);

public:
    Parser(LexicalAnalyzer& lexer);
    Node parse();
    LexicalAnalyzer& lexer;       
};
