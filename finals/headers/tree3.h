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
    int match_count = 0; // contador de las coincidencias con el prefijo
    std::unordered_set<std::string> tags;
};

// Helper function to convert a string to lowercase
std::string toLower(const std::string &str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   ::tolower);
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

    // Insert a title and plot synopsis into the Trie
    void insert(const Movie &movie) {
        insertString(root, toLower(movie.title), movie);
        insertString(root, toLower(movie.plot_synopsis), movie);
    }

    // Search for movies with titles or plot synopses that start with the given
    // prefix
    std::vector<Movie>
    search(const std::string &prefix,
           const std::unordered_set<std::string> &activeFilters) {
        TrieNode *node = root;
        std::string lowerPrefix = toLower(prefix);
        for (char c : lowerPrefix) {
            if (node->children.find(c) == node->children.end()) {
                return {};
            }
            node = node->children[c];
        }
        std::vector<Movie> movies = collectAllMovies(node, activeFilters);

        // Contar cuántas veces aparece el prefijo en el título y sinopsis
        for (auto &movie : movies) {
            movie.match_count =
                countOccurrences(toLower(movie.title), lowerPrefix) +
                countOccurrences(toLower(movie.plot_synopsis), lowerPrefix);
        }

        // Ordenar por número de coincidencias (mayor a menor)
        std::sort(movies.begin(), movies.end(),
                  [](const Movie &a, const Movie &b) {
                      return a.match_count > b.match_count;
                  });

        return movies;
    }

  private:
    void insertString(TrieNode *node, const std::string &str,
                      const Movie &movie) {
        for (char c : str) {
            if (node->children.find(c) == node->children.end()) {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;
        node->movies.push_back(movie);
    }

    std::vector<Movie>
    collectAllMovies(TrieNode *node,
                     const std::unordered_set<std::string> &active_genres) {
        std::vector<Movie> result;
        if (node->isEndOfWord) {
            for (const auto &movie : node->movies) {
                for (const auto &tag : movie.tags) {
                    if (active_genres.find(tag) != active_genres.end()) {
                        result.push_back(movie);
                        break;
                    }
                }
            }
        }
        for (auto &child : node->children) {
            std::vector<Movie> childMovies =
                collectAllMovies(child.second, active_genres);
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
};

#endif // TRIE_H
