#include "Parser.h"


int operatorsCount = 0;
int countLines = 1;

void Parser::getNextToken()
{
    currentToken = lexer.getNextLexeme(); 
    lexer.tokenList.newToken(currentToken);
    if (currentToken.type == TokenType::ERROR) {
        throw runtime_error("Lexical error: invalid token '" + currentToken.lexeme + "'");
    }
}

void Parser::Start(Node& n) {
    n.addSon("PROGRAM");
    Program(n.getSon(n.children.size() - 1)); 

    n.addSon("Descriptions");
    Descriptions(n.getSon(n.children.size() - 1));

    n.addSon("Operators");
    Operators(n.getSon(n.children.size() - 1));

    n.addSon("End");
    End(n.getSon(n.children.size() - 1));
}

int deskrNodeCount = 1;

void Parser::Program(Node& n) {
    getNextToken();
    countLines++;
    if (currentToken.type == TokenType::PROGRAM && currentToken.lexeme == "PROGRAM") {
        n.addSon(currentToken.lexeme);
        getNextToken(); 
        if (currentToken.type == TokenType::ID_NAME) {
            n.addSon(currentToken.lexeme);

            getNextToken(); 
        }
        else {
            throw runtime_error("Syntax error: token of unexpected type after PROGRAM with number: " +
                to_string(lexer.tokenList.tokenCount) + " in line " + to_string(countLines));
        }
        
    }
    else {
        throw runtime_error("Syntax error: expected 'PROGRAM' in token with number: " + to_string(lexer.tokenList.tokenCount) 
            + ", got: " + currentToken.lexeme + " in line " + to_string(countLines)) ;
    }
}


void Parser::Descriptions(Node& n) {
    while (currentToken.type == TokenType::TYPE) { 
        n.addSon("deskrNode" + to_string(deskrNodeCount));
        deskrNodeCount++;
        Descr(n.getSon(n.children.size() - 1));
    }
}

void Parser::Descr(Node& n) {
    if (currentToken.type == TokenType::TYPE) {
        n.addSon(currentToken.lexeme);
        countLines++;

        getNextToken(); 
        if (currentToken.type == TokenType::ID_NAME) {
            n.addSon("VarList");
            VarList(n.getSon(n.children.size() - 1));
        }
        else {
            throw runtime_error("Syntax error: expected new variable in token " + to_string(lexer.tokenList.tokenCount) 
                + ", got: " + currentToken.lexeme + " in line " + to_string(countLines));

        }
        

    }
    else {
        throw runtime_error("Syntax error: expected type in token " + to_string(lexer.tokenList.tokenCount) 
            + ", got: " + currentToken.lexeme + " in line " + to_string(countLines));
    }
}

void Parser::VarList(Node& n) {
    if (currentToken.type == TokenType::ID_NAME) {
        n.addSon(currentToken.lexeme); 
        getNextToken(); 

        while (currentToken.type == TokenType::DELIMITER && currentToken.lexeme == ",") {
            getNextToken(); 

            if (currentToken.type == TokenType::ID_NAME) {
                n.addSon(currentToken.lexeme); 
                getNextToken();
            }
            else {
                throw runtime_error("Syntax error: expected variable name after ',' in token " + to_string(lexer.tokenList.tokenCount) 
                    + ", got: " + currentToken.lexeme + " in line " + to_string(countLines));
            }
        }

        
    }
}


void Parser::Operators(Node& n) {
    while (currentToken.type == TokenType::ID_NAME) {
        operatorsCount++;
        countLines++;

        n.addSon("OpLine " + to_string(operatorsCount));
        Op(n.getSon(n.children.size() - 1));

    }
}

void Parser::Op(Node& n) {
    n.addSon(currentToken.lexeme); 
    getNextToken();

    if (currentToken.type == TokenType::OPERATOR && currentToken.lexeme == "=") {
        n.addSon(currentToken.lexeme);
        getNextToken();

        if (currentToken.type == TokenType::OPERATOR) {
            throw runtime_error("Syntax error: unexpected operator '" + currentToken.lexeme +
                "' after '=' in operator ¹" + to_string(operatorsCount) +
                " in line " + to_string(countLines));
        }

        Expr(n.getSon(n.children.size() - 1));
    }
    else {
        throw runtime_error("Syntax error: expected '=' as start of operator ¹" +
            to_string(operatorsCount) + ", got: " + currentToken.lexeme +
            " in line " + to_string(countLines));
    }
}

