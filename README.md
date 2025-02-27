# Programación III: Proyecto Final (2025-0)
### Sistemas Operativos Soportados
<p align=center>
<br>
<a href="http://makeapullrequest.com"><img src="https://img.shields.io/badge/PRs-welcome-brightgreen.svg"></a>
<a href="#Linux"><img src="https://img.shields.io/badge/os-linux-brightgreen">
<a href="#MacOS"><img src="https://img.shields.io/badge/os-mac-brightgreen">
<a href="#Windows"><img src="https://img.shields.io/badge/os-windows-yellowgreen">
<br>
<h1 align="center">
<a href="logo"><img src="/Pasted image 20250226141439.png"></a>
<br>
<a href="https://github.com/AntoMGB1"><img src="https://img.shields.io/badge/lead-marco-lightblue"></a>
<a href="https://github.com/stiffis"><img src="https://img.shields.io/badge/maintainer-stiffis-blue"></a>
<a href="https://github.com/Vasco2510"><img src="https://img.shields.io/badge/maintainer-abel-blue"></a>

</p>

<h3 align="center">
Un CLI para buscar películas, así como sus respectivas sinopsis y géneros
</h3>

---
## Integrantes: 
- Marco Antonio Galindo Bendezú
- Steve Andy Ildefonso Santos
- Yuri Abel Escobar Perez

