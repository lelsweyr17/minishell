# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/28 13:42:48 by cmarsha           #+#    #+#              #
#    Updated: 2020/12/26 22:20:52 by cmarsha          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mmm
LIBFT = libft/libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
TFLAGS = -ltermcap
HEADERF = minishell.h parser.h
CFILES = minishell.c minishell_parser.c minishell_utils.c
BFILES = bonus_minishell.c
OBJ := $(CFILES:.c=.o)
BOBJ := $(BFILES:.c=.o)

.PHONY: all clean fclean re run deb debb lin w s

all: $(NAME)

%.o : %.c $(HEADERF)
	$(CC) -c $< -o $@
		
$(LIBFT):
	$(MAKE) -C libft

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LIBFT) $(TFLAGS) -o $(NAME)

bonus: $(LIBFT) $(BOBJ)
	$(CC) $(BOBJ) $(CFLAGS) $(LIBFT) $(TFLAGS) -o $(NAME)

clean:
	/bin/rm -f $(OBJ) $(BOBJ)
	$(MAKE) clean -C libft

fclean: clean
	/bin/rm -f $(NAME)
	$(MAKE) fclean -C libft

re: fclean all

run:
	$(CC) $(CFLAGS) -o mmr *.c $(TFLAGS)
	./mmr

deb:
	$(CC) -g -o deb *.c libft/*.c $(TFLAGS)
	./deb

cl:
	$(CC) -g -o cl *.c libft/*.c $(TFLAGS)

debb:
	$(CC) $(CFLAGS) -g -o debb *.c libft/*.c $(TFLAGS)
	./debb

s:
	cp Makefile minishell* .gitignore l/
	cp libft/* l/libft/