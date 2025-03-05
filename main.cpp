#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

void printBox(const string &text) {
    int len = 0;
    vector<string> lines;
    stringstream ss(text);
    string line;
    while (getline(ss, line, '\n')) {
        lines.push_back(line);
        if (line.size() > len)
            len = line.size();
    }
    string border(len + 4, '-');
    cout << border << "\n";
    for (auto &l : lines) {
        cout << "| " << l;
        cout << string(len - l.size(), ' ') << " |\n";
    }
    cout << border << "\n";
}

int countOccurrences(const string &text, const string &word) {
    int count = 0;
    stringstream ss(text);
    string token;
    while (ss >> token) {
        if (token == word)
            count++;
    }
    return count;
}

string normalizar_texto(const string &texto) {
    string resultado;
    for (char c : texto) {
        c = tolower(c);
        if (isalnum(c) || isspace(c))
            resultado.push_back(c);
    }
    return resultado;
}

vector<string> dividir(const string &cadena, char delimitador) {
    vector<string> tokens;
    stringstream ss(cadena);
    string token;
    while (getline(ss, token, delimitador))
        tokens.push_back(normalizar_texto(token));
    return tokens;
}

class TrieNode {
  public:
    unordered_map<char, TrieNode *> children;
    unordered_set<string> movieIds;
    bool isEndOfWord;
    TrieNode() : isEndOfWord(false) {}
};

class Trie {
  private:
    TrieNode *root;

  public:
    Trie() { root = new TrieNode(); }
    ~Trie() {}
    void insert(const string &word, const string &movieId) {
        TrieNode *node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end())
                node->children[c] = new TrieNode();
            node = node->children[c];
        }
        node->isEndOfWord = true;
        node->movieIds.insert(movieId);
    }
    unordered_set<string> search(const string &word) {
        TrieNode *node = root;
        for (char c : word) {
            if (node->children.find(c) == node->children.end())
                return unordered_set<string>();
            node = node->children[c];
        }
        return (node->isEndOfWord) ? node->movieIds : unordered_set<string>();
    }
};

class Pelicula {
  public:
    string imdb_id;
    string titulo;
    string sinopsis;
    vector<string> etiquetas;
    Pelicula() : imdb_id(""), titulo(""), sinopsis(""), etiquetas() {}
    Pelicula(string id, string t, string s, vector<string> e)
        : imdb_id(std::move(id)), titulo(std::move(t)), sinopsis(std::move(s)),
          etiquetas(std::move(e)) {}
};

class MovieDisplay {
  public:
    virtual void display(const Pelicula &p) = 0;
    virtual ~MovieDisplay() {}
};

class BasicMovieDisplay : public MovieDisplay {
  public:
    void display(const Pelicula &p) override {
        cout << "\n=== Detalles de la Pelicula ===\n";
        cout << "Titulo: " << p.titulo << "\n";
        cout << "Sinopsis: " << p.sinopsis << "\n";
        cout << "Etiquetas: ";
        if (p.etiquetas.empty())
            cout << "Sin generos";
        else {
            for (const auto &et : p.etiquetas)
                cout << et << " ";
        }
        cout << "\n============================\n";
    }
};

class MovieDisplayDecorator : public MovieDisplay {
  protected:
    MovieDisplay *wrapped;

  public:
    MovieDisplayDecorator(MovieDisplay *m) : wrapped(m) {}
    virtual ~MovieDisplayDecorator() { delete wrapped; }
    void display(const Pelicula &p) override { wrapped->display(p); }
};

class ExtendedMovieDisplay : public MovieDisplayDecorator {
  public:
    ExtendedMovieDisplay(MovieDisplay *m) : MovieDisplayDecorator(m) {}
    void display(const Pelicula &p) override {
        MovieDisplayDecorator::display(p);
        cout << "IMDB ID: " << p.imdb_id << "\n";
    }
};

class Memento {
  public:
    vector<string> likes;
    vector<string> verMasTarde;
    vector<string> historial;
    vector<pair<string, Pelicula>> resultados;
    Memento(const vector<string> &likes, const vector<string> &verMasTarde,
            const vector<string> &historial,
            const vector<pair<string, Pelicula>> &resultados)
        : likes(likes), verMasTarde(verMasTarde), historial(historial),
          resultados(resultados) {}
};

class GestorPeliculas {
  private:
    map<string, Pelicula> peliculas;
    unordered_set<string> likes;
    vector<string> verMasTarde;
    vector<pair<string, Pelicula>> resultados;
    vector<string> historial;
    Trie trie;