void Parser::Expr(Node& n) {
    if (currentToken.type == TokenType::FUNC ||
        currentToken.type == TokenType::ID_NAME ||
        currentToken.type == TokenType::INT_NUM ||
        currentToken.type == TokenType::REAL_NUM ||
        currentToken.lexeme == "(") {
        n.addSon("SimpleExpr");
        SimpleExpr(n.getSon(n.children.size() - 1));
    }
    else {
        throw runtime_error("Syntax error: expected operand, got: " + currentToken.lexeme +
            " in line " + to_string(countLines));
    }

    if (currentToken.type == TokenType::OPERATOR && currentToken.lexeme != "=") {
        string operatorLexeme = currentToken.lexeme;
        n.addSon(operatorLexeme);
        getNextToken();

        if (currentToken.type == TokenType::FUNC ||
            currentToken.type == TokenType::ID_NAME ||
            currentToken.type == TokenType::INT_NUM ||
            currentToken.type == TokenType::REAL_NUM ||
            currentToken.lexeme == "(") {
            Expr(n.getSon(n.children.size() - 1)); 
        }
        else {
            throw runtime_error("Syntax error: expected operand after operator '" + operatorLexeme +
                "', got: " + currentToken.lexeme + " in line " + to_string(countLines));
        }
    }
}


void Parser::SimpleExpr(Node& n) {
    if (currentToken.lexeme == "(") {
        n.addSon("(");
        getNextToken();
        Expr(n.getSon(n.children.size() - 1));

        if (currentToken.lexeme == ")") {
            n.addSon(")");
            getNextToken();
        }
        else {
            throw runtime_error("Syntax error: expected ')', got: " + currentToken.lexeme +
                " in line " + to_string(countLines));
        }
    }
    else if (currentToken.type == TokenType::INT_NUM) {
        n.addSon("INT_NUM");
        n.children[0].addSon(currentToken.lexeme);
        getNextToken();
    }
    else if (currentToken.type == TokenType::REAL_NUM) {
        n.addSon("REAL_NUM");
        n.children[0].addSon(currentToken.lexeme);
        getNextToken();
    }
    else if (currentToken.type == TokenType::ID_NAME) {
        n.addSon("ID_NAME");
        n.children[0].addSon(currentToken.lexeme);
        getNextToken();
    }
    else if (currentToken.type == TokenType::FUNC) {
        n.addSon(currentToken.lexeme);
        getNextToken();

        if (currentToken.lexeme == "(") {
            n.addSon("(");
            getNextToken();
            Expr(n.getSon(n.children.size() - 1));

            if (currentToken.lexeme == ")") {
                n.addSon(")");
                getNextToken();
            }
            else {
                throw runtime_error("Syntax error: expected ')', got: " + currentToken.lexeme +
                    " in line " + to_string(countLines));
            }
        }
        else {
            throw runtime_error("Syntax error: expected '(', got: " + currentToken.lexeme +
                " in line " + to_string(countLines));
        }
    }
    else {
        throw runtime_error("Syntax error: unexpected token in SimpleExpr: " + currentToken.lexeme +
            " in line " + to_string(countLines));
    }
}




void Parser::End(Node& n)
{
    if (currentToken.type == TokenType::END && currentToken.lexeme == "END") {
        n.addSon(currentToken.lexeme);
        countLines++;
        getNextToken();
        if (currentToken.type == TokenType::ID_NAME) {
            n.addSon(currentToken.lexeme);
            getNextToken();
            
        }
        else {
            throw runtime_error("Syntax error: token of unexpected type after END, got: " + currentToken.lexeme
                + " with number : " + to_string(lexer.tokenList.tokenCount) + " in line " + to_string(countLines));
        }

    }
    else {
        throw runtime_error("Syntax error: expected 'END' , got: " + currentToken.lexeme
            + " with number : " + to_string(lexer.tokenList.tokenCount) + " in line " + to_string(countLines));
    }
}

Parser::Parser(LexicalAnalyzer& lexer) : lexer(lexer) {
    currentToken = Token(TokenType::UNKNOWN, "", 50000, 0);
}

Node Parser::parse() {
    Node root("Program");
    Start(root);     
    return root;
}
