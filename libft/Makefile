# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: helvi <helvi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 12:00:35 by hlaineka          #+#    #+#              #
#    Updated: 2021/02/25 12:37:13 by helvi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

OBJS = objs/*.o

INC = 	includes/ft_error.h \
		includes/ft_exit.h \
		includes/ft_printf.h \
		includes/libft.h \
		includes/lists.h \
		includes/misc.h \
		includes/stringarrays.h \
		includes/strings.h


all: $(NAME)

$(NAME):
	@cd libft && make -s
	@cd printf && make -s
	@cd ft_exit && make -s
	@cd ft_error && make -s
	@cd lists && make -s
	@cd misc && make -s
	@cd stringarrays && make -s
	@cd strings && make -s
	@ar rc $(NAME) $(OBJS) $(INC)

debug:
	@cd libft && make -s
	@cd printf && make -s
	@cd ft_exit && make -s
	@cd ft_error && make -s
	@cd lists && make -s
	@ar rc $(NAME) $(OBJS) $(INC)

clean:
	@rm -f $(OBJS)
	@echo library object files removed.

fclean:
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@echo library .a file removed. Object folder removed.

re: fclean all
