SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -Wall -g  -I$(INC) -c -std=c++11


all: $(BIN)/cifras

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Compilación de módulos ************
$(BIN)/voraz_maximo:  
	$(CXX) $(SRC)/voraz_maximo.cpp -o $(BIN)/voraz_maximo $(CPPFLAGS)


# ************ Limpieza ************
clean :
	-rm $(SRC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
