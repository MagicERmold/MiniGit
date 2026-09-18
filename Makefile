# Compilatore e flag di compilazione
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Isrc/cli -Isrc/controller -Isrc/entity

# Nome dell'eseguibile finale
TARGET = minigit

# Individua tutti i file sorgente .cpp nelle varie cartelle
SRCS = src/main.cpp \
       $(wildcard src/cli/*.cpp) \
       $(wildcard src/controller/*.cpp) \
       $(wildcard src/entity/*.cpp)

# Trasforma l'elenco dei .cpp nei rispettivi file oggetto .o
OBJS = $(SRCS:.cpp=.o)

# Target principale: compila ed effettua il linking
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lssl -lcrypto

# Regola generica per compilare ciascun .cpp in un file oggetto .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target per eliminare file intermedi ed eseguibile
clean:
	rm -f $(OBJS) $(TARGET)