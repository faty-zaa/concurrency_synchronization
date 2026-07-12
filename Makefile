NAME= codexion
FLAGS= -Wall -Wextra -Werror -pthread
COMPILER= cc
FILES= $(wildcard *.c)

OBJ=$(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(COMPILER) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	@$(COMPILER) $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY:
	all clean fclean re