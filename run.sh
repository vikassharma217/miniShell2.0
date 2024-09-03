#!/bin/bash

#norminette -RCheckForbiddenHeader

make re

valgrind --suppressions=leaks.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell

make fclean