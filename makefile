# Dossier des sources et des en-têtes
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Compilateur
CC = g++

# Options de compilation
CFLAGS = -I$(INC_DIR) -Wall -Wextra -pedantic -Wshadow -Wconversion -Wsign-conversion

# Fichiers source
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) 

# Cible finale
TARGET = crossword

# Règles de compilation
$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

# Règle pour compiler tous les fichiers .cpp en fichiers .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f $(OBJ) $(TARGET)