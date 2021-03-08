# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: helvi <helvi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 12:00:35 by hlaineka          #+#    #+#              #
#    Updated: 2021/03/05 11:56:35 by helvi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = ft_select

_SRC = 	ft_select.c \
		rawmode.c \
		print.c \
		cursor.c \
		read.c \
		read_helpers.c \
		arrows.c \
		helpers.c \
		signal.c

_OBJ = $(_SRC:.c=.o)
_INC = ft_select.h
_LIBFT = libft.a

SRC_DIR = src
OBJ_DIR = objs
INC_DIR = includes
LIBFT_DIR = libft

SRC = $(patsubst %,$(SRC_DIR)/%,$(_SRC))
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))
INC = $(patsubst %,$(INC_DIR)/%,$(_INC))
LIBFT = $(patsubst %,$(LIBFT_DIR)/%,$(_LIBFT))

INC_LIBFT = -I libft/includes
INC_TERMCAPS = -ltermcap

FLAGS = -Wall -Wextra -Werror -g -I $(INC_DIR) $(INC_LIBFT) $(INC_TERMCAPS)
DEBUG_FLAGS = -Wall -Wextra -Werror -g -I $(INC_DIR) $(INC_LIBFT)

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	@echo "\n"object files made."\n"
	@cd $(LIBFT_DIR) && make -s
	@echo libraries ready.
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)
	@echo compiled!

debug: $(OBJ_DIR) $(OBJ)
	@echo "\n"object files made."\n"
	@cd $(LIBFT_DIR) && make -s debug
	@$(CC) $(DEBUG_FLAGS) -o $(NAME) $(OBJ) $(LIBFT)
	@echo minishell compiled with -g.

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC)
	@printf "|"
	@$(CC) $(DEBUG_FLAGS) -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

lib:
	@cd $(LIBFT_DIR) && make -s

clean:
	@rm -f $(OBJ)
	@echo minishell object files removed.
	@cd $(LIBFT_DIR) && make -s clean
	@find . -type f -name '.DS_Store' -delete
	@find . -type f -name '*~' -print -delete -o -name "#*#" -print -delete

fclean: clean
	@rm -f $(NAME)
	@cd $(LIBFT_DIR) && make -s fclean
	@rm -rf $(OBJ_DIR)
	@echo minishell removed. Object folder removed.
	

re: fclean all
