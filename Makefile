# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbaelor- <bbaelor-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/09 20:53:51 by bwerewol          #+#    #+#              #
#    Updated: 2019/02/20 20:46:23 by bbaelor-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_ls
SRCS		=	main.c\
				ft_ls.c\
				ft_ls_func.c\
				ft_setflags.c\
				ft_sorts_1.c\
				ft_sorts_2.c\
				ft_print_long.c\
				ft_func_array.c\
				ft_align_attr.c\
				ft_err_msg.c\
				ft_put_name.c\
				ft_print_lines.c\
				ft_print_newline.c\
				ft_print_column.c\
				ft_put_mode.c\
				ft_put_usrgrp.c\
				ft_put_size.c\
				ft_param_len.c\
				ft_print_attr.c
OBJS		=	$(SRCS:.c=.o)
INCS		=	-I . -I libft/includes/
INCSFS		=	ft_ls.h
LIBS		=	-L libft/ -lft
FLAGS		=	-Wall -Wextra -Werror
FLAGS		+=	-O3
# FLAGS		+=	-g

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	gcc $(OBJS) $(LIBS) $(INCS) $(FLAGS) -o $(NAME)

$(OBJS): $(INCSFS)

%.o: %.c
	gcc $(INCS) $(FLAGS) -o $@ -c $<

clean:
	make clean -C libft
	rm -rf $(OBJS)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all
