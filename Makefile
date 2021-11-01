
CC = g++
f90 = gfortran
libs = -lstdc++

MODEL_DIR = src/model
COMPS_DIR = ${MODEL_DIR}/compartments
TYPES_DIR = ${MODEL_DIR}/types_constants
F90_DIR = ${COMPS_DIR}/f90

BIN_DIR = bin
OBJ_DIR = ${BIN_DIR}/obj
BUILD_DIR = build
MOD_DIR = ${PWD}/${BIN_DIR}/mod
MAIN = main

COMPS_SRCS = ${wildcard ${COMPS_DIR}/*.cpp} 
TYPES_SRCS = ${wildcard ${TYPES_DIR}/*.cpp}
CPP_SRCS = ${COMPS_SRCS} ${TYPES_SRCS}
F90_SRCS = constants.f90 buhl.f90 module.f90 #Compile in right order

OBJS_FILES = ${COMPS_SRCS:${COMPS_DIR}/%.cpp=%.o} ${TYPES_SRCS:${TYPES_DIR}/%.cpp=%.o} ${F90_SRCS:%.f90=%.o}
MOD_FILES = ${F90_SRCS:${F90_DIR/%.f90=${MOD_DIR}/%.mod}}
OBJS = ${OBJS_FILES:%=${OBJ_DIR}/%}

opt = -Wall -Wextra -pedantic -g
fopt = -J${MOD_DIR} -I${MOD_DIR}

all: ${OBJ_DIR} ${MOD_DIR} ${OBJS}

PHONY: main
main: all
	${CC} ${opt} -c ${MAIN}.cpp -o ${OBJ_DIR}/${MAIN}.o
	${f90} -o ${MAIN} ${OBJS} ${OBJ_DIR}/${MAIN}.o ${libs}

${OBJ_DIR}/%.o ${MOD_DIR}/%.mod: ${F90_DIR}/%.f90
	${f90} ${opt} -c -o $@ $< -I${MOD_DIR} -J${MOD_DIR}

${OBJ_DIR}/%.o: ${COMPS_DIR}/%.cpp 
	${CC} ${opt} -c -o $@ $<

${OBJ_DIR}/%.o: ${TYPES_DIR}/%.cpp
	${CC} ${opt} -c -o $@ $<

${OBJ_DIR}:
	mkdir -p $@

${MOD_DIR}:
	mkdir -p $@

PHONY: clean
clean:
	rm -rf bin 

PHONY: remove
remove: clean
	rm -rf build
	rm -f main.exe
