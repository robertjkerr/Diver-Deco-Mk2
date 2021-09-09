
alg = src/model/algorithm
comps = src/model/compartments
types = src/model/types_constants

all: tissues.o buhlmann.o vpm.o deco_algorithm.o

deco_algorithm.o: ${alg}/deco_algorithm.cpp ${alg}/deco_algorithm.hpp
	g++ -c ${alg}/deco_algorithm.cpp

tissues.o: ${comps}/tissues.cpp ${comps}/tissues.hpp
	g++ -c ${comps}/tissues.cpp

buhlmann.o: ${comps}/buhlmann.cpp ${comps}/buhlmann.hpp
	g++ -c ${comps}/buhlmann.cpp

vpm.o: ${comps}/vpm.cpp ${comps}/vpm.hpp
	g++ -c ${comps}/vpm.cpp



