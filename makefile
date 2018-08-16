CC = g++
INCLUDE_DIRS=-I/SFML-2.5.0/include
LFLAGS=-L/SFML-2.5.0/lib
LIBS=-lsfml-main -lsfml-audio-s -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopenal32 -lopengl32 -lwinmm -lgdi32 -lfreetype -lvorbisenc -lvorbisfile -lvorbis -logg -lFLAC

# LIBS=-lsfml-main -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lopenal32 -lopengl32 -lwinmm -lgdi32 -lfreetype -lvorbisenc -lvorbisfile -lvorbis -logg
SRCS=fact.cpp end_of_review_state.cpp quiz_state.cpp main_menu_state.cpp main.cpp
all:
	$(CC) -DSFML_STATIC $(SRCS) -ggdb -o math.exe $(INCLUDE_DIRS) $(LIBS) $(LFLAGS)
# $(CC) $(SRCS) -ggdb -o math.exe $(INCLUDE_DIRS) $(LIBS) $(LFLAGS)

clean:
	del *.exe
