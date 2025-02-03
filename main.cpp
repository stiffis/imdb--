// Cómo organizar el algoritmo del proyecto
// Para cumplir con los requerimientos, usar un árbol de búsqueda optimizado para
// strings es clave.
// La estructura más adecuada es un Trie (Árbol de prefijos).

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <map>
#include <set>

using namespace std;

struct Pelicula {
    string imdb_id;
    string title;
    string plot_synopsis;
    string tags;
    string split;
    string synopsis_source;
};

// Función para eliminar tildes y convertir a minúsculas
string normalizarTexto(const string& texto) {
    string resultado = texto;
    transform(resultado.begin(), resultado.end(), resultado.begin(), ::tolower);

    unordered_map<char, char> tildes = {
        {'á', 'a'}, {'é', 'e'}, {'í', 'i'}, {'ó', 'o'}, {'ú', 'u'},
        {'Á', 'a'}, {'É', 'e'}, {'Í', 'i'}, {'Ó', 'o'}, {'Ú', 'u'}
    };

    for (char& c : resultado) {
        if (tildes.count(c)) {
            c = tildes[c];
        }
    }
    
    return resultado;
}

// Función para leer CSV y cargar datos
vector<Pelicula> readCSV(const string& filename) {
    vector<Pelicula> peliculas;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo " << filename << endl;
        return peliculas;
    }

    string line;
    getline(file, line); // Saltar encabezado

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

// Función de búsqueda mejorada
vector<Pelicula> buscarPeliculas(const vector<Pelicula>& peliculas, const string& palabra) {
    vector<Pelicula> resultados;
    string palabra_normalizada = normalizarTexto(palabra);

    for (const auto& pelicula : peliculas) {
        string title_normalizado = normalizarTexto(pelicula.title);
        string synopsis_normalizado = normalizarTexto(pelicula.plot_synopsis);

        if (title_normalizado.find(palabra_normalizada) != string::npos ||
            synopsis_normalizado.find(palabra_normalizada) != string::npos) {
            resultados.push_back(pelicula);
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
        cout << "\nPelículas encontradas:\n";
        for (const auto& pelicula : resultados) {
            cout << "IMDB ID: " << pelicula.imdb_id
                 << ", Title: " << pelicula.title
                 << ", Plot Synopsis: " << pelicula.plot_synopsis
                 << "\n--------------------------------------\n";
        }
    } else {
        cout << "No se encontraron películas con la palabra proporcionada.\n";
    }

    return 0;
}

