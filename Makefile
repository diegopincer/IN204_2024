# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Iinclude -Wall -std=c++11

# Linker flags for X11
LDFLAGS = -lX11

# Directories
SRCDIR = src
INCDIR = include
BUILDDIR = build

# Target executable
TARGET = $(BUILDDIR)/main

# Source files
SRCFILES = $(SRCDIR)/main.cpp

# Object files
OBJFILES = $(BUILDDIR)/main.o

# Default rule
all: $(TARGET) copy_image

# Rule to link the executable
$(TARGET): $(OBJFILES)
	$(CXX) $(OBJFILES) -o $(TARGET) $(LDFLAGS)

# Rule to compile the source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create the build directory if it doesn't exist
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Copy image to the build directory
copy_image:
	cp $(SRCDIR)/lenna.png $(BUILDDIR)/lenna.png

# Clean up the build
clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean
