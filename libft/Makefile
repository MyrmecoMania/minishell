# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root <root@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 15:17:56 by enorie            #+#    #+#              #
#    Updated: 2024/01/14 12:25:42 by root             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAG = -Wall -Wextra -Werror

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c    \
ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c  \
ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c  \
ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_striteri.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_split.c ft_itoa.c

SRC_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

.c.o:
		cc $(FLAG) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
		ar -rc -o $(NAME) $(OBJ)

bonus: $(OBJ_BONUS)
		ar -rc -o $(NAME) $(OBJ_BONUS)

all: $(NAME)

clean:
		rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
