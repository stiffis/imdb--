#include "miniPandas.h"
#include "treeF.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
    CSVHandler pandas;
    Trie movieTrie;
    std::vector<std::vector<std::string>> data;
    data = pandas.readCSV("/home/stiff/PRO/profavorfin/fin/fin2/cleaned_data.csv");
    
    // Empezar a usar la data limpia
    for (const auto &row : data) {
        if (row.size() >= 5) { // Consideramos datos completos, incluyendo géneros
            Movie movie = {row[0], row[1], row[2], row[3]}; // Se asume que la columna de géneros es la cuarta
            movieTrie.insert(movie);
        }
    }

    std::string search;
    std::cout << "Searching for: ";
    std::getline(std::cin, search);
    
    std::string genreFilter;
    std::cout << "Filter by genre (leave empty to skip): ";
    std::getline(std::cin, genreFilter);

    std::vector<Movie> results = movieTrie.search(search, genreFilter);
    std::cout << "Results: " << std::endl;
    for (const auto &movie : results) {
        std::cout << "Title: " << movie.title << std::endl;
        std::cout << "IMDB ID: " << movie.imdb_id << std::endl;
        std::cout << "Genres: " << movie.genres << std::endl;
        std::cout << "Importance: " << movie.match_count << std::endl;
        std::cout << "--------------------" << std::endl;
    }
    return 0;
}
