#ifndef TRIE_H
#define TRIE_H

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Movie {
    std::string imdb_id;
    std::string title;
    std::string plot_synopsis;
    std::string genres;
    int match_count = 0; // Contador de las coincidencias con el prefijo
};

// Helper function to convert a string to lowercase
std::string to_Lower(const std::string &str) {
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

    // Insert a title, plot synopsis, and genres into the Trie
    void insert(const Movie &movie) {
        insertString(root, to_Lower(movie.title), movie);
        insertString(root, to_Lower(movie.plot_synopsis), movie);
    }

    // Search for movies with titles or plot synopses that start with the given prefix, optionally filtering by genre
    std::vector<Movie> search(const std::string &prefix, const std::string &genreFilter = "") {
        TrieNode *node = root;
        std::string lowerPrefix = to_Lower(prefix);
        for (char c : lowerPrefix) {
            if (node->children.find(c) == node->children.end()) {
                return {};
            }
            node = node->children[c];
        }
        std::vector<Movie> movies = collectAllMovies(node);

        // Contar cuántas veces aparece el prefijo en el título y sinopsis
        for (auto &movie : movies) {
            movie.match_count = countOccurrences(to_Lower(movie.title), lowerPrefix) +
                                countOccurrences(to_Lower(movie.plot_synopsis), lowerPrefix);
        }

        // Filtrar por género si se especifica
        if (!genreFilter.empty()) {
            std::string lowerGenreFilter = to_Lower(genreFilter);
            movies.erase(std::remove_if(movies.begin(), movies.end(), [&](const Movie &movie) {
                return movie.genres.find(lowerGenreFilter) == std::string::npos;
            }), movies.end());
        }

        // Ordenar por número de coincidencias (mayor a menor)
        std::sort(movies.begin(), movies.end(),
                  [](const Movie &a, const Movie &b) {
                      return a.match_count > b.match_count;
                  });

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

    std::vector<Movie> collectAllMovies(TrieNode *node) {
        std::vector<Movie> result;
        if (node->isEndOfWord) {
            result.insert(result.end(), node->movies.begin(), node->movies.end());
        }
        for (auto &child : node->children) {
            std::vector<Movie> childMovies = collectAllMovies(child.second);
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
