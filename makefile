CC = g++
CFLAGS = -Wall -g
TARGET = shop
SOURCES = main.cpp Product.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = Product.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
