CXX = g++

CXXFLAGS = -Iinclude -O2

LDFLAGS = -lX11

TARGET = build/resize_image

SOURCES = src/main.cpp src/resize_nearest_neighbour.cpp src/resize_bilinear.cpp

HEADERS = include/resize_image_base.h include/resize_nearest_neighbour.h include/resize_bilinear.h

OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS := $(patsubst src/%,build/%,$(OBJECTS))

all: create_build_dir $(TARGET)

create_build_dir:
	mkdir -p build

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

build/%.o: src/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f build/*.o $(TARGET)

.PHONY: all clean create_build_dir
