#ifndef CSV_HANDLER_H
#define CSV_HANDLER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class CSVHandler {
  public:
    std::vector<std::vector<std::string>> readCSV(const std::string &filename);
    void writeCSV(const std::string &filename, const std::vector<std::vector<std::string>> &data);
    void cleanData(const std::string &inputFile, const std::string &outputFile);
    std::vector<std::string> split(const std::string &s, char delimiter);

  private:
    std::string join(const std::vector<std::string>& tokens, char delimiter);
};

std::vector<std::vector<std::string>> CSVHandler::readCSV(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<std::vector<std::string>> data;
    std::string line;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    while (std::getline(file, line)) {
        data.push_back(split(line, ','));
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
    std::istringstream tokenStream(s);
    bool inQuotes = false;
    std::string currentToken;

    while (std::getline(tokenStream, token, delimiter)) {
        if (!inQuotes) {
            if (token.front() == '"' && token.back() != '"') {
                inQuotes = true;
                currentToken = token;
            } else {
                tokens.push_back(token);
            }
        } else {
            currentToken += delimiter + token;
            if (token.back() == '"') {
                inQuotes = false;
                tokens.push_back(currentToken);
            }
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

void CSVHandler::cleanData(const std::string &inputFile, const std::string &outputFile) {
    auto data = readCSV(inputFile);

    // Remove the last two columns from each row
    for (auto &row : data) {
        if (row.size() > 2) {
            row.resize(row.size() - 2);
        }
    }

    writeCSV(outputFile, data);
}

#endif // CSV_HANDLER_H
