CC=g++
CFLAGS=-c
LDFLAGS=-Wall -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL_net
SOURCES=src\main.cpp src\engine.cpp src\frame.cpp src\globals.cpp src\instance.cpp src\pad.cpp src\particulas.cpp src\pelota.cpp src\teclado.cpp src\temporizador.cpp src\warning.cpp src\1jugador\turbo.cpp src\1jugador\infinito\instancia.cpp src\1jugador\infinito\pad_1j_inf.cpp src\1jugador\infinito\pelota_1j_inf.cpp src\menu\boton.cpp src\menu\instance_menu.cpp src\menu\menu.cpp src\menu\submenu\instance_menu_1j.cpp src\menu\submenu\instance_menu_mj.cpp src\menu\submenu\instance_menu_mj_online.cpp src\multijugador\marcador.cpp src\multijugador\pad_mj.cpp src\multijugador\pelota_mj.cpp src\multijugador\local\instancia.cpp src\multijugador\local\pad_mj_local.cpp src\multijugador\local\pelota_mj_local.cpp src\multijugador\local\cpu\instancia.cpp src\multijugador\local\cpu\pad_cpu.cpp src\multijugador\local\cpu\pelota_cpu.cpp src\multijugador\online\instancia_client.cpp src\multijugador\online\instancia_server.cpp src\multijugador\online\marcador_online.cpp src\multijugador\online\network_struct.cpp src\multijugador\online\pad_mj_online.cpp src\multijugador\online\pelota_mj_online.cpp src\multijugador\online\tecladoIP.cpp src\network\CNet.cpp src\opciones\opciones.cpp src\opciones\opciones_flechas.cpp src\opciones\tablero.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=bin\Pong++

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	del $(OBJECTS) $(EXECUTABLE)
doxy:
	doxygen documentation.Doxyfile