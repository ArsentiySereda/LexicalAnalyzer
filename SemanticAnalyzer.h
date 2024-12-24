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
	void printSematicAnalyzer(ofstream& outputFile);

private:

	vector <string> int_id;
	vector <string> real_id;
	bool isCorrectName;
	vector <vector <string> > Deskriptions;
	vector <vector <string> > Operators;
	void lineToConsole(vector <string> line);
	bool isNameEqual(Node PROGRAM, Node END);
	void WriteDeskriptions(Node Deskr);
	void WriteOperators(Node Oper);
	vector <string> WriteExpr(Node Expr, string type, int num);
	vector <string> WriteSimpleExpr(Node SimpleExpr, string type, int num);
	string getIdType(string ID, int line);
};

