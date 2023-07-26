UTIL=./Util/vertexArray.cpp ./Util/shader.cpp ./Util/gerarMatriz.cpp ./Util/vertexBuffer.cpp ./Util/indexBuffer.cpp
MAIN=main.cpp
BINARY=game.out

compile:
	g++ -Wall $(MAIN) $(UTIL) -o $(BINARY) -lglfw -lGL -lGLEW -lm

run:
	./$(BINARY)
