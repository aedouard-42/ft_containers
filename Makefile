NAME = containers

SRCS = m.cpp

CXX = clang++

OBJS = ${SRCS:.cpp=.o}

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g3

STDFLAGS = ""

all : $(NAME)

std: ${NAME_STD}

.cpp.o :
		${CXX} ${STDFLAGS} ${CXXFLAGS} -c $< -o ${<:.cpp=.o}

$(NAME): ${OBJS}
		${CXX} -o ${NAME} ${OBJS}

clean :
		rm -rf ${OBJS}

fclean: clean
		rm -rf ${NAME}

re:		fclean all

.PHONY: all clean fclean res

std:
