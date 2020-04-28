include VERSION

COMPILER=clang++
CPP_STD=c++14

BUILD_DIR=build/
TEST_DIR=tests/
TEST_BUILD_DIR=${BUILD_DIR}/tests/

# Main Source Files
SRC_FILES=$(wildcard src/*.cpp)

OBJ=$(patsubst %.cpp,%.o, ${SRC_FILES})

DEPS=$(patsubst %.cpp,%.d, ${SRC_FILES})

# Test source files
TEST_SRC_FILES=$(wildcard tests/src/*.cpp)

FILES_UNDER_TEST= \
src/game_math.cpp

TEST_OBJ=$(patsubst %.cpp,%.o, ${TEST_SRC_FILES})

OBJS_UNDER_TEST=$(patsubst %.cpp,%.o, ${FILES_UNDER_TEST})

TEST_DEPS=$(patsubst %.cpp,%.d, ${TEST_SRC_FILES})

TEST_INCLUDES_FILES=$(wildcard tests/include/*.h)

ASSET_FILES=$(wildcard assets/*)

BUILD_ASSETS=$(patsubst assets/%,${BUILD_DIR}/assets/%, ${ASSET_FILES})

# Get list of include files for code formatter
INCLUDE_FILES=$(wildcard include/*.h)

INCLUDES=-Iinclude

THIRD_PARTY_INCLUDES= \
-F/Users/cwilson/Libs/SDL/

LIBS= -F/Users/cwilson/Libs/SDL/ -framework SDL2 -framework SDL2_mixer
LD_FLAGS = ${LIBS} -Wl,-rpath,/Users/cwilson/Libs/SDL/

CPP_FLAGS= -Wall

BINARY_NAME=terminal-reboot-${VERSION}.app

OUTPUT=${BUILD_DIR}${BINARY_NAME}

TEST_APP=run_tests.app
TEST_OUTPUT=${TEST_BUILD_DIR}${TEST_APP}

.PHONY: all
all: format-code build-app tests

.PHONY: build-app
build-app: ${OUTPUT}

${OUTPUT}: ${BUILD_DIR} ${OBJ} ${BUILD_ASSETS}
	${COMPILER} -std=${CPP_STD} ${OBJ} ${LD_FLAGS} -o ${OUTPUT}

%.o: %.cpp
	${COMPILER} -std=${CPP_STD} -MMD -MP ${CPP_FLAGS} ${INCLUDES} ${THIRD_PARTY_INCLUDES} -c $< -o $@

# Include generated dependency files
-include ${DEPS}
-include ${TEST_DEPS}

${BUILD_DIR}:
	mkdir ${BUILD_DIR}

.PHONY: clean
clean:
	$(RM) ${OBJ} ${DEPS} ${TEST_OBJ}
	$(RM) -r ${BUILD_DIR}

.PHONY: format-code
format-code:
	clang-format --style=file -i ${SRC_FILES} ${INCLUDE_FILES} ${TEST_SRC_FILES} ${TEST_INCLUDES_FILES}

${BUILD_ASSETS}:
	cp -r assets ${BUILD_DIR}/assets

.PHONY: tests
tests: ${TEST_OUTPUT}
	./${TEST_OUTPUT}

${TEST_OUTPUT}: ${TEST_BUILD_DIR} ${TEST_OBJ}
	${COMPILER} -std=${CPP_STD} ${TEST_OBJ} ${OBJS_UNDER_TEST} ${LD_FLAGS} -o ${TEST_OUTPUT}

${TEST_BUILD_DIR}:
	mkdir ${TEST_BUILD_DIR}
