#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <fstream>
#include <sstream>
#include <locale>;
#include "windows.h";

using namespace std;

class Token {
public:
	string lexeme;
	string type;

	Token(string lexeme, string type) : lexeme(lexeme), type(type) {}
};

string getTokenType(string lexeme) {

	if (regex_match(lexeme, regex("\\d+\\.\\d*|\\d*\\.\\d+"))) {
		return "Число з плаваючою крапкою";
	}
	else if (regex_match(lexeme, regex("0x[0-9a-fA-F]+"))) {
		return "Шістнадцяткове число";
	}
	else if (regex_match(lexeme, regex("\\d+"))) {
		return "Число";
	}
	else if (regex_match(lexeme, regex("\"[^\"]*\"|'[^']*'"))) {
		return "Рядок";
	}
	else if (regex_match(lexeme, regex("(#[If|ElseIf|Else|End If|Const]+.*)"))) {
		return "Директива препроцесора";
	}
	else if (regex_match(lexeme, regex("'[^\n]*"))) {
		return "Коментар";
	}
	else if (
		lexeme == "If" || 
		lexeme == "ElseIf" ||
		lexeme == "Else" ||
		lexeme == "End If" ||
		lexeme == "End" ||
		lexeme == "Then" ||
		lexeme == "Module" ||
		lexeme == "Program" ||
		lexeme == "Sub" ||
		lexeme == "String" ||
		lexeme == "As" ||
		lexeme == "Dim" ||
		lexeme == "Double" ||
		lexeme == "Char" ||
		lexeme == "Integer" ||
		lexeme == "Console" ||
		lexeme == "WriteLine" ||
		lexeme == "End If"
		) {
		return "Зарезервоване слово";
	}
	else if (lexeme == "+" || lexeme == "-" || lexeme == "*" || lexeme == "/" || lexeme == "=") {
		return "Оператор";
	}
	else if (lexeme == ";" || lexeme == "," || lexeme == "(" || lexeme == ")") {
		return "Розділовий знак";
	}
	else if (regex_match(lexeme, regex("^[a-zA-Z_][a-zA-Z0-9_]*$"))) {
		return "Ідентифікатор";
	}
	else {
		return "Нерозпізнана лексема";
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_CTYPE, "ukr");

	regex pattern(R"(\"[^\"]*\"|'[^']*'|[(]|[)]|[,]|[\]|["]|[a-zA-Z_]\w*|0[xX][0-9a-fA-F]+|\d*\.\d+|\d+\.\d*|\d+|//[^$]*|#\w+|==|=|[+\-*/])");

	vector<Token> tokens;

	ifstream file("input.txt");

	if (!file.is_open()) {
		cerr << "File open error, no file found." << endl;
		return 0;
	}

	string line;

	while (getline(file, line)) {
		sregex_iterator it(line.begin(), line.end(), pattern);
		sregex_iterator it_end;
		while (it != it_end) {
			string lexeme = it->str();
			string type = getTokenType(lexeme);
			tokens.push_back(Token(lexeme, type));
			++it;
		}
	}

	cout << "Лексема - Тип лексеми" << endl;
	for (const Token& token : tokens) {
		cout << token.lexeme << " - " << token.type << endl;
	}

	system("pause");
	return 0;
}
