ifeq ($(OS),Windows_NT)
	GLFLAGS = -lglut32win -lopengl32 -lglu32
	EXT = .exe
else
	GLFLAGS = -lGL -lGLU -lglut
	EXT = 
endif

CFLAGS = -Wall
CVERSION = -std=c++98

all: clean n3

debug: clean n3debug

doc:
	$(info Gerando documentacao...)
	doxygen doxygen.config

n3debug:
	$(info Compilando modo degug...)
	g++ -g -o n3$(EXT) n3.cpp $< $(CVERSION) $(CFLAGS) $(GLFLAGS)

n3:
	$(info Compilando...)
	g++ -o n3$(EXT) n3.cpp $< $(CVERSION) $(CFLAGS) $(GLFLAGS)

clean:
	$(info Removendo objetos...)
	rm -f n3$(EXT)
	rm -f -r html/
