NAME = ircserv
CC = c++ -std=c++98 
#CFLAGS = -Wall -Wextra -Werror
INC = INC
SRCS = $(wildcard SRCS/*.cpp)

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(SRCS) -I$(INC) -o $(NAME)
	@echo "\033[1;92mCompiled succesfully..\033[0m"

clean:
	rm -rf  $(NAME)

fclean: clean


re: fclean all

.PHONY: all clean fclean re