## Tabla de Contenidos
- [Introducción](#introducción)
    - [Objetivo](#objetivo)
    - [Motivación](#motivación)
    - [Alcance](#alcance)
- [Requisitos](#requisitos)
    - [Requisitos de Software](#requisitos-de-software)
    - [Requisitos de Hardware](#requisitos-de-hardware)
- [Instalación](#instalación)
- [Manual de Uso](#manual-de-uso)
- [Documentación](#documentación)
    - [Diagrama de Clases](#diagrama-de-clases)
    - [Limpieza de Datos](#limpieza-de-datos)
        - [Uso de R](#uso-de-r)
    - [Características](#características)
        - [Búsqueda con Trie](#búsqueda-con-trie)
        - [Interfaz CLI](#interfaz-cli)
        - [Listas de Usuarios](#listas-de-usuarios)
    - [Arquitectura](#arquitectura)
        - [Estructura de datos](#estructura-de-datos)
        - [Clases principales](#clases-principales)
        - [Uso de STL](#uso-de-stl)
        - [Uso de threads](#uso-de-threads)
    - [Patrones de Diseño](#patrones-de-diseño)
        - [Singleton](#singleton)
        - [Decorator](#decorator)
        - [Memento](#memento)
    - [Rendimiento](#rendimiento)
        - [Complejidad Temporal](#complejidad-temporal)
        - [Complejidad Espacial](#complejidad-espacial)
        - [Tabla de Comparación](#tabla-de-comparación)
        - [¿Qué podemos mejorar?](#¿qué-podemos-mejorar?)
    - [Manejo de Errores](#manejo-de-errores)
        - [Errores](#errores)
        - [Excepciones](#excepciones)
        - [Validación de Entrada](#validación-de-entrada)
    - [Proceso de Desarrollo](#proceso-de-desarrollo)
        - [Metodología de Trabajo](#metodología-de-trabajo)
        - [Solución de Errores](#solucion-de-errores)
        - [Herramientas Usadas](#herramientas-usadas)
- [Contribución](#contribución)
- [Licencia](#licencia)

## Introducción
### Objetivo
El propósito del presente proyecto de nombre "IMDb--", es implementar una plataforma de *streaming*, donde se administre la *búsqueda y visualización* de sinopsis de películas, este proyecto es especial ya que se usó también como práctica para el manejo de "workflows", simulando un ambiente de trabajo real, con reuniones fijas en un horario, donde se comparte el progreso de cada integrante, planificaciones semanales y de retroalimentación.

### Motivación
Fuimos motivados por la complejidad del proyecto ya que requerimos de conocimientos sobre el manejo de estructuras de datos y algoritmos, así como el uso de programación paralela, además de la necesidad de trabajar en equipo, lo cual nos permitió mejorar nuestras habilidades de comunicación, mejorando la calidad de nuestro trabajo.

### Alcance
El proyecto IMDb-- permite la búsqueda de películas mediante un prefijo o una palabra clave, además de mostrar la sinopsis y géneros de la película. También permite a los usuarios crear una lista de películas a las que se le dio like y una lista con las películas para ver después.

## Requisitos
### Requisitos de Software
- **Compilador de C++**: 
    - Se recomienda usar `g++` (GCC) versión 11.2.0 o superior.
    - Alternativamente, se puede usar `clang++` versión 13.0.0 o superior.
- **Sistema operativo**:
    - Linux (Ubuntu, Fedora, Arch, etc.)
    - MacOS
    - Windows

### Requisitos de Hardware
No se requiere de un hardware específico, ya que el programa no es muy demandante en cuanto a recursos.

## Instalación
Si en caso no se tuviera instalado el compilador de C++, se puede instalar con el siguiente comando:
```bash
sudo apt-get install g++
```
Para instalar el programa, se debe clonar el repositorio y compilar el código fuente. Para ello, se debe ejecutar los siguientes comandos en la terminal:
```bash
git clone <url>
cd imdb--/
```
Para compilar el código fuente, se debe ejecutar el siguiente comando:
```bash
g++ -o main main.cpp
```
Para ejecutar el programa, se debe ejecutar el siguiente comando:
```bash
./main
```

## Manual de Uso
Una vez ejecutado el programa, se mostrará un menú con las siguientes opciones:
```bash
No tienes peliculas en Likes.
No tienes peliculas en Ver Mas Tarde.

=== Menu Principal ===
1. Ver peliculas en Ver Mas Tarde
2. Ver peliculas Likeadas
3. Buscar peliculas
4. Ver historial de busquedas
5. Guardar estado
6. Restaurar estado
7. Peliculas recomendadas
0. Salir
--------------------------
| Seleccione una opcion: |
--------------------------

```
Para seleccionar una opción, se debe ingresar el número correspondiente y presionar la tecla `Enter`. A continuación, se detallan las opciones del menú:

- **Ver peliculas en Ver Mas Tarde**:
    - Muestra las películas que se han agregado a la lista de "Ver Mas Tarde". Si no hay películas en la lista, se mostrará un mensaje indicando que no hay películas en la lista.
    ```bash
    No tienes peliculas en Ver Mas Tarde.
    ```

- **Ver peliculas Likeadas**:
    - Muestra las películas que se han agregado a la lista de "Likes". Si no hay películas en la lista, se mostrará un mensaje indicando que no hay películas en la lista.
    ```bash
    No tienes peliculas en Likes.
    ```

- **Buscar peliculas**:
    - Permite buscar películas por nombre. Se puede ingresar el nombre completo de la película o una parte del nombre. El programa mostrará las películas que coincidan con la búsqueda.
    ```bash
    -----------------------------------
    | Ingrese el termino de busqueda: |
    -----------------------------------
    Wolverine
    ```

    - Si no se encuentra ninguna película que coincida con la búsqueda, se mostrará un mensaje indicando que no se encontraron resultados.
    ```bash
    No se encontraron resultados para 'Wolverine'.
    ```

    - Si se encuentra una película que coincida con la búsqueda, se preguntará si se desea añadir algún/os género/s a la búsqueda.
    ```bash
    ----------------------------------------------------
    | Desea filtrar los resultados por genero? (s/n):  |
    ----------------------------------------------------
    ```

    - Si se desea añadir algún género a la búsqueda, se debe ingresar `s` y presionar la tecla `Enter`. Luego escribir el género que se desea añadir a la búsqueda y presionar la tecla `Enter`.
    ```bash
    -----------------------
    | Ingrese el genero:  |
    -----------------------
    comedy
    ```

    - Se mostrarán las películas que coincidan con la búsqueda y el género seleccionado.
    ```bash
    Mostrando pagina 1 de 1
    1. fear and loathing in las vegas
    2. logan
    -------------------------------------
    | Opciones:                         |
    | 'si' PARA SIGUIENTE PAGINA        |
    | 'g' PARA FILTRAR POR GENERO       |
    | 'r' PARA REMOVER EL ULTIMO FILTRO |
    |  '0' PARA SALIR:                  |
    -------------------------------------
    ```

    - Detalles de las opciones:
        - `si`: Muestra la siguiente página de resultados en caso hubieran más películas.
        - `g`: Permite filtrar los resultados por género.
        - `r`: Remueve el último filtro aplicado.
        - `0`: Sale de la búsqueda.

- **Ver historial de busquedas**:
    - Muestra el historial de búsquedas realizadas. Si no se ha realizado ninguna búsqueda, se mostrará un mensaje indicando que no hay búsquedas en el historial.
    ```bash
    No hay busquedas en el historial.
    ```

- **Guardar estado**:
    - Guarda el estado actual del programa. Se mostrará un mensaje indicando que el estado ha sido guardado.
    ```bash
    Estado guardado.
    ```

- **Restaurar estado**:
    - Restaura el estado guardado previamente. Se mostrará un mensaje indicando que el estado ha sido restaurado.
    ```bash
    Estado restaurado.
    ```

- **Peliculas recomendadas**:
    - Muestra las películas recomendadas. Si no hay películas recomendadas, se mostrará un mensaje indicando que no hay películas recomendadas.
    ```bash
    No hay peliculas recomendadas.
    ```

- **Salir**:
    - Sale del programa.

## Documentación
### Diagrama de Clases
El diagrama de clases muestra la estructura de clases del programa, así como las relaciones entre ellas. A continuación, se muestra el diagrama de clases del programa IMDb--:

![Diagrama de Clases](Falta imagen)

### Limpieza de Datos
Para la limpieza de datos, se utilizó el lenguaje de programación R. A continuación, se detallan los pasos realizados para la limpieza de datos:
#### Uso de R
1. **Carga de librearías**:
    - Se cargaron las librerías necesarias para la limpieza de datos.
    ```R
    library(dplyr)
    library(stringr)
    ```
2. **Carga de datos**:
    - Se cargaron los datos a limpiar.
    ```R
    data <- read.csv("C:/Users/Marco/Desktop/Prp/Data.csv")
    ```
3. **Función para limpiar texto, eliminando caracteres no latinos y símbolos innecesarios**
    ```R
    clean_text <- function(text) {
    cleaned <- str_replace_all(text, "[^a-zA-Z0-9\\s.!?-]", "")
    return(cleaned)
    }
    ```
4. **Aplicación de la función**
    ```R
    cleaned_data <- data %>%
    mutate(across(everything(), ~ sapply(., clean_text)))
    ```
5. **Guardado de datos limpios**
    - Se guardaron los datos limpios en un archivo CSV.
    ```R
    write.csv(cleaned_data, "C:/Users/Marco/Desktop/Prp/CleanedData.csv", row.names = FALSE)
    ```

### Características
#### Búsqueda con Trie
El programa implementa un Trie para realizar búsquedas eficientes de películas por prefijo o palabra clave. El Trie está constituido por las letras de cada palabra que hay en toda la data, permitiendo así búsquedas rápidas y precisas.

#### Interfaz CLI
El programa cuenta con una interfaz de línea de comandos (CLI) que permite a los usuarios interactuar con el sistema de manera sencilla y eficiente. El menú principal ofrece opciones para ver películas en "Ver Mas Tarde", ver películas "Likeadas", buscar películas, ver el historial de búsquedas, guardar el estado, restaurar el estado y obtener recomendaciones de películas.

#### Listas de Usuarios
El programa permite a los usuarios crear y gestionar listas de películas. Los usuarios pueden agregar películas a una lista de "Likes" y a una lista de "Ver Mas Tarde". Estas listas se guardan en archivos de texto para su persistencia.

### Arquitectura
#### Estructura de datos
El programa utiliza varias estructuras de datos de la biblioteca estándar de C++ (STL), como `vector`, `unordered_set`, `unordered_map`, y `map`, para almacenar y gestionar la información de las películas y las listas de usuarios.

#### Clases principales
El programa define varias clases principales, entre ellas:
- `Pelicula`: Representa una película con atributos como `imdb_id`, `titulo`, `sinopsis`, y `etiquetas`.
- `GestorPeliculas`: Gestiona la colección de películas y las listas de usuarios.
- `Trie` y `TrieNode`: Implementan la estructura de datos Trie para las búsquedas de películas.
- `CargadorCSV`: Se encarga de cargar películas desde un archivo CSV.
- `MovieDisplay` y sus decoradores: Gestionan la visualización de los detalles de las películas.

#### Uso de STL
El programa aprovecha las estructuras de datos y algoritmos de la STL para realizar operaciones eficientes de búsqueda, inserción y eliminación.

#### Uso de threads
El programa utiliza threads para cargar las películas desde el archivo CSV en paralelo, mejorando así el rendimiento y la eficiencia.

### Patrones de Diseño
#### Singleton
El patrón Singleton se utiliza en la clase `GestorPeliculas` para asegurar que solo exista una instancia de esta clase en todo el programa.

#### Decorator
El patrón Decorator se utiliza en las clases `MovieDisplay`, `BasicMovieDisplay`, y `ExtendedMovieDisplay` para agregar funcionalidades adicionales a la visualización de las películas.

#### Memento
El patrón Memento se utiliza para guardar y restaurar el estado del programa, permitiendo a los usuarios deshacer cambios y volver a estados anteriores.

### Rendimiento
#### Complejidad Temporal
Las operaciones de búsqueda en el Trie tienen una complejidad temporal de O(m), donde m es la longitud de la palabra buscada. Las operaciones de inserción también tienen una complejidad de O(m).

#### Complejidad Espacial
La estructura Trie puede consumir una cantidad significativa de memoria, especialmente si el conjunto de palabras es grande. Sin embargo, esta estructura permite búsquedas rápidas y eficientes.

#### Tabla de Comparación
Falta completar.

#### ¿Qué podemos mejorar?
1. Uso de Punteros Inteligentes:
    - Usar punteros inteligentes (std::unique_ptr, std::shared_ptr) en lugar de punteros crudos para gestionar la memoria de manera más segura y evitar fugas de memoria.
2. Refactorización del Código:
    - Refactorizar el código para eliminar redundancias y mejorar la legibilidad.
    - Usar const correctamente para indicar que ciertas variables no deben cambiar.
3. Logging:
    - Implementar un sistema de logging para registrar eventos importantes y errores. Esto puede ser muy útil para depuración y monitoreo.
4. Optimizaciones de Rendimiento:
    - Revisar el uso de tus estructuras de datos para asegurarte de que sean las más eficientes para las tareas que estás realizando.
    - Considerar el uso de algoritmos más eficientes para las operaciones más costosas.
### Manejo de Errores
#### Errores
El programa maneja varios tipos de errores, como la falta de archivos de datos y errores de entrada del usuario.

#### Excepciones
Se utilizan excepciones para manejar errores críticos, como la imposibilidad de abrir archivos de datos.

#### Validación de Entrada
El programa valida las entradas del usuario para asegurar que sean correctas y evitar errores durante la ejecución.

### Proceso de Desarrollo
#### Metodología de Trabajo
Se utilizó una metodología de desarrollo ágil, con reuniones semanales para planificar tareas y revisar el progreso.

#### Solución de Errores
Se utilizaron herramientas de depuración y pruebas unitarias para identificar y solucionar errores en el código.

#### Herramientas Usadas
Se utilizaron varias herramientas para el desarrollo del proyecto, incluyendo:
- **Compilador de C++**: g++ (GCC)
- **Editor de código**: Visual Studio Code
- **Sistema de control de versiones**: Git y GitHub
- **Lenguaje de programación R**: Para la limpieza de datos

## Contribución
### Reglas de Contribución
1. **Código Limpio**
2. **Ajusta el Readme según cambios (si aplica)**
3. **No agregues dependencias extra a menos de ser absolutamente necesario**
4. **Si estás solucionando un problema, abre un _issue_ o enlaza uno existente**

## Licencia
Este proyecto está bajo la licencia MIT. Para más información, revisa el archivo `LICENSE`.

---
<p align="center">Copyright &copy; 2025-present <a href="https://github.com/stiffis/imdb--" target="_blank">IMDb-- Org</a>
