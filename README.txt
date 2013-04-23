   _____   ____  _   _  _____                
  |  __ \ / __ \| \ | |/ ____|    _     _    
  | |__) | |  | |  \| | |  __   _| |_ _| |_  
  |  ___/| |  | | . ` | | |_ | |_   _|_   _| 
  | |    | |__| | |\  | |__| |   |_|   |_|   
  |_|     \____/|_| \_|\_____|

DESCRIPCION:
---------------------------------------------------------------------------------------
Pequeña implementación del famoso juego “Pong” para lograr un simulador de ping-pong completo en 2 dimensiones sobre cualquier sistema operativo que admita las librerías utilizadas.

La idea principal del proyecto es aprender a realizar una aplicación interactiva con el mayor número de implementaciones posibles. Para el caso, el videojuego “Pong” será generado a partir de una serie de librerías (SDL) para mostrar por la pantalla del ordenador el juego funcional. Lo que el grupo pretende alcanzar es reconocer y aprender conceptos básicos de programación en videojuegos, tales que sean abarcados por los siguientes módulos:

x- Estructurado de un proyecto semi-complejo.
x- Representación bidimensional de imágenes y alteración de píxeles.
x- Calculo de coordenadas y posicionamiento de superficies con ayuda de vectores.
x- Utilización del mezclador de sonido.
x- Uso de librerías avanzadas.
x- Añadido de un módulo de comunicación entre programas del tipo cliente-servidor para la comunicación externa al programa cliente (juego on-line más concretamente), y todos los conceptos que eso lleva consigo (protocolo TCP/IP, sockets, flujos, etc…).
x- Añadido de un sistema simple de Inteligencia artificial (para jugar contra la propia máquina).
x- Proporcionar un sistema sencillo de opciones para cambiar ciertas variables del juego (sonido, teclas, imágenes, etc…).
- Añadido de un módulo de progresión de niveles (tipo arkanoid), con una dificultad de juego proporcional al progreso del mismo:
  - Añadido un sistema de salvado de partida.
  - Añadido de un sistema de puntaciones on-line. 
  - Añadido de un sistema de generación de niveles aleatorios.
  - Añadido de un programa-interfaz que permite al usuario generar niveles.
Las opciones con una "x" se han llegado a implementar satisfactoriamente. Además, el proyecto sin compilar con las librerías, si se realiza debidamente, puede ser exportado e implementado en cualquier otro sistema operativo compatible con las librerías utilizadas (SDL), siempre y cuando en el debido formato y con las respectivas librerías del sistema necesarias.


ÁRBOL DE FICHEROS:
---------------------------------------------------------------------------------------
Puede ver el árbol de ficheros en la documentación, en la ruta doc/html/files.html o en el siguiente enlace:
http://htmlpreview.github.io/?https://github.com/wikiti/ullPong/blob/master/doc/html/files.html

DOCUMENTACIÓN:
---------------------------------------------------------------------------------------
Puede acceder a la documentación del proyecto entrando en el archivo html ubicado en doc/html/index.html o accediendo al siguiente enlace:
http://htmlpreview.github.io/?https://github.com/wikiti/ullPong/blob/master/doc/html/index.html

TUTORIALES:
---------------------------------------------------------------------------------------
  - Lazy Foo' Productions:	http://lazyfoo.net/SDL_tutorials/index.php
  - Game Art Spain:		http://www.gameartspain.es/wiki/programacion/cursosdl_00_indice
  - Framework:			http://www.sdltutorials.com/sdl-net-part-1-user-tutorial

LIBRERÍAS-DEPENDENCIAS:
---------------------------------------------------------------------------------------
  - SDL:			http://www.libsdl.org/
  - SDL_image:			http://www.libsdl.org/projects/SDL_image/
  - SDL_mixer:			http://www.libsdl.org/projects/SDL_mixer/
  - SDL_ttf:			http://www.libsdl.org/projects/SDL_ttf/
  - SDL_net:			http://www.libsdl.org/projects/SDL_net/

Nota: las librerías para linkear vienen separadas en 2 carpetas: x86 y x64. Usar las del x86 y colocarlas en la carpeta /lib del compilador, no en /lib/x86

INSTALACIÓN:
---------------------------------------------------------------------------------------
1. Bajar del repositorio todo el proyecto (se puede bajar como un ZIP desde gitHub, o por medio de un cliente git).
2. Descargar todas las librerías y dependencias especificadas en el apartado superior y colocarlas en el correspondiente lugar del compilador (/{DIR_COMPILADOR}/lib y /{DIR_COMPILADOR}/include por lo general).
3. Ubicarnos en el directorio raíz del proyecto, donde se encuentra el fichero makefile.
4. Compilar el proyecto con la herramienta make (> make all).
5. Copiar la carpeta "media" y las librerías dinámicas compiladas necesarias en el directorio "bin".
6. Si el ejecutable no arranca, debe de faltar algún archivo. Pruebe a ejecutar desde una línea de comandos y ver que fichero falta (aviso por medio de la salida estándar cout).

PLATAFORMAS:
---------------------------------------------------------------------------------------  
Si bien fue diseñado para windows, el programa en sí no utiliza ninguna librería ni API dependiente de alguna plataforma. El programa simplemente usa las librerías de SDL que, supuestamente, no dependen de la plataforma en la que se compila. Para ver más sobre esto, visite la página principal de SDL(http://www.libsdl.org/).

AUTORES:
---------------------------------------------------------------------------------------
  - Daniel Herzog Cruz:		wikiti.doghound@gmail.com