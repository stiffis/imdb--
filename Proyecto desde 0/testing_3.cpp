#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include <cctype>
#include <exception>
#include <regex>
#include <thread>  // Para utilizar hilos
#include <mutex>   // Para manejar el acceso concurrente a los resultados
#include <future>  // Para std::async y std::future

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

    // Constructor con parámetros
    Pelicula(string id, string t, string s, vector<string> e)
        : imdb_id(move(id)), titulo(move(t)), sinopsis(move(s)), etiquetas(move(e)) {}
};

class GestorPeliculas {
private:
    map<string, Pelicula> peliculas;  // Usamos un map para almacenar películas, clave es el imdb_id
    unordered_set<string> likes;
    vector<string> verMasTarde;
    vector<pair<string, Pelicula>> resultados;  // Almacena los resultados de la búsqueda
    mutex mtx;  // Mutex para acceso seguro a resultados compartidos

public:
    // Función para agregar una película
    void agregar_pelicula(const Pelicula& pelicula) {
        peliculas[pelicula.imdb_id] = pelicula;
    }

    // Función para agregar una película a los "Likes"
    void agregar_like(const string& imdb_id) {
        likes.insert(imdb_id);
        cout << "Pelicula con IMDB ID " << imdb_id << " agregada a Likes." << endl;
    }

    // Función para agregar una película a "Ver más tarde"
    void agregar_ver_mas_tarde(const string& imdb_id) {
        verMasTarde.push_back(imdb_id);
        cout << "Pelicula con IMDB ID " << imdb_id << " agregada a Ver Más Tarde." << endl;
    }

    // Función para mostrar las películas en "Likes"
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

    // Función para mostrar las películas en "Ver más tarde"
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

    // Función de búsqueda asincrónica con espera hasta obtener 5 resultados
    void buscar_pelicula(const string& termino) {
        bool encontrado = false;

        // Crear un patrón de expresión regular para buscar la palabra exacta
        string pattern = "\\b" + termino + "\\b";
        regex r(pattern, regex_constants::icase);

        // Iniciar búsqueda en segundo plano usando std::async
        auto future = async(launch::async, &GestorPeliculas::buscar_pelicula_worker, this, r);

        // Esperar a tener al menos 5 resultados o que termine la búsqueda
        while (resultados.size() < 5) {
            cout << "Buscando... (esperando al menos 5 resultados)\n";
           this_thread::sleep_for(chrono::milliseconds(500));  // Pausa corta para evitar consumo excesivo de CPU
        }

        // Ahora que tenemos 5 o más resultados, mostramos los primeros
        future.get();  // Esperar a que la búsqueda se complete

        // Mostrar los resultados
        size_t pagina = 0;
        size_t total_paginas = (resultados.size() + 4) / 5;  // Dividir en páginas de 5 resultados

        while (true) {
            size_t inicio = pagina * 5;
            size_t fin = min(inicio + 5, resultados.size());

            cout << "\nMostrando página " << pagina + 1 << " de " << total_paginas << endl;

            for (size_t i = inicio; i < fin; ++i) {
                cout << i + 1 << ". " << resultados[i].second.titulo << endl;
            }

            cout << "\nDesea ver más resultados? (Ingrese 'si' para mostrar, o el número de la opción que quiere ver, o 0 para salir): ";
            string respuesta;
            cin >> respuesta;

            if (respuesta == "0") {
                break;
            }

            if (respuesta == "si") {
                if (pagina + 1 < total_paginas) {
                    ++pagina;
                } else {
                    cout << "No hay más resultados." << endl;
                    break;
                }
            } else {
                int seleccion;
                try {
                    seleccion = stoi(respuesta);
                } catch (...) {
                    seleccion = -1;
                }

                if (seleccion >= 1 && seleccion <= resultados.size()) {
                    const auto& pelicula = resultados[seleccion - 1].second;
                    cout << "\nDetalles de la película:\n";
                    cout << "Título: " << pelicula.titulo << endl;
                    cout << "Sinopsis: " << pelicula.sinopsis << endl;
                    cout << "Etiquetas: ";
                    for (const auto& etiqueta : pelicula.etiquetas) {
                        cout << etiqueta << " ";
                    }
                    cout << endl;

                    cout << "\nOpciones: \n";
                    cout << "1. Agregar a Likes\n";
                    cout << "2. Agregar a Ver más tarde\n";
                    cout << "0. Volver a la lista\n";
                    int opcion_detalles;
                    cin >> opcion_detalles;

                    if (opcion_detalles == 1) {
                        agregar_like(resultados[seleccion - 1].first);
                    } else if (opcion_detalles == 2) {
                        agregar_ver_mas_tarde(resultados[seleccion - 1].first);
                    }
                } else {
                    cout << "Selección inválida. Intente nuevamente.\n";
                }
            }
        }
    }

    // Función que realiza la búsqueda de películas en segundo plano
    void buscar_pelicula_worker(const regex& r) {
        for (const auto& [id, pelicula] : peliculas) {
            if (regex_search(pelicula.titulo, r) || regex_search(pelicula.sinopsis, r)) {
                lock_guard<mutex> lock(mtx);  // Bloqueo para asegurar acceso seguro
                resultados.push_back({id, pelicula});
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
        }

        getline(archivo, linea);  // Saltar la primera línea de encabezado
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
        cout << "\n1. Ver peliculas en Ver Más Tarde" << endl;
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
            cout << "Ingrese el término de búsqueda: ";
            cin >> busqueda;
            gestor.buscar_pelicula(busqueda);
        }
    }

    return 0;
}
