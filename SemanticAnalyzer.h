#include "Node.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#pragma once
class SemanticAnalyzer
{
public:

	SemanticAnalyzer(Node n) {
		isCorrectName = isNameEqual(n.children[0], n.children[3]);
		WriteDeskriptions(n.children[1]);
		WriteOperators(n.children[2]);
	}

	void printSematicAnalyzer();

private:
	bool isCorrectName;
	vector <vector <string> > Deskriptions;
	vector <vector <string> > Operators;

	bool isNameEqual(Node PROGRAM, Node END);
	void WriteDeskriptions(Node Deskr);
	void WriteOperators(Node Oper);
	vector <string> WriteExpr(Node Expr);
};

