NAME = serializer
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS_DIR = srcs
SRCS = $(SRCS_DIR)/main.cpp $(SRCS_DIR)/Serializer.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.cpp $(SRCS_DIR)/Serializer.hpp $(SRCS_DIR)/Data.hpp
	$(CXX) $(CXXFLAGS) -I$(SRCS_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
