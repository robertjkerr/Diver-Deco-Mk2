
CC = g++

MODEL_SRC := src/model
BIN_DIR := bin
OBJ_DIR := ${BIN_DIR}/obj
BUILD_DIR := build

HDRS = ${wildcard ${wildcard ${MODEL_SRC}/*/}*.h}
SRCS = ${wildcard ${wildcard ${MODEL_SRC}/*/}*.cpp}

OBJS := ${SRCS:${MODEL_SRC}/%.cpp=${OBJ_DIR}/%.o}

API := ${SRCS:${MODEL_SRC}/api/%.cpp=${OBJ_DIR}/%.o}
COMPS := ${SRCS:${MODEL_SRC}/compartments/%.cpp=${OBJ_DIR}/%.o}
ALG := ${SRCS:${MODEL_SRC}/algorithm/%.cpp=${OBJ_DIR}/%.o}
TRACK := ${SRCS:${MODEL_SRC}/tracking/%.cpp=${OBJ_DIR}/%.o}
TYPES := ${SRCS:${MODEL_SRC}/types_constants/%.cpp=${OBJ_DIR}/%.o}

all: 
	${SRCS}

${OBJ_DIR}: ${OBJ_DIR}
	mkdir -p $@

link: ${OBJS}
	${CC} -o ${BIN_DIR}/model_test ${OBJS}

objs: ${OBJ_DIR} | ${OBJS}

${OBJS}: ${SRCS} ${HDRS}
	${CC} -c -o $@ $<