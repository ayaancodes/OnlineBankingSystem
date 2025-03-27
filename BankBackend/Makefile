CXX = g++
CXXFLAGS = -std=c++17 -Wall -I/opt/homebrew/Cellar/libpqxx/7.10.0/include
LDFLAGS = -L/opt/homebrew/opt/libpqxx/lib -L/opt/homebrew/opt/libpq/lib -lpqxx -lpq

TARGET = dbtest
SRC = main.cpp src/db.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
