#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <thread>
#include <mutex>

using namespace std;

struct Pelicula {
    string imdb_id;
    string title;
    string plot_synopsis;
    string tags;
    int relevancia = 0;
};

mutex mtx; // Para proteger acceso a los resultados compartidos

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
// Función para leer el CSV
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
        string basura;

        getline(ss, pelicula.imdb_id, ',');
        getline(ss, pelicula.title, ',');
        getline(ss, pelicula.plot_synopsis, ',');
        getline(ss, pelicula.tags, ',');
        getline(ss, basura, ','); // Ignorar columnas extra
        getline(ss, basura, ',');

        peliculas.push_back(pelicula);
    }

    file.close();
    return peliculas;
}

// Función de búsqueda paralela
void buscarEnBloque(vector<Pelicula>& peliculas, const string& palabra, vector<Pelicula>& resultados) {
    string palabra_normalizada = normalizarTexto(palabra);
    vector<Pelicula> temp_resultados;

    for (auto& pelicula : peliculas) {
        int relevancia = 0;
        string title_normalizado = normalizarTexto(pelicula.title);
        string synopsis_normalizado = normalizarTexto(pelicula.plot_synopsis);
        string tags_normalizado = normalizarTexto(pelicula.tags);

        if (title_normalizado.find(palabra_normalizada) != string::npos) {
            relevancia += 3;
        }
        if (tags_normalizado.find(palabra_normalizada) != string::npos) {
            relevancia += 2;
        }
        if (synopsis_normalizado.find(palabra_normalizada) != string::npos) {
            relevancia += 1;
        }

        if (relevancia > 0) {
            pelicula.relevancia = relevancia;
            temp_resultados.push_back(pelicula);
        }
    }

    // Bloqueo para insertar en el vector compartido
    lock_guard<mutex> lock(mtx);
    resultados.insert(resultados.end(), temp_resultados.begin(), temp_resultados.end());
}

// Función de búsqueda principal
vector<Pelicula> buscarPeliculas(vector<Pelicula>& peliculas, const string& palabra) {
    int num_threads = thread::hardware_concurrency(); // Obtener número de hilos disponibles
    int chunk_size = peliculas.size() / num_threads; // Dividir películas entre los hilos
    vector<Pelicula> resultados;
    vector<thread> threads;

    for (int i = 0; i < num_threads; i++) {
        int inicio = i * chunk_size;
        int fin = (i == num_threads - 1) ? peliculas.size() : (inicio + chunk_size);
        vector<Pelicula> sub_vector(peliculas.begin() + inicio, peliculas.begin() + fin);
        threads.push_back(thread(buscarEnBloque, ref(sub_vector), palabra, ref(resultados)));
    }

    for (auto& t : threads) {
        t.join(); // Esperar a que terminen todos los hilos
    }

    // Ordenar resultados por relevancia
    sort(resultados.begin(), resultados.end(), [](const Pelicula& a, const Pelicula& b) {
        return a.relevancia > b.relevancia;
    });

    return resultados;
}

// Función para mostrar películas con paginación
void mostrarPeliculas(const vector<Pelicula>& resultados) {
    if (resultados.empty()) {
        cout << "No se encontraron películas con la palabra proporcionada.\n";
        return;
    }

    int total = resultados.size();
    int pagina = 0;

    while (true) {
        int inicio = pagina * 5;
        int fin = min(inicio + 5, total);

        cout << "\nPelículas encontradas (página " << pagina + 1 << "):\n";
        for (int i = inicio; i < fin; i++) {
            cout << "\nTítulo: " << resultados[i].title
                 << "\nSinopsis: " << resultados[i].plot_synopsis
                 << "\nIMDB ID: " << resultados[i].imdb_id
                 << "\n[1] Like  |  [2] Ver más tarde"
                 << "\n--------------------------------------";
        }

        if (fin == total) {
            break; // No hay más películas para mostrar
        }

        cout << "\n[3] Ver más resultados  |  [0] Salir\n";
        int opcion;
        cin >> opcion;

        if (opcion == 3) {
            pagina++;
        } else {
            break;
        }
    }
}

int main() {
    string filename = "mpst_full_data.csv";
    vector<Pelicula> peliculas = readCSV(filename);

    string palabra;
    cout << "Introduce una palabra para buscar (título, sinopsis o tags): ";
    cin >> palabra;

    vector<Pelicula> resultados = buscarPeliculas(peliculas, palabra);
    mostrarPeliculas(resultados);

    return 0;
}
