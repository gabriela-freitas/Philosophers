NAME = philosophers

SRC =	main.c \
		parse.c \
		libft.c \
		utils.c

INC = -I .
LIB = -lpthread

CC = gcc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address

RM = rm -f

COLOUR_GREEN=\033[7;1;32m
COLOUR_YELLOW=\033[7;1;33m
COLOUR_END=\033[0m

$(NAME): $(OBJS)
	@ $(CC) $(FLAGS) $(INC) $(SRC) $(LIB) -o $(NAME)
	@echo "$(COLOUR_GREEN) $(NAME) is ready to use $(COLOUR_END)"

all : $(NAME)

clean:
	@ $(RM) $(NAME)

fclean: clean
	@echo "$(COLOUR_YELLOW) $(NAME) cleaned $(COLOUR_END)"

test: clean all
	./$(NAME) 20 100 50 200

valgrind: clean all
	valgrind ./$(NAME)

valgrindfull: re
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

re: fclean all

.PHONY: clean fclean all re
