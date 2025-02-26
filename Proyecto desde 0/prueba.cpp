#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include <cctype>
#include <exception> // manejo de lecturas invalidas del archivo
#include <regex> // Incluir la librería para expresiones regulares
#include <threads> // paralelizar la busqueda
#include <mutex>

using namespace std;

namespace Utilidades {
    string normalizar_texto(const string &texto) {
        string resultado;
        for (char c : texto) {
            if (isalnum(c) || isspace(c)) {
                resultado += tolower(c);
            }
        }
        return resultado;
    }

    vector<string> dividir(const string &cadena, char delimitador) {
        vector<string> tokens;
        stringstream ss(cadena);
        string token;
        while (getline(ss, token, delimitador)) {
            tokens.push_back(normalizar_texto(token));
        }
        return tokens;
    }
}

class Pelicula {
public:
    string imdb_id;
    string titulo;
    string sinopsis;
    vector<string> etiquetas;

    // Constructor por defecto
    Pelicula() : imdb_id(""), titulo(""), sinopsis(""), etiquetas() {}

    // Constructor con parámetros
    Pelicula(string id, string t, string s, vector<string> e)
        : imdb_id(move(id)), titulo(move(t)), sinopsis(move(s)), etiquetas(move(e)) {}
};

class GestorPeliculas {
private:
    map<string, Pelicula> peliculas; // Usamos un map para almacenar películas, clave es el imdb_id
    unordered_set<string> likes;
    vector<string> verMasTarde;

    vector<pair<string, Pelicula>> resultados;  // Resultados de la búsqueda
    mutex mtx;  // Mutex para proteger el acceso a los resultados


public:
    void agregar_pelicula(const Pelicula& pelicula) {
        peliculas[pelicula.imdb_id] = pelicula;
    }

    void agregar_like(const string& imdb_id) {
        likes.insert(imdb_id);
        cout << "Pelicula con IMDB ID " << imdb_id << " agregada a Likes." << endl;
    }

    void agregar_ver_mas_tarde(const string& imdb_id) {
        verMasTarde.push_back(imdb_id);
        cout << "Pelicula con IMDB ID " << imdb_id << " agregada a Ver Más Tarde." << endl;
    }

    void mostrar_likes() {
        if (likes.empty()) {
            cout << "No tienes peliculas en Likes." << endl;
        } else {
            cout << "Peliculas en Likes:" << endl;
            for (const auto& imdb_id : likes) {
                cout << "- " << peliculas[imdb_id].titulo << " (IMDB ID: " << imdb_id << ")" << endl;
            }
        }
    }

    void mostrar_ver_mas_tarde() {
        if (verMasTarde.empty()) {
            cout << "No tienes peliculas en Ver Más Tarde." << endl;
        } else {
            cout << "Peliculas en Ver Más Tarde:" << endl;
            for (const auto& imdb_id : verMasTarde) {
                cout << "- " << peliculas[imdb_id].titulo << " (IMDB ID: " << imdb_id << ")" << endl;
            }
        }
    }

    void buscar_pelicula(const string& termino) {
        bool encontrado = false;

        // Crear un patrón de expresión regular para buscar la palabra exacta, no una subcadena
        string pattern = "\\b" + termino + "\\b"; // \b asegura que sea una palabra completa
        regex r(pattern, regex_constants::icase); // Ignorar mayúsculas/minúsculas

        vector<pair<string, Pelicula>> resultados;

        // Buscar las películas que coincidan
        for (const auto& [id, pelicula] : peliculas) {
            if (regex_search(pelicula.titulo, r) || regex_search(pelicula.sinopsis, r)) {
                resultados.push_back({id, pelicula});
            }
        }

        // Si no se encontraron resultados
        if (resultados.empty()) {
            cout << "No se encontraron peliculas con el término: " << termino << endl;
            return;
        } else {
            cout << "Se encontraron " << resultados.size() <<"peliculas"<<endl;
        }

        // Mostrar los resultados de 6 en 6
        size_t pagina = 0;
        size_t total_paginas = (resultados.size() + 5) / 6;

        while (true) {
            cout << "\nMostrando página " << pagina + 1 << " de " << total_paginas << endl;

            // Mostrar hasta 6 resultados
            size_t inicio = pagina * 6;
            size_t fin = min(inicio + 6, resultados.size());

            for (size_t i = inicio; i < fin; ++i) {
                const auto& pelicula = resultados[i].second;
                cout << "Titulo: " << pelicula.titulo << " (IMDB ID: " << resultados[i].first << ")" << endl;
                cout << "Sinopsis: " << pelicula.sinopsis << endl;
                cout << "Etiquetas: ";
                for (const auto& etiqueta : pelicula.etiquetas) {
                    cout << etiqueta << " ";
                }
                cout << endl << "---------------------------" << endl;
            }

            // Preguntar al usuario si quiere ver más
            cout << "\n6. Página siguiente" << endl;
            cout << "7. Página anterior" << endl;
            cout << "0. Volver al menú principal" << endl;
            cout << "Seleccione una opción: ";
            int seleccion;
            cin >> seleccion;

            if (seleccion == 0) break;
            if (seleccion == 6 && pagina + 1 < total_paginas) {
                ++pagina;
            } else if (seleccion == 7 && pagina > 0) {
                --pagina;
            } else {
                cout << "Opción inválida." << endl;
            }
        }
    }
};

class CargadorCSV {
public:
    static vector<Pelicula> cargar_csv(const string& nombre_archivo) {
        ifstream archivo(nombre_archivo);
        vector<Pelicula> peliculas;
        string linea;

        if (!archivo.is_open()) {
            cerr << "Error: No se pudo abrir el archivo. Saldremos del programa" << endl;
            terminate();
            // return peliculas;
        }

        getline(archivo, linea);  // Saltar la primera línea de encabezado
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string imdb_id, titulo, sinopsis, etiquetas;

            getline(ss, imdb_id, ',');
            getline(ss, titulo, ',');
            getline(ss, sinopsis, ',');
            getline(ss, etiquetas, ',');

            vector<string> etiquetas_procesadas = Utilidades::dividir(etiquetas, ',');
            Pelicula pelicula(imdb_id, Utilidades::normalizar_texto(titulo),
                              Utilidades::normalizar_texto(sinopsis), etiquetas_procesadas);

            peliculas.push_back(pelicula);
        }

        archivo.close();
        return peliculas;
    }
};

int main() {
    string nombre_archivo = "cleaned_data.csv";
    GestorPeliculas gestor;

    // Cargar peliculas
    vector<Pelicula> peliculas = CargadorCSV::cargar_csv(nombre_archivo);
    for (const auto& pelicula : peliculas) {
        gestor.agregar_pelicula(pelicula);
    }

    int opcion;
    while (true) {
        cout << "\n1. Ver peliculas en Ver Más Tarde" << endl;
        cout << "2. Ver peliculas Likeadas" << endl;
        cout << "3. Buscar peliculas" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 0) break;

        if (opcion == 1) {
            gestor.mostrar_ver_mas_tarde();
        } else if (opcion == 2) {
            gestor.mostrar_likes();
        } else if (opcion == 3) {
            string busqueda;
            cout << "Ingrese el término de búsqueda: ";
            cin >> busqueda;
            gestor.buscar_pelicula(busqueda);
        }
    }

    return 0;
}