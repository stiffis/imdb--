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

class CSVHandler {
  public:
    std::vector<std::vector<std::string>> readCSV(const std::string &filename);
    void writeCSV(const std::string &filename, const std::vector<std::vector<std::string>> &data);
    void cleanData(const std::string &inputFile, const std::string &outputFile);
    std::vector<std::string> split(const std::string &s, char delimiter);

  private:
    std::string join(const std::vector<std::string>& tokens, char delimiter);
    bool isValidRow(const std::vector<std::string>& row);
};

std::vector<std::vector<std::string>> CSVHandler::readCSV(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<std::vector<std::string>> data;
    std::string line;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    while (std::getline(file, line)) {
        std::vector<std::string> row = split(line, ',');
        if (isValidRow(row)) {
            data.push_back(row);
        }
    }

    file.close();
    return data;
}

void CSVHandler::writeCSV(const std::string &filename, const std::vector<std::vector<std::string>> &data) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    for (const auto &row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) {
                file << ",";
            }
        }
        file << "\n";
    }

    file.close();
}

std::vector<std::string> CSVHandler::split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    bool inQuotes = false;
    std::ostringstream currentToken;

    for (char ch : s) {
        if (ch == '"' && (currentToken.str().empty() || currentToken.str().back() != '\\')) {
            inQuotes = !inQuotes;
        } else if (ch == delimiter && !inQuotes) {
            tokens.push_back(currentToken.str());
            currentToken.str("");
            currentToken.clear();
        } else {
            currentToken << ch;
        }
    }
    tokens.push_back(currentToken.str());

    // Trim spaces and quotes from tokens
    for (auto &t : tokens) {
        t.erase(t.begin(), std::find_if(t.begin(), t.end(), [](unsigned char ch) { return !std::isspace(ch); }));
        t.erase(std::find_if(t.rbegin(), t.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), t.end());
        if (t.front() == '"' && t.back() == '"') {
            t = t.substr(1, t.size() - 2);
        }
    }

    return tokens;
}

std::string CSVHandler::join(const std::vector<std::string>& tokens, char delimiter) {
    std::ostringstream result;
    for (size_t i = 0; i < tokens.size(); ++i) {
        result << tokens[i];
        if (i < tokens.size() - 1) {
            result << delimiter;
        }
    }
    return result.str();
}

bool CSVHandler::isValidRow(const std::vector<std::string>& row) {
    for (const auto &cell : row) {
        if (cell.empty() || cell == "\"\"" || cell == "==" || cell == "\",") {
            return false;
        }
    }
    return true;
}

void CSVHandler::cleanData(const std::string &inputFile, const std::string &outputFile) {
    auto data = readCSV(inputFile);

    // Remove invalid rows
    std::vector<std::vector<std::string>> cleanedData;
    for (const auto &row : data) {
        if (isValidRow(row)) {
            cleanedData.push_back(row);
        }
    }

    writeCSV(outputFile, cleanedData);
}

#endif // CSV_HANDLER_H
