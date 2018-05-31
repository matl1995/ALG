SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -Wall -pg  -I$(INC) -c -std=c++11


all:  $(BIN)/mipareja_practicas_voraz $(BIN)/mipareja_practicas_backtracking_sin_poda $(BIN)/mipareja_practicas_backtracking_con_poda $(BIN)/mipareja_practicas_branch_and_bound

# ************ Compilación de módulos ************

$(BIN)/mipareja_practicas_voraz:  
	$(CXX) $(SRC)/mipareja_practicas_voraz.cpp -o $(BIN)/mipareja_practicas_voraz -std=c++11

$(BIN)/mipareja_practicas_backtracking_sin_poda: $(OBJ)/mipareja_practicas_backtracking_sin_poda.o $(OBJ)/Apermutacion.o
	$(CXX) -o $(BIN)/mipareja_practicas_backtracking_sin_poda  $(OBJ)/mipareja_practicas_backtracking_sin_poda.o $(OBJ)/Apermutacion.o

$(OBJ)/mipareja_practicas_backtracking_sin_poda.o: $(SRC)/mipareja_practicas_backtracking_sin_poda.cpp
	$(CXX) $(CPPFLAGS) $(SRC)/mipareja_practicas_backtracking_sin_poda.cpp -o $(OBJ)/mipareja_practicas_backtracking_sin_poda.o

$(BIN)/mipareja_practicas_backtracking_con_poda: $(OBJ)/mipareja_practicas_backtracking_con_poda.o $(OBJ)/Apermutacion.o
	$(CXX) -o $(BIN)/mipareja_practicas_backtracking_con_poda  $(OBJ)/mipareja_practicas_backtracking_con_poda.o $(OBJ)/Apermutacion.o

$(OBJ)/mipareja_practicas_backtracking_con_poda.o: $(SRC)/mipareja_practicas_backtracking_con_poda.cpp
	$(CXX) $(CPPFLAGS) $(SRC)/mipareja_practicas_backtracking_con_poda.cpp -o $(OBJ)/mipareja_practicas_backtracking_con_poda.o

$(BIN)/mipareja_practicas_branch_and_bound: $(OBJ)/mipareja_practicas_branch_and_bound.o $(OBJ)/Apermutacion.o 
	$(CXX) -o $(BIN)/mipareja_practicas_branch_and_bound  $(OBJ)/mipareja_practicas_branch_and_bound.o $(OBJ)/Apermutacion.o

$(OBJ)/mipareja_practicas_branch_and_bound.o: $(SRC)/mipareja_practicas_branch_and_bound.cpp
	$(CXX) $(CPPFLAGS) $(SRC)/mipareja_practicas_branch_and_bound.cpp -o $(OBJ)/mipareja_practicas_branch_and_bound.o

$(OBJ)/Apermutacion.o: $(SRC)/Apermutacion.cpp $(INC)/Apermutacion.h
	$(CXX) $(CPPFLAGS) $(SRC)/Apermutacion.cpp -o $(OBJ)/Apermutacion.o

# ************ Limpieza ************
clean :
	-rm $(OBJ)/*

mrproper : clean
	-rm $(OBJ)/* $(BIN)/*
