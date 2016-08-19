
LINKS=-lSDL2 -lSDL2_image -ltmxparser -lz -ltinyxml2

HEADERS=./src/character.h ./src/cTexture.h ./src/cSurface.h ./src/levelMap.h ./src/main_typedef.h

INCLUDE=-I /usr/local/include/ -L /usr/local/lib/ -Wl,-rpath,/usr/local/lib/

all: sdltest
	
sdltest: cTexture.o cSurface.o character.o levelMap.o sdltesting.o
	g++ -Wall -Wl,-rpath,/usr/local/lib/ cTexture.o cSurface.o character.o levelMap.o $(LINKS) sdltesting.o -o sdltest $(LINKS)

sdltesting.o: ./src/sdltesting.cpp $(HEADERS)
	g++ -Wall -c ./src/sdltesting.cpp

character.o: ./src/character.cpp $(HEADERS)
	g++ -Wall -c ./src/character.cpp

levelMap.o: ./src/levelMap.cpp $(HEADERS)
	g++ -Wall -I ./src/ -Wl,-rpath,/usr/local/lib/ -c ./src/levelMap.cpp

cTexture.o: ./src/cTexture.cpp $(HEADERS)
	g++ -Wall -c ./src/cTexture.cpp

cSurface.o: ./src/cSurface.cpp $(HEADERS)
	g++ -Wall -c ./src/cSurface.cpp

clean:
	rm *.o
