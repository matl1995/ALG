SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS =-std=c++11


all: $(BIN)/maxmin $(BIN)/minmax_matriz $(BIN)/zapatos $(BIN)/moda

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Compilación de módulos ************
$(BIN)/maxmin:  
	$(CXX) $(SRC)/maxmin.cpp -o $(BIN)/maxmin $(CPPFLAGS)

$(BIN)/minmax_matriz:
	$(CXX) $(SRC)/minmax_matriz.cpp -o $(BIN)/minmax_matriz $(CPPFLAGS)

$(BIN)/zapatos:
	$(CXX) $(SRC)/zapatos.cpp -o $(BIN)/zapatos $(CPPFLAGS)

$(BIN)/moda:
	$(CXX) $(SRC)/moda.cpp -o $(BIN)/moda $(CPPFLAGS)


# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
