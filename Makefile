NAME = ircserv
CC = c++ -std=c++98 
CFLAGS = -Wall -Wextra -Werror
INC = INC
INCS = $(INC)/*.hpp
SRCS = $(wildcard SRCS/*.cpp) $(wildcard SRCS/Commands/*.cpp)

all: $(NAME)

$(NAME): $(SRCS) $(INCS)
	@$(CC) $(CFLAGS) $(SRCS) -I$(INC) -o $(NAME)
	@echo "\033[1;92mCompiled succesfully..\033[0m"

clean:
	rm -rf  $(NAME)

fclean: clean

re: fclean all

push: fclean
	git add *
	git commit -m "Eerr"
	git push

.PHONY: all clean fclean re
