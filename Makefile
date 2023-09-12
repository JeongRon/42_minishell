# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dongmiki <dongmiki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/13 17:36:01 by dongmiki          #+#    #+#              #
#    Updated: 2023/09/12 18:12:35 by dongmiki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = Libft
LIBRL =  -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
NAME = minishell
SRCS = minishell.c \
		minishell_signal.c \
		minishell_utils.c \
		minishell_error.c \
		minishell_gnl_utils.c\
		minishell_gnl.c\
		minishell_input/minishell_input.c \
		minishell_input/minishell_input_token.c \
		minishell_input/minishell_input_quote.c \
		minishell_input/minishell_input_utils.c \
		minishell_input/minishell_split_quote.c \
		minishell_excute/minishell_util.c\
		minishell_excute/minishell_child.c\
		minishell_excute/minishell_excute_main.c\
		minishell_excute/minishell_exec.c\
		minishell_excute/minishell_set_redirection.c\
		minishell_built_in/utils/utils_add.c\
		minishell_built_in/utils/utils_check.c\
		minishell_built_in/utils/utils_del.c\
		minishell_built_in/utils/utils_lib.c\
		minishell_built_in/utils/utils_malloc.c\
		minishell_built_in/utils/utils_mini.c\
		minishell_built_in/utils/utils_split.c\
		minishell_built_in/utils/utils_makeinfile.c\
		minishell_built_in/cd.c\
		minishell_built_in/check_cmd.c\
		minishell_built_in/echo.c\
		minishell_built_in/env.c\
		minishell_built_in/exit.c\
		minishell_built_in/export.c\
		minishell_built_in/pwd.c\
		minishell_built_in/set_env_var.c\
		minishell_built_in/sort_exp.c\
		minishell_built_in/unset.c\

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