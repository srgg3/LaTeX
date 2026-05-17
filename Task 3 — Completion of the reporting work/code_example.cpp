// Упрощённый лексический анализатор для C++-подобного языка
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

enum TokenType {
    KEYWORD,    // int, float, return
    IDENTIFIER, // a, b, result
    NUMBER,     // 123, 3.14
    OPERATOR,   // =, +, -, *, /
    UNKNOWN
};

struct Token {
    TokenType type;
    string lexeme;
};

const vector<string> keywords = {"int", "float", "return"};

vector<Token> lex(const string& input) {
    vector<Token> tokens;
    size_t i = 0;
    while (i < input.size()) {
        char ch = input[i];
        if (isspace(ch)) {
            i++;
            continue;
        }
        if (isalpha(ch) || ch == '_') {
            string word;
            while (i < input.size() && (isalnum(input[i]) || input[i] == '_')) {
                word += input[i];
                i++;
            }
            bool isKw = false;
            for (const string& kw : keywords) {
                if (word == kw) {
                    tokens.push_back({KEYWORD, word});
                    isKw = true;
                    break;
                }
            }
            if (!isKw) {
                tokens.push_back({IDENTIFIER, word});
            }
            continue;
        }
        if (isdigit(ch)) {
            string num;
            while (i < input.size() && isdigit(input[i])) {
                num += input[i];
                i++;
            }
            tokens.push_back({NUMBER, num});
            continue;
        }
        if (ch == '=' || ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            tokens.push_back({OPERATOR, string(1, ch)});
            i++;
            continue;
        }
        tokens.push_back({UNKNOWN, string(1, ch)});
        i++;
    }
    return tokens;
}

void printTokens(const vector<Token>& tokens) {
    for (const Token& t : tokens) {
        string typeStr;
        switch (t.type) {
            case KEYWORD: typeStr = "KEYWORD"; break;
            case IDENTIFIER: typeStr = "IDENTIFIER"; break;
            case NUMBER: typeStr = "NUMBER"; break;
            case OPERATOR: typeStr = "OPERATOR"; break;
            case UNKNOWN: typeStr = "UNKNOWN"; break;
        }
        cout << "<" << typeStr << ", \"" << t.lexeme << "\">" << endl;
    }
}

int main() {
    string code = "int a = 5 + 3;";
    cout << "Input: " << code << endl;
    vector<Token> tokens = lex(code);
    printTokens(tokens);
    return 0;
}