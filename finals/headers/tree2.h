#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

struct Movie {
    std::string imdb_id;
    std::string title;
    std::string plot_synopsis;
};

// Helper function to convert a string to lowercase
std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    std::vector<Movie> movies;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() : root(new TrieNode()) {}

    // Insert a title and plot synopsis into the Trie
    void insert(const Movie& movie) {
        insertString(root, toLower(movie.title), movie);
        insertString(root, toLower(movie.plot_synopsis), movie);
    }

    // Search for movies with titles or plot synopses that start with the given prefix
    std::vector<Movie> search(const std::string& prefix) {
        TrieNode* node = root;
        std::string lowerPrefix = toLower(prefix);
        for (char c : lowerPrefix) {
            if (node->children.find(c) == node->children.end()) {
                return {};
            }
            node = node->children[c];
        }
        return collectAllMovies(node);
    }

private:
    void insertString(TrieNode* node, const std::string& str, const Movie& movie) {
        for (char c : str) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;
        node->movies.push_back(movie);
    }

    std::vector<Movie> collectAllMovies(TrieNode* node) {
        std::vector<Movie> result;
        if (node->isEndOfWord) {
            result.insert(result.end(), node->movies.begin(), node->movies.end());
        }
        for (auto& child : node->children) {
            std::vector<Movie> childMovies = collectAllMovies(child.second);
            result.insert(result.end(), childMovies.begin(), childMovies.end());
        }
        return result;
    }
};

#endif // TRIE_H
