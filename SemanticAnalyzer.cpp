#include "SemanticAnalyzer.h"

bool SemanticAnalyzer::isNameEqual(Node PROGRAM, Node END)
{
	if (PROGRAM.children[1].data == END.children[1].data) {
		return true;
	}
	else {
		throw runtime_error("Semantic error, the beginning and ending names of the program do not match");
	}
	return false;
}

void SemanticAnalyzer::WriteDeskriptions(Node Deskr)
{
	//Рассматриваем по одной ветке определения переменных
	for (int i = 0; i < Deskr.children.size(); i++) {
		vector <string> newDeskr;//Первым в новую запись помещаем первого ребенка первой 
		newDeskr.push_back(Deskr.children[i].children[0].data);	//ветки определения => тип вводимых данных
		int CountDefinitions = Deskr.children[i].children[1].children.size();
		for (int j = 0; j < CountDefinitions; j++) {
			string thisVar = Deskr.children[i].children[1].children[j].data;
			for (int h = 0; h < Deskriptions.size(); h++) {
				for (int k = 1; k < Deskriptions[h].size() - 1; k++) {
					if (thisVar == Deskriptions[h][k]) {
						throw runtime_error("Semantic error, a repeat announcement was received of token "
						+ thisVar + " in deskription line №" + to_string(i + 1));
					}
				}
			}
			for (int k = 1; k < newDeskr.size(); k++) {
				if (thisVar == newDeskr[k]) {
					throw runtime_error("Semantic error, a repeat announcement was received of token "
						+ thisVar + " in deskription line №" + to_string(i + 1));
				}
			}
			newDeskr.push_back(thisVar);
		}
		if (CountDefinitions > 1) {
			newDeskr.push_back(to_string(CountDefinitions + 1));
		}
		newDeskr.push_back("DECL");
		Deskriptions.push_back(newDeskr);
	}
}

void SemanticAnalyzer::WriteOperators(Node Oper)
{
	int OperCount = Oper.children.size();
	for (int i = 0; i < OperCount; i++) {
		vector <string> newOper;
		newOper.push_back(Oper.children[i].children[0].data);
		vector <string> Expr = WriteExpr(Oper.children[i].children[1]);
		for (int h = 0; h < Expr.size(); h++) { newOper.push_back(Expr[h]); }
		newOper.push_back(Oper.children[i].children[1].data);
		Operators.push_back(newOper);
	}
}

vector<string> SemanticAnalyzer::WriteExpr(Node Expr)
{
	vector <string> Expression;
	if (Expr.children[0].children[0].data == "ID_NAME" || Expr.children[0].children[0].data == "INT_NUM" ||
		Expr.children[0].children[0].data == "REAL_NUM") {
		Expression.push_back(Expr.children[0].children[0].children[0].data);
	}
	else {
		if (Expr.children[0].children[0].data == "ITOR" || Expr.children[0].children[0].data == "RTOI") {
			Expression.push_back(Expr.children[0].children[0].data); // мы нашли функцию itor или rtoi
			vector <string> Expr1 = WriteExpr(Expr.children[0].children[1]);//анализируем выражение под функцией
			for (int h = 0; h < Expr1.size(); h++) { Expression.push_back(Expr1[h]); }
			Expression.push_back("CALL");
		}
		else if (Expr.children[0].children[0].data == "(") {
			vector <string> Expr1 = WriteExpr(Expr.children[0].children[0]);//анализируем выражение под функцией
			for (int h = 0; h < Expr1.size(); h++) { Expression.push_back(Expr1[h]); }
		}
	}
	if (Expr.children.size() == 2) {
		vector <string> Expr2 = WriteExpr(Expr.children[1]);
		for (int h = 0; h < Expr2.size(); h++) { Expression.push_back(Expr2[h]); }
		Expression.push_back(Expr.children[1].data);
	}
	return Expression;
}

void SemanticAnalyzer::printSematicAnalyzer()
{
	for (int i = 0; i < Deskriptions.size(); i++) {
		cout << Deskriptions[i][0];
		for (int j = 1; j < Deskriptions[i].size(); j++) {
			cout << Deskriptions[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < Operators.size(); i++) {
		for (int j = 0; j < Operators[i].size(); j++) {
			cout << Operators[i][j] << " ";
		}
		cout << endl;
	}
}
