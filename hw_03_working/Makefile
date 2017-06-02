CXX = g++
CXXFLAGS = -O2 -Werror -Wall -Iinclude
LDFLAGS = 

EXE = main
SRCDIR = src
BINDIR = bin

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

all: $(EXE)

$(EXE): $(BINDIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)
	
$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(BINDIR)/*.d)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(BINDIR) $(EXE)

.PHONY: clean all

CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++03 -Iinclude
LDFLAGS = 

EXE1 = test
SRCDIR1 = test
BINDIR = bin

OBJECTS1 = $(patsubst $(SRCDIR1)/%.cpp,$(BINDIR)/%.o,$(wildcard $(SRCDIR1)/*.cpp))

test: $(EXE1)

$(EXE1): $(BINDIR) $(OBJECTS1) ./bin/huffman.o
	$(CXX) $(OBJECTS1) ./bin/huffman.o -o $(EXE1) $(LDFLAGS)

$(BINDIR)/%.o: $(SRCDIR1)/%.cpp ./src/huffman.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(BINDIR)/*.d)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(BINDIR) $(EXE1)

.PHONY: clean test
