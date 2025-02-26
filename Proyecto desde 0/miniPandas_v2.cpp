#ifndef CSV_HANDLER_H
#define CSV_HANDLER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <regex>
#include <algorithm>
#include <stack>

class CSVHandler {
  public:
    std::vector<std::vector<std::string>> readCSV(const std::string &filename);
    void writeCSV(const std::string &filename, const std::vector<std::vector<std::string>> &data);
    void cleanData(const std::string &inputFile, const std::string &outputFile);
    std::vector<std::string> split(const std::string &s, char delimiter);

  private:
    std::string join(const std::vector<std::string>& tokens, char delimiter);
    bool isValidRow(const std::vector<std::string>& row);
    bool validarCierreSimbolos(const std::string& str);
};

bool CSVHandler::validarCierreSimbolos(const std::string& str) {
    std::stack<char> s;
    bool dentroComillas = false;

    for (char ch : str) {
        if (ch == '"') {
            dentroComillas = !dentroComillas;
        } else if (!dentroComillas) {
            if (ch == '(' || ch == '[' || ch == '{') {
                s.push(ch);
            } else if (ch == ')' || ch == ']' || ch == '}') {
                if (s.empty()) return false;
                char top = s.top();
                if ((ch == ')' && top != '(') ||
                    (ch == ']' && top != '[') ||
                    (ch == '}' && top != '{')) {
                    return false;
                }
                s.pop();
            }
        }
    }
    return s.empty() && !dentroComillas;
}

bool CSVHandler::isValidRow(const std::vector<std::string>& row) {
    for (const auto &cell : row) {
        if (cell.empty() || cell == "\"\"" || cell == "==" || cell == "\",") {
            return false;
        }
        if (!validarCierreSimbolos(cell)) {
            return false;
        }
    }
    return true;
}

#endif // CSV_HANDLER_H
