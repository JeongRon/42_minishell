# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/13 17:36:01 by dongmiki          #+#    #+#              #
#    Updated: 2023/08/22 16:24:38 by dongmiki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror 
LIBFT = Libft
LIBRL =  -L/Users/dongmiki/.brew/opt/readline/lib -lreadline
NAME = minishell
SRCS = minishell.c \
		minishell_utils.c \
		minishell_error.c \
		minishell_input/minishell_input.c \
		minishell_input/minishell_input_token.c \
		minishell_input/minishell_input_quote.c \
		minishell_input/minishell_input_utils.c \
		minishell_input/minishell_split_quote.c \


OBJS = $(SRCS:.c=.o)
HEAD = minishell.h

all : $(NAME)

bonus : $(NAME)

$(NAME) : $(OBJS) $(HEAD)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) Libft/libft.a $(OBJS) -o $@ $(LIBRL)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -I./ -o $@

clean :
	rm -f $(OBJS)
	rm -f *.a
	make clean -C $(LIBFT)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re : fclean all

.PHONY : all clean fclean bonus re