    const string likesFile = "likes.txt";
    const string verMasTardeFile = "ver_mas_tarde.txt";
    const string historialFile = "historial.txt";

    void guardar_lista(const string &filename, const vector<string> &lista) {
        ofstream file(filename, ios::out | ios::trunc);
        for (const auto &item : lista)
            file << item << "\n";
        file.close();
    }

    void guardar_conjunto(const string &filename,
                          const unordered_set<string> &conjunto) {
        ofstream file(filename, ios::out | ios::trunc);
        for (const auto &item : conjunto)
            file << item << "\n";
        file.close();
    }

    vector<string> cargar_lista(const string &filename) {
        vector<string> lista;
        ifstream file(filename);
        string line;
        while (getline(file, line))
            lista.push_back(line);
        file.close();
        return lista;
    }

    unordered_set<string> cargar_conjunto(const string &filename) {
        unordered_set<string> conjunto;
        ifstream file(filename);
        string line;
        while (getline(file, line))
            conjunto.insert(line);
        file.close();
        return conjunto;
    }

  public:
    static GestorPeliculas &getInstance() {
        static GestorPeliculas instance;
        return instance;
    }

    void cargar_datos() {
        if (filesystem::exists(likesFile))
            likes = cargar_conjunto(likesFile);
        if (filesystem::exists(verMasTardeFile))
            verMasTarde = cargar_lista(verMasTardeFile);
        if (filesystem::exists(historialFile))
            historial = cargar_lista(historialFile);
    }

    void guardar_datos() {
        guardar_conjunto(likesFile, likes);
        guardar_lista(verMasTardeFile, verMasTarde);
        guardar_lista(historialFile, historial);
    }

    Memento *createMemento() {
        return new Memento({likes.begin(), likes.end()}, verMasTarde, historial,
                           resultados);
    }

    void restoreMemento(Memento *memento) {
        likes =
            unordered_set<string>(memento->likes.begin(), memento->likes.end());
        verMasTarde = memento->verMasTarde;
        historial = memento->historial;
        resultados = memento->resultados;
    }

    void agregar_pelicula(const Pelicula &pelicula) {
        peliculas[pelicula.imdb_id] = pelicula;
        vector<string> palabrasTitulo = dividir(pelicula.titulo, ' ');
        for (const auto &palabra : palabrasTitulo)
            if (!palabra.empty())
                trie.insert(palabra, pelicula.imdb_id);
        vector<string> palabrasSinopsis = dividir(pelicula.sinopsis, ' ');
        for (const auto &palabra : palabrasSinopsis)
            if (!palabra.empty())
                trie.insert(palabra, pelicula.imdb_id);
    }

    void agregar_like(const string &imdb_id) {
        likes.insert(imdb_id);
        guardar_conjunto(likesFile, likes);
        cout << "Pelicula con IMDB ID " << imdb_id << " agregada a Likes."
             << endl;
    }

    void agregar_ver_mas_tarde(const string &imdb_id) {
        verMasTarde.push_back(imdb_id);
        guardar_lista(verMasTardeFile, verMasTarde);
        cout << "Pelicula con IMDB ID " << imdb_id
             << " agregada a Ver Mas Tarde." << endl;
    }

    void mostrar_likes() {
        if (likes.empty())
            cout << "No tienes peliculas en Likes." << endl;
        else {
            cout << "Peliculas en Likes:" << endl;
            for (const auto &id : likes)
                cout << "- " << peliculas[id].titulo << " (IMDB ID: " << id
                     << ")" << endl;
        }
    }

    void mostrar_ver_mas_tarde() {
        if (verMasTarde.empty())
            cout << "No tienes peliculas en Ver Mas Tarde." << endl;
        else {
            cout << "Peliculas en Ver Mas Tarde:" << endl;
            for (const auto &id : verMasTarde)
                cout << "- " << peliculas[id].titulo << " (IMDB ID: " << id
                     << ")" << endl;
        }
    }

    void mostrar_historial() {
        if (historial.empty())
            cout << "No hay historial de busquedas." << endl;
        else {
            cout << "Historial de busquedas:" << endl;
            for (const auto &busqueda : historial)
                cout << "- " << busqueda << endl;
        }
    }

