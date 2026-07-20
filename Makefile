NAME= codexion
FLAGS= -Wall -Wextra -Werror -pthread -Isrc
COMPILER= cc
SRC_DIR= src

SRC=$(wildcard $(SRC_DIR)/*.c)

OBJ=$(SRC:.c=.o)

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