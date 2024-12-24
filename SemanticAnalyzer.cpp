#include "SemanticAnalyzer.h"

void SemanticAnalyzer::lineToConsole(vector<string> line)
{
	for (int i = 0; i < line.size(); i++) {
		cout << line[i] << " ";
	}
	cout << endl;
}

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
			if (Deskr.children[i].children[0].data == "INTEGER") {
				int_id.push_back(thisVar);
			}
			else if (Deskr.children[i].children[0].data == "REAL") {
				real_id.push_back(thisVar);
			}
		}
		if (CountDefinitions > 1) {
			newDeskr.push_back(to_string(CountDefinitions + 1));
		}
		newDeskr.push_back("DECL");
		Deskriptions.push_back(newDeskr);
		lineToConsole(Deskriptions[Deskriptions.size() - 1]);
	}
	//lineToConsole(int_id);
	//lineToConsole(real_id);
}

void SemanticAnalyzer::WriteOperators(Node Oper)
{
	int OperCount = Oper.children.size();
	for (int i = 0; i < OperCount; i++) {
		vector <string> newOper;
		newOper.push_back(Oper.children[i].children[0].data);//получаем первый операнд которому все будет присваиваться
		string type = getIdType(Oper.children[i].children[0].data, i + 1);
		vector <string> Expr1 = WriteSimpleExpr(Oper.children[i].children[1].children[0],type, i + 1);
		for (int h = 0; h < Expr1.size(); h++) { newOper.push_back(Expr1[h]); }
		if (Oper.children[i].children[1].children.size() == 2) {
			vector <string> Expr = WriteExpr(Oper.children[i].children[1].children[1], type, i + 1);
			for (int h = 0; h < Expr.size(); h++) { newOper.push_back(Expr[h]); }
		}
		newOper.push_back(Oper.children[i].children[1].data);
		Operators.push_back(newOper);
		lineToConsole(Operators[Operators.size() - 1]);
	}
}

vector <string> SemanticAnalyzer::WriteExpr(Node Expr, string type, int num) {
	vector <string> Expression;
	vector <string> Expr1 = WriteSimpleExpr(Expr.children[0], type, num);
	for (int h = 0; h < Expr1.size(); h++) { Expression.push_back(Expr1[h]); }
	Expression.push_back(Expr.data);
	if (Expr.children.size() == 2) {
		vector <string> Expr2 = WriteExpr(Expr.children[1], type, num);
		for (int h = 0; h < Expr2.size(); h++) { Expression.push_back(Expr2[h]); }
	}
	return Expression;
}

vector<string> SemanticAnalyzer::WriteSimpleExpr(Node SimpleExpr, string type, int num)
{
	vector <string> SimpleExpression;
	if (SimpleExpr.children[0].data == "ID_NAME") {
		string id_type = getIdType(SimpleExpr.children[0].children[0].data, num);
		if (id_type == type) {
			SimpleExpression.push_back(SimpleExpr.children[0].children[0].data);
		}
		else {
			throw runtime_error("Sematnic error: incorrect type of operand '" + SimpleExpr.children[0].children[0].data
				+ "' in operator line №" + to_string(num));
		}
	}
	else if (SimpleExpr.children[0].data == "INT_NUM") {
		if (type == "INT") {
			SimpleExpression.push_back(SimpleExpr.children[0].children[0].data);
		}
		else {
			throw runtime_error("Sematnic error: incorrect type of operand '" + SimpleExpr.children[0].children[0].data
				+ "' in operator line №" + to_string(num));
		}
	}
	else if (SimpleExpr.children[0].data == "REAL_NUM") {
		if (type == "REAL") {
			SimpleExpression.push_back(SimpleExpr.children[0].children[0].data);
		}
		else {
			throw runtime_error("Sematnic error: incorrect type of operand '" + SimpleExpr.children[0].children[0].data
				+ "' in operator line №" + to_string(num));
		}
	}
	else {
		if (SimpleExpr.children[0].data == "ITOR") {
			if (type == "REAL") {
				SimpleExpression.push_back(SimpleExpr.children[0].data); // мы нашли функцию itor
				string type1 = "INT";
				vector <string> Expr1 = WriteSimpleExpr(SimpleExpr.children[1].children[0], type1, num);
				for (int h = 0; h < Expr1.size(); h++) { SimpleExpression.push_back(Expr1[h]); }
				if (SimpleExpr.children[1].children.size() == 2) {
					vector <string> Expr1 = WriteExpr(SimpleExpr.children[1].children[1], type1, num);
					for (int h = 0; h < Expr1.size(); h++) { SimpleExpression.push_back(Expr1[h]); }
				}
				SimpleExpression.push_back("CALL");
			}
			else {
				throw runtime_error("Sematnic error: incorrect function '" + SimpleExpr.children[0].data
					+ "' in operator line №" + to_string(num));
			}
		}
		else if (SimpleExpr.children[0].data == "RTOI") {
			if (type == "INT") {
				SimpleExpression.push_back(SimpleExpr.children[0].data); // мы нашли функцию rtoi
				string type1 = "REAL";
				vector <string> Expr1 = WriteSimpleExpr(SimpleExpr.children[1].children[0], type1, num);
				for (int h = 0; h < Expr1.size(); h++) { SimpleExpression.push_back(Expr1[h]); }
				if (SimpleExpr.children[1].children.size() == 2) {
					vector <string> Expr1 = WriteExpr(SimpleExpr.children[1].children[1], type1, num);
					for (int h = 0; h < Expr1.size(); h++) { SimpleExpression.push_back(Expr1[h]); }
				}
				SimpleExpression.push_back("CALL");
			}
			else {
				throw runtime_error("Sematnic error: incorrect function '" + SimpleExpr.children[0].data
					+ "' in operator line №" + to_string(num));
			}
		}
		else if (SimpleExpr.children[0].data == "(") {
			vector <string> Expr1 = WriteSimpleExpr(SimpleExpr.children[0].children[0], type, num);
			for (int h = 0; h < Expr1.size(); h++) { SimpleExpression.push_back(Expr1[h]); }
			if (SimpleExpr.children[0].children.size() == 2) {
				vector <string> Expr2 = WriteExpr(SimpleExpr.children[0].children[1], type, num);
				for (int h = 0; h < Expr2.size(); h++) { SimpleExpression.push_back(Expr2[h]); }
			}
		}
	}
	return SimpleExpression;
}

string SemanticAnalyzer::getIdType(string ID, int line)
{
	for (int i = 0; i < int_id.size(); i++) {
		if (ID == int_id[i]) { return "INT";}
	}
	for (int i = 0; i < real_id.size(); i++) {
		if (ID == real_id[i]) { return "REAL";}
	}
	throw runtime_error("Semantic error: id '" + ID + "' in operator line " + to_string(line) + " not found in definitions");
}

void SemanticAnalyzer::printSematicAnalyzer(ofstream& outputFile)
{
	for (int i = 0; i < Deskriptions.size(); i++) {
		outputFile << Deskriptions[i][0];
		for (int j = 1; j < Deskriptions[i].size(); j++) {
			outputFile << Deskriptions[i][j] << " ";
		}
		outputFile << endl;
	}
	for (int i = 0; i < Operators.size(); i++) {
		for (int j = 0; j < Operators[i].size(); j++) {
			outputFile << Operators[i][j] << " ";
		}
		outputFile << endl;
	}
}