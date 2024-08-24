# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/21 11:43:39 by vsharma           #+#    #+#              #
#    Updated: 2024/08/21 13:36:59 by vsharma          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c \
		builtins/builtin.c builtins/builtin_utils.c \
		builtins/echo.c builtins/env.c builtins/exit.c \
		builtins/ft_cd.c builtins/ft_export.c builtins/pwd.c \
		builtins/unset.c \
		execution/binaries.c execution/binaries_utils.c \
		execution/execute.c execution/pipe_execution.c \
		execution/redirections.c execution/redirections1.c \
		execution/utils_linked_lists.c \
		parser/parser.c  parser/env_var.c \
		parser/expander.c parser/handel_quotes.c \
		signals/signals.c \
		utils/utils_list.c utils/utils_parser.c \
		utils_libft/ft_atoi.c utils_libft/ft_putchar_fd.c \
		utils_libft/ft_putendl_fd.c utils_libft/ft_putstr_fd.c \
		utils_libft/ft_putchar_fd.c utils_libft/ft_split.c \
		utils_libft/ft_strchr.c utils_libft/ft_strjoin.c \
		utils_libft/ft_strtrim.c utils_libft/ft_strncpy.c \
		utils_libft/ft_strdup.c utils_libft/ft_strlen.c \
		utils_libft/ft_strncmp.c utils_libft/ft_substr.c \
		utils_libft/ft_strcmp.c utils_libft/ft_putstr_fd.c \
		utils_libft/ft_isspace.c signals/signals.c \
		utils_libft/ft_putnbr_fd.c utils_libft/ft_isalnum.c \
		utils_libft/ft_isalpha.c utils_libft/ft_isdigit.c \
		validation/input_validation.c validation/cleanup.c \


OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAG = -lreadline

BLUE = \033[1;34m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAG)
	@echo "$(BLUE) excutable ./$(NAME) is created $(RESET)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re