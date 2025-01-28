// Cómo organizar el algoritmo del proyecto
// Para cumplir con los requerimientos, usar un árbol de búsqueda optimizado para
// strings es clave.
// La estructura más adecuada es un Trie (Árbol de prefijos).


#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Propuesta para la lectura y carga de peliculas
void cargarPeliculas(const  string& archivo,  vector<Pelicula>& peliculas, Trie& trie) {
     ifstream archivoEntrada(archivo);
     string linea;

    if (!archivoEntrada.is_open()) {
         cerr << "No se pudo abrir el archivo." <<  endl;
        return;
    }

     getline(archivoEntrada, linea); // Leer encabezado

    while ( getline(archivoEntrada, linea)) {
         stringstream ss(linea);
        Pelicula pelicula;

         getline(ss, pelicula.imdb_id, ',');
         getline(ss, pelicula.titulo, ',');
         getline(ss, pelicula.sinopsis, ',');
         string tags;
         getline(ss, tags, ','); // Etiquetas como string
        pelicula.tags = dividir(tags, '|'); // Suponiendo que las etiquetas están separadas por '|'

        peliculas.push_back(pelicula);

        // Indexar en el Trie
        for (const  string& palabra : dividirEnPalabras(pelicula.titulo)) {
            trie.insertar(palabra, pelicula.imdb_id);
        }
        for (const  string& palabra : dividirEnPalabras(pelicula.sinopsis)) {
            trie.insertar(palabra, pelicula.imdb_id);
        }
        for (const  string& tag : pelicula.tags) {
            trie.insertar(tag, pelicula.imdb_id);
        }
    }
}

 vector< string> dividirEnPalabras(const  string& texto) {
     istringstream ss(texto);
     vector< string> palabras;
     string palabra;
    while (ss >> palabra) {
        palabras.push_back(palabra);
    }
    return palabras;
}


struct Pelicula {
     string imdb_id;
     string titulo;
     string sinopsis;
     vector< string> tags;
};

class Trie {
    struct Nodo {
         unordered_map<char, Nodo*> hijos;
         vector< string> peliculas; // IDs de películas
        bool esPalabra = false;
    };

    Nodo* raiz;

public:
    Trie() { raiz = new Nodo(); }

    void insertar(const  string& palabra, const  string& pelicula_id) {
        Nodo* actual = raiz;
        for (char c : palabra) {
            if (!actual->hijos[c]) {
                actual->hijos[c] = new Nodo();
            }
            actual = actual->hijos[c];
        }
        actual->esPalabra = true;
        actual->peliculas.push_back(pelicula_id);
    }

     vector< string> buscar(const  string& prefijo) {
        Nodo* actual = raiz;
        for (char c : prefijo) {
            if (!actual->hijos[c]) return {}; // No hay coincidencias
            actual = actual->hijos[c];
        }
        return recolectarPeliculas(actual);
    }

private:
     vector< string> recolectarPeliculas(Nodo* nodo) {
         vector< string> resultados;
        if (nodo->esPalabra) {
            resultados.insert(resultados.end(), nodo->peliculas.begin(), nodo->peliculas.end());
        }
        for (auto& hijo : nodo->hijos) {
            auto subresultados = recolectarPeliculas(hijo.second);
            resultados.insert(resultados.end(), subresultados.begin(), subresultados.end());
        }
        return resultados;
    }
};
