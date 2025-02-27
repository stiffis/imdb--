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
