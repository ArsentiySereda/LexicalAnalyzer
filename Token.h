#ifndef TOKEN_H
#define TOKEN_H
#include <string>
using namespace std;

enum class TokenType {
    PROGRAM,     
    TYPE,       
    BEGIN,     
    END,       
    ID_NAME,
    INT_NUM,    
    REAL_NUM,  
    OPERATOR,   
    DELIMITER,  
    FUNC,       
    ERROR,      
    UNKNOWN
};

class Token {
public:
    TokenType type;       
    string lexeme;      
    int index;          
    int hash;         

    Token() : type(TokenType::UNKNOWN), lexeme(""), index(-1), hash(0) {}

    Token(TokenType t, const string& lex, int idx, int hsh)
        : type(t), lexeme(lex), index(idx), hash(hsh) {}

    int getIndex();        
    string getType();     
};

#endif TOKEN_H  