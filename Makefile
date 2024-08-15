CXX = g++

CXXFLAGS = -Iinclude -O2

LDFLAGS = -lX11

TARGET = build/resize_image

SOURCES = src/main.cpp src/resize_nearest_neighbour.cpp src/resize_bilinear.cpp

OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS := $(patsubst src/%,build/%,$(OBJECTS))

all: create_build_dir $(TARGET)

create_build_dir:
	mkdir -p build

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f build/*.o $(TARGET)

.PHONY: all clean create_build_dir