    void buscar_pelicula(const string &termino) {
        resultados.clear();
        historial.push_back(termino);
        guardar_lista(historialFile, historial);
        vector<string> palabras = dividir(termino, ' ');
        unordered_set<string> interseccion;
        bool first = true;
        vector<pair<string, Pelicula>> resultadosTitulo;
        vector<pair<string, Pelicula>> resultadosOtros;
        for (const auto &palabra : palabras) {
            unordered_set<string> ids = trie.search(palabra);
            if (first) {
                interseccion = ids;
                first = false;
            } else {
                unordered_set<string> temp;
                for (const auto &id : interseccion)
                    if (ids.find(id) != ids.end())
                        temp.insert(id);
                interseccion = temp;
            }
        }
        for (const auto &id : interseccion) {
            if (peliculas.find(id) != peliculas.end()) {
                const auto &p = peliculas.at(id);
                bool encontradoEnTitulo = false;
                for (const auto &palabra : palabras) {
                    if (normalizar_texto(p.titulo).find(palabra) !=
                        string::npos) {
                        encontradoEnTitulo = true;
                        break;
                    }
                }
                if (encontradoEnTitulo)
                    resultadosTitulo.push_back({id, p});
                else
                    resultadosOtros.push_back({id, p});
            }
        }
        resultados.insert(resultados.end(), resultadosTitulo.begin(),
                          resultadosTitulo.end());
        resultados.insert(resultados.end(), resultadosOtros.begin(),
                          resultadosOtros.end());
        if (resultados.empty()) {
            cout << "No se encontraron resultados para '" << termino << "'."
                 << endl;
            return;
        }
        printBox("Desea filtrar los resultados por genero? (s/n): ");
        string respGenero;
        cin >> respGenero;
        vector<vector<pair<string, Pelicula>>> stackFiltros;
        if (respGenero == "s" || respGenero == "si") {
            printBox("Ingrese el genero: ");
            string genero;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, genero);
            genero = normalizar_texto(genero);
            vector<pair<string, Pelicula>> resultadosGenero;
            for (const auto &res : resultados) {
                bool enc = false;
                for (const auto &tag : res.second.etiquetas) {
                    if (tag.find(genero) != string::npos) {
                        enc = true;
                        break;
                    }
                }
                if (enc)
                    resultadosGenero.push_back(res);
            }
            if (resultadosGenero.empty()) {
                cout << "No se encontraron peliculas para el genero '" << genero
                     << "'." << endl;
                return;
            }
            stackFiltros.push_back(resultados);
            resultados = resultadosGenero;
        }
        size_t pagina = 0;
        size_t total_paginas = (resultados.size() + 4) / 5;
        while (true) {
            size_t inicio = pagina * 5;
            size_t fin = min(inicio + 5, resultados.size());
            cout << "\nMostrando pagina " << pagina + 1 << " de "
                 << total_paginas << endl;
            for (size_t i = inicio; i < fin; ++i)
                cout << i + 1 << ". " << resultados[i].second.titulo << endl;
            printBox(
                "Opciones:\n'si' PARA SIGUIENTE PAGINA\n'g' PARA FILTRAR POR "
                "GENERO\n'r' PARA REMOVER EL ULTIMO FILTRO\n '0' PARA SALIR:");
            string respuesta;
            cin >> respuesta;
            if (respuesta == "0")
                break;
            else if (respuesta == "si") {
                if (++pagina >= total_paginas) {
                    cout << "No hay mas resultados." << endl;
                    break;
                }
            } else if (respuesta == "g") {
                printBox("Ingrese el genero para filtrar: ");
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string nuevoGenero;
                getline(cin, nuevoGenero);
                nuevoGenero = normalizar_texto(nuevoGenero);
                vector<pair<string, Pelicula>> nuevosResultados;
                for (const auto &res : resultados) {
                    bool enc = false;
                    for (const auto &tag : res.second.etiquetas) {
                        if (tag.find(nuevoGenero) != string::npos) {
                            enc = true;
                            break;
                        }
                    }
                    if (enc)
                        nuevosResultados.push_back(res);
                }
                if (nuevosResultados.empty()) {
                    cout << "No se encontraron peliculas para el genero '"
                         << nuevoGenero << "'." << endl;
                } else {
                    stackFiltros.push_back(resultados);
                    resultados = nuevosResultados;
                    total_paginas = (resultados.size() + 4) / 5;
                    pagina = 0;
                    cout << "Filtrado aplicado. Mostrando nueva lista de "
                            "resultados:"
                         << endl;
                }
            } else if (respuesta == "r") {
                if (!stackFiltros.empty()) {
                    resultados = stackFiltros.back();
                    stackFiltros.pop_back();
                    total_paginas = (resultados.size() + 4) / 5;
                    pagina = 0;
                    cout << "Ultimo filtro removido. Mostrando resultados "
                            "actualizados:"
                         << endl;
                } else {
                    cout << "No hay filtros para remover." << endl;
                }
            } else {
                int seleccion = stoi(respuesta);
                if (seleccion >= 1 &&
                    seleccion <= static_cast<int>(resultados.size())) {
                    const auto &p = resultados[seleccion - 1].second;
                    MovieDisplay *display =
                        new ExtendedMovieDisplay(new BasicMovieDisplay());
                    display->display(p);
                    delete display;
                    string combined = p.titulo + " " + p.sinopsis;
                    cout << "\nFrecuencia de palabras encontradas:" << endl;
                    for (const auto &w : palabras) {
                        int freq = countOccurrences(combined, w);
                        cout << w << ": " << freq << endl;
                    }
                    printBox("DESEA DARLE LIKE (1)\nDESEA VERLO MAS TARDE "
                             "(2)?\nDESEA OMITIR (0)");
                    int opcionAccion;
                    cin >> opcionAccion;
                    if (opcionAccion == 1)
                        agregar_like(p.imdb_id);
                    else if (opcionAccion == 2)
                        agregar_ver_mas_tarde(p.imdb_id);
                } else
                    cout << "Seleccion invalida. Intente nuevamente." << endl;
            }
        }
    }
};

