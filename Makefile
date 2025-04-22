NAME = minishell

SRC =  parsing/parsing.c parsing/struct_utils.c parsing/struct_utils2.c parsing/parse_utils.c \
parsing/check_parse.c exec/exec.c exec/exec_utils.c parsing/ft_split_minishell.c parsing/parse_utils2.c \
exec/main.c exec/get_next_line.c exec/get_next_line_utils.c exec/process.c exec/utils.c parsing/ft_split_minishell_utils.c \
parsing/parse_file.c parsing/parse_quotes.c parsing/parse_quotes_utils.c  parsing/get_env_var.c \
parsing/big_free.c parsing/get_env_var_utils.c  parsing/get_env_var_utils2.c parsing/cpy_env_var.c builtins/ft_pwd.c \
builtins/ft_echo.c builtins/ft_exit.c builtins/ft_cd.c builtins/ft_env.c builtins/ft_unset.c  builtins/ft_export.c signals/signals.c exec/get_path.c \
exec/file.c exec/exec_utils_2.c exec/here_doc.c builtins/ft_utils.c

CC = cc -Ilibft -Iincludes -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft bonus
	make -C libft
	$(CC) $(OBJ) -Llibft -l:libft.a -lreadline -o $(NAME)

.c.o:
		$(CC) -c $< -o $(<:.c=.o)

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
