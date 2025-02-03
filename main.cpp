#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Pelicula {
    string imdb_id;
    string title;
    string plot_synopsis;
    string tags;
    string split;
    string synopsis_source;
};

vector<Pelicula> readCSV(const string& filename) {
    vector<Pelicula> peliculas;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo " << filename << endl;
        return peliculas;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        Pelicula pelicula;

        getline(ss, pelicula.imdb_id, ',');
        getline(ss, pelicula.title, ',');
        getline(ss, pelicula.plot_synopsis, ',');
        getline(ss, pelicula.tags, ',');
        getline(ss, pelicula.split, ',');
        getline(ss, pelicula.synopsis_source, ',');

        peliculas.push_back(pelicula);
    }

    file.close();
    return peliculas;
}

vector<Pelicula> buscarPeliculas(const vector<Pelicula>& peliculas, const string& palabra) {
    vector<Pelicula> resultados;
    string palabra_lower = palabra;
    transform(palabra_lower.begin(), palabra_lower.end(), palabra_lower.begin(), ::tolower);

    for (const auto& pelicula : peliculas) {
        string title_lower = pelicula.title;
        transform(title_lower.begin(), title_lower.end(), title_lower.begin(), ::tolower);

        unordered_set<string::size_type> posiciones;

        if (palabra.size() <= 2) {
            string::size_type pos = title_lower.find(palabra_lower);
            while (pos != string::npos) {
                if (posiciones.find(pos) == posiciones.end()) {
                    posiciones.insert(pos);
                    resultados.push_back(pelicula);
                    break;
                }
                pos = title_lower.find(palabra_lower, pos + 1);
            }
        } else {
            string::size_type pos = title_lower.find(palabra_lower);
            if (pos != string::npos) {
                resultados.push_back(pelicula);
            }
        }
    }

    return resultados;
}

int main() {
    string filename = "mpst_full_data.csv";
    vector<Pelicula> peliculas = readCSV(filename);

    string palabra;
    cout << "Introduce una palabra para buscar: ";
    cin >> palabra;

    vector<Pelicula> resultados = buscarPeliculas(peliculas, palabra);

    if (!resultados.empty()) {
        cout << "Peliculas encontradas: " << endl;
        for (const auto& pelicula : resultados) {
            cout << "IMDB ID: " << pelicula.imdb_id
                  << ", Title: " << pelicula.title
                  << ", Plot Synopsis: " << pelicula.plot_synopsis
                  << ", Tags: " << pelicula.tags
                  << ", Split: " << pelicula.split
                  << ", Synopsis Source: " << pelicula.synopsis_source
                  << endl;
        }
    } else {
        cout << "No se encontraron películas que coincidan con la palabra proporcionada." << endl;
    }

    return 0;
}
