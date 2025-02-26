# Programación III: Proyecto Final (2025-0)
## Sistemas Operativos Soportados
<p align=center>
<br>
<a href="http://makeapullrequest.com"><img src="https://img.shields.io/badge/PRs-welcome-brightgreen.svg"></a>
<a href="#Linux"><img src="https://img.shields.io/badge/os-linux-brightgreen">
<a href="#MacOS"><img src="https://img.shields.io/badge/os-mac-brightgreen">
<a href="#Android"><img src="https://img.shields.io/badge/os-android-brightgreen">
<a href="#Windows"><img src="https://img.shields.io/badge/os-windows-yellowgreen">
<br>
<h1 align="center">
<a href="logo"><img src="/Pasted image 20250226141439.png"></a>
<br>
<a href="https://github.com/stiffis"><img src="https://img.shields.io/badge/lead-stiffis-lightblue"></a>
<a href="https://github.com/CoolnsX"><img src="https://img.shields.io/badge/maintainer-abel-blue"></a>
<a href="https://github.com/justchokingaround"><img src="https://img.shields.io/badge/maintainer-marco-blue"></a>

</p>

<h3 align="center">
Un CLI para buscar peliculas, así como sus respectivas sinópsis y géneros <a></a>
</h3>

---
## Integrantes: 
- Marco Antonio Galindo Bendezú (202310440)
- Yuri
- Steve Andy Ildefonso Santos (202410402)

## Tabla de Contenidos
- [Introducción](#introducción)
    - [Objetivo](#objetivo)
    - [Motivación](#motivación)
    - [Alcance](#alcance)
- [Requisitos](#requisitos)
    - [Requisitos de Software](#requisitos-de-software)
    - [Requisitos de Hardware](#requisitos-de-hardware)
- [Instalación](#instalación)
- [Uso](#uso)
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
        - [Solucion de Errores](#solucion-de-errores)
        - [Herramientas Usadas](#herramientas-usadas)
    - [Conclusiones](#conclusiones)
        - [Logros](#logros)
        - [Recomendaciones](#recomendaciones)
- [Contribución](#contribución)
- [Licencia](#licencia)


El propósito del presente proyecto de nombre "IMDb--", es implementar una plataforma de *streaming*, donde se administre la *búsqueda y visualización* de sinopsis de películas, este proyecto es especial ya que se usó también como practica para el manejo de "workflows", simulando un ambiente de trabajo real, con reuniones fijas en un horario, donde se comparte el progreso de cada integrante, planificaciones semanales y de retroalimentación. 

