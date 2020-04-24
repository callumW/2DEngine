include VERSION

COMPILER=clang++
CPP_STD=c++14

# Main Source Files
SRC_FILES=$(wildcard src/*.cpp)

OBJ=$(patsubst %.cpp,%.o, ${SRC_FILES})

DEPS=$(patsubst %.cpp,%.d, ${SRC_FILES})

# Get list of include files for code formatter
INCLUDE_FILES=$(wildcard include/*.h)

INCLUDES=-Iinclude

THIRD_PARTY_INCLUDES=

LIBS=
LD_FLAGS = ${LIBS}

BINARY_NAME=terminal-reboot-${VERSION}.app

BUILD_DIR=build/

OUTPUT=${BUILD_DIR}${BINARY_NAME}

.PHONY: all
all: format-code build-app

.PHONY: build-app
build-app: ${OUTPUT}

${OUTPUT}: ${BUILD_DIR} ${OBJ}
	${COMPILER} -std=${CPP_STD} ${OBJ} ${LD_FLAGS} -o ${OUTPUT}

%.o: %.cpp
	${COMPILER} -std=${CPP_STD} -MMD -MP ${INCLUDES} ${THIRD_PARTY_INCLUDES} -c $< -o $@

# Include generated dependency files
-include ${DEPS}

${BUILD_DIR}:
	mkdir ${BUILD_DIR}

.PHONY: clean
clean:
	$(RM) ${OBJ} ${DEPS}
	$(RM) -r ${BUILD_DIR}

.PHONY: format-code
format-code:
	clang-format -i ${SRC_FILES} ${INCLUDE_FILES}
