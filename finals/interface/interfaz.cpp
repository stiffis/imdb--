#include <ncurses.h>
#include <string>
#include <vector>
struct Filter {
    Filter(const std::string _t) : name(_t) {}
    std::string name;
    int status;
};
// Función para inicializar ncurses
void init_ncurses(int &rows, int &cols) {
    setlocale(LC_ALL, ""); // Habilitar soporte para UTF-8
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    // Dimensiones de las ventanas
    getmaxyx(stdscr, rows, cols); // 150x33
}

int main() {
    int rows, cols;
    init_ncurses(rows, cols);
    WINDOW *search = newwin(3, cols / 3 + 2, 0, cols / 3 - 2);
    WINDOW *filter = newwin(rows - 6, 20, 3, 0);
    WINDOW *watchList = newwin(rows - 6, 20, 3, cols - 20);
    WINDOW *movies = newwin(rows - 3, cols - 40, 3, 20);
    WINDOW *num = newwin(3, 10, rows - 3, cols - 15);

    refresh();
    werase(search);
    box(search, 0, 0); // dibuja un borde sobre una ventada(WINDOW, caracter
                       // vertical, caracter horizontal)
    mvwprintw(search, 1, 1, "Buscar: ");
    // TODO: terminar el rellenado de las ventanas.

    werase(filter);
    box(filter, 0, 0);
    mvwprintw(filter, 1, 1, "Filtros:");
    mvwhline(filter, 2, 1, ACS_HLINE, 18); // Línea horizontal

    Filter one("Romance");
    Filter two("Thriller");
    Filter three("Horror");
    Filter four("Indie");
    Filter five("Sci-Fi");

    std::vector<Filter> filters = {one, two, three, four, five};
    int y = 3;
    // INFO: Cuando un filtro se encuentr activo, se imprimirá en rojo.
    for (auto var : filters) {
        mvwprintw(filter, y, 2, "%s", var.name.c_str());
        mvwprintw(filter, y, 15, "..");
        mvwprintw(filter, y, 18, "%c", var.name[0]);
        y++;
    }

    werase(movies);
    box(movies, 0, 0);
    mvwprintw(movies, 1, 1, "Peliculas:");
    mvwhline(movies, 2, 1, ACS_HLINE, cols - 42); // Línea horizontal

    werase(watchList);
    box(watchList, 0, 0);
    mvwprintw(watchList, 1, 1, "Ver mas tarde:");
    mvwhline(watchList, 2, 1, ACS_HLINE, 18); // Línea horizontal

    werase(num);
    box(num, 0, 0);

    wrefresh(watchList);
    wrefresh(filter);
    wrefresh(search);
    wrefresh(movies);
    wrefresh(num);

    // INFO: Bucle para que la ventana no se salte de la ejecucion a la
    // finalización.
    int ch;
    while ((ch = getch()) != 'q') {
    }

    // Finalizar ncurses
    delwin(search);
    delwin(filter);
    delwin(watchList);
    delwin(movies);
    delwin(num);
    endwin();
    return 0;
}
