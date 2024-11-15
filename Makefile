# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/21 11:43:39 by vsharma           #+#    #+#              #
#    Updated: 2024/09/14 14:10:24 by vsharma          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c \
		builtins/builtin.c builtins/builtin_utils.c \
		builtins/echo.c builtins/env.c builtins/exit.c \
		builtins/cd.c builtins/export.c builtins/pwd.c \
		builtins/unset.c \
		execution/system_commands.c \
		execution/execute_handler.c execution/execute_pipeline.c \
		redirections/redirections_handler.c redirections/heredoc_handler.c \
		redirections/heredoc_utils.c redirections/filename_generator.c \
		redirections/redirections_input_output.c \
		parser/env_list.c  parser/expander_utils.c parser/expander.c \
		parser/handel_quotes.c parser/parser.c  parser/tokenizer.c \
		signals/signals.c signals/signal_heredoc.c \
		utils/cmd_list_utils.c utils/list_utils.c \
		utils/num_utils.c utils/string_utils.c \
		utils/var_utils.c \
		utils_libft/ft_putchar_fd.c utils_libft/ft_putendl_fd.c \
		utils_libft/ft_putstr_fd.c utils_libft/ft_putchar_fd.c \
		utils_libft/ft_split.c utils_libft/ft_strchr.c \
		utils_libft/ft_strjoin.c utils_libft/ft_strncpy.c \
		utils_libft/ft_strdup.c utils_libft/ft_strlen.c \
		utils_libft/ft_substr.c utils_libft/ft_putstr_fd.c \
		utils_libft/ft_isspace.c signals/signals.c \
		utils_libft/ft_isalnum.c utils_libft/ft_isdigit.c \
		utils_libft/ft_strrchr.c utils_libft/ft_strlcpy.c \
		utils_libft/ft_strlcat.c utils_libft/ft_strncmp.c \
		utils_libft/ft_bzero.c \
		validation/input_handeling.c validation/cleanup.c \
		validation/validation_syntax.c 


OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAG = -lreadline

BLUE = \033[1;34m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAG)
	@echo "$(BLUE) ./$(NAME) ready !! $(RESET)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
