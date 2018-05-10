SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -Wall -g  -I$(INC) -std=c++11


all: $(BIN)/voraz_maximo $(BIN)/PD_maximo $(BIN)/PD_operaciones

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Compilación de módulos ************
$(BIN)/voraz_maximo:  
	$(CXX) $(SRC)/voraz_maximo.cpp -o $(BIN)/voraz_maximo $(CPPFLAGS)

$(BIN)/PD_maximo:  
	$(CXX) $(SRC)/PD_maximo.cpp -o $(BIN)/PD_maximo $(CPPFLAGS)

$(BIN)/PD_operaciones:  
	$(CXX) $(SRC)/PD_operaciones.cpp -o $(BIN)/PD_operaciones $(CPPFLAGS)

# ************ Limpieza ************
clean :
	-rm $(SRC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
