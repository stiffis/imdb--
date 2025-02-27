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
Un CLI para buscar peliculas, así como sus respectivas sinópsis y géneros <a></a>
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
    - [Casos de Uso](#casos-de-uso)
    - [Diagrama de Clases](#diagrama-de-clases)
    - [Limpieza de Datos](#limpieza-de-datos)
        - [Uso de R](#uso-de-r)
    - [Características](#características)
        - [Búsqueda con Trie](#búsqueda-con-trie)
        - [Interfaz CLI](#interfaz-cli)
        - [Listas de Usuarios](#listas-de-usuarios)
    - [Arquitetura](#arquitetura)
        - [Estructura de datos](#estructura-de-datos)
        - [Clases principales](#clases-principales)
        - [Uso de STL](#uso-de-stl)
        - [Uso de threads](#uso-de-threads)
    - [Patrones de Diseño](#patrones-de-diseño)
        - [Singleton](#singleton)
        - [Decorator](#decorator)
        - [Memento](#memento)
        - [Composite](#composite)
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
    - [Conclusiones](#conclusiones)
        - [Logros](#logros)
        - [Recomendaciones](#recomendaciones)
- [Contribución](#contribución)
- [Licencia](#licencia)
## Introducción
### Objetivo
El propósito del presente proyecto de nombre "IMDb--", es implementar una plataforma de *streaming*, donde se administre la *búsqueda y visualización* de sinopsis de películas, este proyecto es especial ya que se usó también como practica para el manejo de "workflows", simulando un ambiente de trabajo real, con reuniones fijas en un horario, donde se comparte el progreso de cada integrante, planificaciones semanales y de retroalimentación.
### Motivación
Fuimos motivados por la complejidad del proyecto ya que requerimos de conocimientos sobre el manejo de estructuras de datos y algoritmos, así como el uso de programación paralela, además de la necesidad de trabajar en equipo, lo cual nos permitió mejorar nuestras habilidades de comunicación, mejorando la calidad de nuestro trabajo.
### Alcance
El proyecto IMDb-- permite la búsqueda de películas mediante un prefijo o una palabra clave, además de mostrar la sinopsis y géneros de la película, también permite a los usuarios crear una lista de películas a las que se le dio like y un lista con las películas para ver después.
## Requisitos
### Requisitos de Software
- **Compilados de C++**: 
    - Se recomienda usar `g++`(GCC) versión 11.2.0 o superior.
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
    - Si se encuentra una película que coincida con la búsqueda, se preguntará si se desea añadir algun/os género/s a la búsqueda.
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
                    ```bash
                    Mostrando pagina 2 de 4
                    6. xmen the official game
                    7. xmen days of future past
                    8. fear and loathing in las vegas
                    9. keyhole
                    10. xmen apocalypse

                    -------------------------------------
                    | Opciones:                         |
                    | 'si' PARA SIGUIENTE PAGINA        |
                    | 'g' PARA FILTRAR POR GENERO       |
                    | 'r' PARA REMOVER EL ULTIMO FILTRO |
                    |  '0' PARA SALIR:                  |
                    -------------------------------------
                    
                    ```
                    - Si no hay más páginas de resultados, se mostrará un mensaje indicando que no hay más resultados y se volverá al menú principal.
                    ```bash
                    No hay mas resultados.

                    === Menu Principal ===
                    1. Ver peliculas en Ver Mas Tarde
                    2. Ver peliculas Likeadas
                    3. Buscar peliculas
                    4. Ver historial de busquedas
                    5. Guardar estado
                    6. Restaurar estado
                    0. Salir
                    --------------------------
                    | Seleccione una opcion: |
                    --------------------------
                    
                    ```
            - `g`: Permite filtrar los resultados por género.
            - `r`: Remueve el último filtro aplicado.
            - `0`: Sale de la búsqueda.

- **Ver historial de busquedas**:

## Contribución
### Reglas de Contribución
1. **Código Limpio**
2. **Satisface el linter**
3. **Ajusta el Readme según cambios (si aplica)**
4. **No agregues dependencias extra a menos de ser absolutamente necesario**
5. **Si estás solucionando un problema, abre un _issue_ o enlaza uno existente**

## Licencia
Este proyecto está bajo la licencia MIT. Para más información, revisa el archivo `LICENSE`.


---
<p align="center">Copyright &copy; 2025-present <a href="https://github.com/stiffis/imdb--" target="_blank">IMDb-- Org</a>
