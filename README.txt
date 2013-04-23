   _____   ____  _   _  _____                
  |  __ \ / __ \| \ | |/ ____|    _     _    
  | |__) | |  | |  \| | |  __   _| |_ _| |_  
  |  ___/| |  | | . ` | | |_ | |_   _|_   _| 
  | |    | |__| | |\  | |__| |   |_|   |_|   
  |_|     \____/|_| \_|\_____|

DESCRIPCION:
---------------------------------------------------------------------------------------
Peque�a implementaci�n del famoso juego �Pong� para lograr un simulador de ping-pong completo en 2 dimensiones sobre cualquier sistema operativo que admita las librer�as utilizadas.

La idea principal del proyecto es aprender a realizar una aplicaci�n interactiva con el mayor n�mero de implementaciones posibles. Para el caso, el videojuego �Pong� ser� generado a partir de una serie de librer�as (SDL) para mostrar por la pantalla del ordenador el juego funcional. Lo que el grupo pretende alcanzar es reconocer y aprender conceptos b�sicos de programaci�n en videojuegos, tales que sean abarcados por los siguientes m�dulos:

x- Estructurado de un proyecto semi-complejo.
x- Representaci�n bidimensional de im�genes y alteraci�n de p�xeles.
x- Calculo de coordenadas y posicionamiento de superficies con ayuda de vectores.
x- Utilizaci�n del mezclador de sonido.
x- Uso de librer�as avanzadas.
x- A�adido de un m�dulo de comunicaci�n entre programas del tipo cliente-servidor para la comunicaci�n externa al programa cliente (juego on-line m�s concretamente), y todos los conceptos que eso lleva consigo (protocolo TCP/IP, sockets, flujos, etc�).
x- A�adido de un sistema simple de Inteligencia artificial (para jugar contra la propia m�quina).
x- Proporcionar un sistema sencillo de opciones para cambiar ciertas variables del juego (sonido, teclas, im�genes, etc�).
- A�adido de un m�dulo de progresi�n de niveles (tipo arkanoid), con una dificultad de juego proporcional al progreso del mismo:
  - A�adido un sistema de salvado de partida.
  - A�adido de un sistema de puntaciones on-line. 
  - A�adido de un sistema de generaci�n de niveles aleatorios.
  - A�adido de un programa-interfaz que permite al usuario generar niveles.
Las opciones con una "x" se han llegado a implementar satisfactoriamente. Adem�s, el proyecto sin compilar con las librer�as, si se realiza debidamente, puede ser exportado e implementado en cualquier otro sistema operativo compatible con las librer�as utilizadas (SDL), siempre y cuando en el debido formato y con las respectivas librer�as del sistema necesarias.


�RBOL DE FICHEROS:
---------------------------------------------------------------------------------------
Puede ver el �rbol de ficheros en la documentaci�n, en la ruta doc/html/files.html o en el siguiente enlace:
http://htmlpreview.github.io/?https://github.com/wikiti/ullPong/blob/master/doc/html/files.html

DOCUMENTACI�N:
---------------------------------------------------------------------------------------
Puede acceder a la documentaci�n del proyecto entrando en el archivo html ubicado en doc/html/index.html o accediendo al siguiente enlace:
http://htmlpreview.github.io/?https://github.com/wikiti/ullPong/blob/master/doc/html/index.html

TUTORIALES:
---------------------------------------------------------------------------------------
  - Lazy Foo' Productions:	http://lazyfoo.net/SDL_tutorials/index.php
  - Game Art Spain:		http://www.gameartspain.es/wiki/programacion/cursosdl_00_indice
  - Framework:			http://www.sdltutorials.com/sdl-net-part-1-user-tutorial

LIBRER�AS-DEPENDENCIAS:
---------------------------------------------------------------------------------------
  - SDL:			http://www.libsdl.org/
  - SDL_image:			http://www.libsdl.org/projects/SDL_image/
  - SDL_mixer:			http://www.libsdl.org/projects/SDL_mixer/
  - SDL_ttf:			http://www.libsdl.org/projects/SDL_ttf/
  - SDL_net:			http://www.libsdl.org/projects/SDL_net/

Nota: las librer�as para linkear vienen separadas en 2 carpetas: x86 y x64. Usar las del x86 y colocarlas en la carpeta /lib del compilador, no en /lib/x86

INSTALACI�N:
---------------------------------------------------------------------------------------
1. Bajar del repositorio todo el proyecto (se puede bajar como un ZIP desde gitHub, o por medio de un cliente git).
2. Descargar todas las librer�as y dependencias especificadas en el apartado superior y colocarlas en el correspondiente lugar del compilador (/{DIR_COMPILADOR}/lib y /{DIR_COMPILADOR}/include por lo general).
3. Ubicarnos en el directorio ra�z del proyecto, donde se encuentra el fichero makefile.
4. Compilar el proyecto con la herramienta make (> make all).
5. Copiar la carpeta "media" y las librer�as din�micas compiladas necesarias en el directorio "bin".
6. Si el ejecutable no arranca, debe de faltar alg�n archivo. Pruebe a ejecutar desde una l�nea de comandos y ver que fichero falta (aviso por medio de la salida est�ndar cout).

PLATAFORMAS:
---------------------------------------------------------------------------------------  
Si bien fue dise�ado para windows, el programa en s� no utiliza ninguna librer�a ni API dependiente de alguna plataforma. El programa simplemente usa las librer�as de SDL que, supuestamente, no dependen de la plataforma en la que se compila. Para ver m�s sobre esto, visite la p�gina principal de SDL(http://www.libsdl.org/).

AUTORES:
---------------------------------------------------------------------------------------
  - Daniel Herzog Cruz:		wikiti.doghound@gmail.com