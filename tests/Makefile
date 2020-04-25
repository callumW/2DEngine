COMPILER=clang++
CPP_STD=c++14

MATH_TEST=test_maths.app

TESTING_OBJS=../src/game_math.o

# Main Source Files
SRC_FILES=$(wildcard src/*.cpp)

OBJ=$(patsubst %.cpp,%.o, ${SRC_FILES})

INCLUDES=-I../include

${MATH_TEST}: ${OBJ}
	${COMPILER} -std=${CPP_STD} ${OBJ} ${TESTING_OBJS} -o ${MATH_TEST}

%.o: %.cpp
	${COMPILER} -std=${CPP_STD} ${INCLUDES} -c $< -o $@

.PHONY: clean
clean:
	${RM} ${OBJ} ${MATH_TEST}

.PHONY: format-code
format-code:
	clang-format --style=file -i ${SRC_FILES} ${INCLUDE_FILES}