class CargadorCSV {
  public:
    static vector<Pelicula> cargar_csv(const string &nombre_archivo) {
        ifstream archivo(nombre_archivo);
        vector<Pelicula> peliculas;
        string linea;
        if (!archivo.is_open()) {
            cerr << "Error: No se pudo abrir el archivo. Saldremos del programa"
                 << endl;
            terminate();
        }
        getline(archivo, linea);
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string imdb_id, titulo, sinopsis, etiquetas;
            getline(ss, imdb_id, ',');
            getline(ss, titulo, ',');
            getline(ss, sinopsis, ',');
            getline(ss, etiquetas, ',');
            vector<string> etiquetas_procesadas = dividir(etiquetas, ',');
            Pelicula pelicula(imdb_id, normalizar_texto(titulo),
                              normalizar_texto(sinopsis), etiquetas_procesadas);
            peliculas.push_back(pelicula);
        }
        archivo.close();
        return peliculas;
    }
};
int main() {
    string nombre_archivo = "cleaned_data.csv";
    GestorPeliculas &gestor = GestorPeliculas::getInstance();
    gestor.cargar_datos();

    thread cargadorThread(
        [](const string &archivo, GestorPeliculas &gestor) {
            vector<Pelicula> peliculas = CargadorCSV::cargar_csv(archivo);
            for (const auto &pelicula : peliculas)
                gestor.agregar_pelicula(pelicula);
        },
        nombre_archivo, ref(gestor));

    cargadorThread.join();

    gestor.mostrar_likes();
    gestor.mostrar_ver_mas_tarde();

    vector<Memento *> mementos;
    int opcion;
    while (true) {
        cout << "\n=== Menu Principal ===" << endl;
        cout << "1. Ver peliculas en Ver Mas Tarde" << endl;
        cout << "2. Ver peliculas Likeadas" << endl;
        cout << "3. Buscar peliculas" << endl;
        cout << "4. Ver historial de busquedas" << endl;
        cout << "5. Guardar estado" << endl;
        cout << "6. Restaurar estado" << endl;
        cout << "0. Salir" << endl;
        printBox("Seleccione una opcion:");
        cin >> opcion;
        if (opcion == 0)
            break;
        if (opcion == 1)
            gestor.mostrar_ver_mas_tarde();
        else if (opcion == 2)
            gestor.mostrar_likes();
        else if (opcion == 3) {
            printBox("Ingrese el termino de busqueda:");
            string busqueda;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, busqueda);
            gestor.buscar_pelicula(normalizar_texto(busqueda));
        } else if (opcion == 4) {
            gestor.mostrar_historial();
        } else if (opcion == 5) {
            mementos.push_back(gestor.createMemento());
            cout << "Estado guardado." << endl;
        } else if (opcion == 6) {
            if (mementos.empty())
                cout << "No hay estados guardados." << endl;
            else {
                gestor.restoreMemento(mementos.back());
                mementos.pop_back();
                cout << "Estado restaurado." << endl;
            }
        }
    }
    gestor.guardar_datos();
    return 0;
}
