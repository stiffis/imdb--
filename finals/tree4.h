
#ifndef TRIE_H
#define TRIE_H

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Movie {
    std::string imdb_id;
    std::string title;
    std::string plot_synopsis;
    int match_count = 0; // Contador de coincidencias con el prefijo
    std::unordered_set<std::string> tags;
};

// Convierte un string a minúsculas
std::string toLower(const std::string &str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

class TrieNode {
  public:
    std::unordered_map<char, TrieNode *> children;
    bool isEndOfWord;
    std::vector<Movie> movies;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
  private:
    TrieNode *root;

  public:
    Trie() : root(new TrieNode()) {}

    ~Trie() { freeTrie(root); }

    // Insertar una película en el Trie
    void insert(const Movie &movie) {
        insertString(root, toLower(movie.title), movie);
        insertString(root, toLower(movie.plot_synopsis), movie);
    }

    // Buscar películas excluyendo los géneros no deseados
    std::vector<Movie> search(const std::string &prefix,
                              const std::unordered_set<std::string> &excludedGenres) {
        TrieNode *node = root;
        std::string lowerPrefix = toLower(prefix);

        for (char c : lowerPrefix) {
            if (node->children.find(c) == node->children.end()) {
                return {};
            }
            node = node->children[c];
        }

        std::vector<Movie*> moviePtrs = collectAllMovies(node, excludedGenres);

        // Contar coincidencias del prefijo en título y sinopsis
        for (auto *movie : moviePtrs) {
            movie->match_count = countOccurrences(toLower(movie->title), lowerPrefix) +
                                 countOccurrences(toLower(movie->plot_synopsis), lowerPrefix);
        }

        // Ordenar las películas por mayor número de coincidencias
        std::sort(moviePtrs.begin(), moviePtrs.end(),
                  [](Movie *a, Movie *b) {
                      return a->match_count > b->match_count;
                  });

        std::vector<Movie> movies;
        for (auto *movie : moviePtrs) {
            movies.push_back(*movie);
        }

        return movies;
    }

  private:
    void insertString(TrieNode *node, const std::string &str, const Movie &movie) {
        for (char c : str) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;
        node->movies.push_back(movie);
    }

    // Recolectar todas las películas excluyendo ciertos géneros
    std::vector<Movie*> collectAllMovies(TrieNode *node,
                                         const std::unordered_set<std::string> &excludedGenres) {
        std::vector<Movie*> result;

        for (auto &movie : node->movies) {
            bool exclude = false;
            for (const auto &tag : movie.tags) {
                if (excludedGenres.find(tag) != excludedGenres.end()) {
                    exclude = true;
                    break;
                }
            }
            if (!exclude) {
                result.push_back(&movie);
            }
        }

        for (auto &child : node->children) {
            std::vector<Movie*> childMovies = collectAllMovies(child.second, excludedGenres);
            result.insert(result.end(), childMovies.begin(), childMovies.end());
        }

        return result;
    }

    int countOccurrences(const std::string &text, const std::string &prefix) {
        int count = 0;
        size_t pos = text.find(prefix);
        while (pos != std::string::npos) {
            count++;
            pos = text.find(prefix, pos + 1);
        }
        return count;
    }

    void freeTrie(TrieNode *node) {
        if (!node) return;
        for (auto &child : node->children) {
            freeTrie(child.second);
        }
        delete node;
    }
};

#endif // TRIE_H
