#include "headers/miniPandas.h"
#include "headers/tree4.h"
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

// TODO : IMPLEMENTARLO CON LA INTERFACE QUE TENDRÁ EL PROGRAMA

int main() {
    CSVHandler pandas;
    Trie movieTrie;
    std::vector<std::vector<std::string>> data;
    data = pandas.readCSV("cleaned.csv");

    // empezar a usar la data limpia
    for (const auto &row : data) {
        if (row.size() >= 4) { // solo consideramos datos completos osea las
                               // columnas imdb_id, title, plot_synopsis y tags.
            Movie movie = {row[0], row[1], row[2]};
            std::vector<std::string> genres = pandas.split(row[3], ',');
            for (auto &genre : genres) {
                movie.tags.insert(toLower(genre));
            }
            movieTrie.insert(movie);
        }
    }
    // pedido de pelicula
    std::string search;
    std::cout << "Searching for: ";
    std::getline(std::cin, search);

    // pedido de los filtros
    std::unordered_set<std::string> activeFilters;
    std::string genreFilter;
    std::cout << "Ingrese los géneros activos separados por coma (ej. "
                 "Action,Adventure): ";
    std::getline(std::cin, genreFilter);
    std::vector<std::string> genres = pandas.split(genreFilter, ',');
    for (auto &g : genres) {
        activeFilters.insert(toLower(g));
    }

    std::vector<Movie> results = movieTrie.search(search, activeFilters);
    std::cout << "Results: " << std::endl;
    for (const auto &movie : results) {
        std::cout << "Title: " << movie.title << std::endl;
        std::cout << "IMDB ID: " << movie.imdb_id << std::endl;
        std::cout << "Importance: " << movie.match_count << std::endl;
        std::cout << "Tags: ";
        for (const auto &tag : movie.tags) {
            std::cout << tag << " ";
        }
        std::cout << std::endl;
        std::cout << "--------------------" << std::endl;
    }
    return 0;
}
