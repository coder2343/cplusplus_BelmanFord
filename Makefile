# Makefile for CSC-301 Project #1
# Eric A. Autry, 09/08/22
# 
# As usual, you can build this software by typing:
#
#     make


# ----- Make Macros -----

CXXFLAGS =	-O3
CXX	=	gcc

TARGETS =	arbitrage
OBJECTS =	arbitrage.cpp project3.cpp
REMOVE =	arbitrage.o project3.o
LINKS =	-std=c++20 -lstdc++ -lm
INCLUDE = 

# ----- Make Rules -----

all:	$(TARGETS)

arbitrage:	$(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o arbitrage $(OBJECTS) $(LINKS)

clean:
	rm -f $(TARGETS) $(REMOVE)