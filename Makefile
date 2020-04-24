include VERSION

COMPILER=clang++
CPP_STD=c++14

BUILD_DIR=build/

# Main Source Files
SRC_FILES=$(wildcard src/*.cpp)

OBJ=$(patsubst %.cpp,%.o, ${SRC_FILES})

DEPS=$(patsubst %.cpp,%.d, ${SRC_FILES})

ASSET_FILES=$(wildcard assets/*)

BUILD_ASSETS=$(patsubst assets/%,${BUILD_DIR}/assets/%, ${ASSET_FILES})

# Get list of include files for code formatter
INCLUDE_FILES=$(wildcard include/*.h)

INCLUDES=-Iinclude

THIRD_PARTY_INCLUDES= \
-F/Users/cwilson/Libs/SDL/

LIBS= -F/Users/cwilson/Libs/SDL/ -framework SDL2 -framework SDL2_mixer
LD_FLAGS = ${LIBS} -Wl,-rpath,/Users/cwilson/Libs/SDL/

BINARY_NAME=terminal-reboot-${VERSION}.app

OUTPUT=${BUILD_DIR}${BINARY_NAME}

.PHONY: all
all: format-code build-app

.PHONY: build-app
build-app: ${OUTPUT}

${OUTPUT}: ${BUILD_DIR} ${OBJ} ${BUILD_ASSETS}
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

${BUILD_ASSETS}:
	cp -r assets ${BUILD_DIR}/assets
