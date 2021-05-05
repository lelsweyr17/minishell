# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/28 13:42:48 by cmarsha           #+#    #+#              #
#    Updated: 2021/05/04 14:56:34 by lelsweyr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft/libft.a
CC = gcc
CFLAGS = -g
TFLAGS = -ltermcap
HEADERF = minishell.h processor.h structs.h
CFILES = parser/minishell.c \
	parser/minishell_executor.c \
	parser/minishell_history.c \
	parser/minishell_termcap.c \
	parser/minishell_parser1.c \
	parser/minishell_parser2.c \
	parser/minishell_parser3.c \
	parser/minishell_parser4.c \
	parser/minishell_pars_syntax.c \
	parser/minishell_parser_env.c \
	parser/minishell_utils1.c \
	parser/minishell_utils2.c \
	processor/start/processor1.c \
	processor/start/processor2.c \
	processor/export/export1.c \
	processor/export/export2.c \
	processor/export/export3.c \
	processor/unset/unset1.c \
	processor/unset/unset2.c \
	processor/env/env.c \
	processor/cd/cd1.c \
	processor/cd/cd2.c \
	processor/pwd/pwd.c \
	processor/echo/echo.c \
	processor/exit/exit.c \
	processor/prepare/pre_processor1.c \
	processor/prepare/pre_processor2.c \
	processor/bin/bin_command1.c \
	processor/bin/bin_command2.c \
	processor/bin/bin_command3.c \
	processor/bin/bin_command4.c \
	processor/bin/bin_command5.c \
	processor/error/errors.c \
	processor/pipe/pipe1.c \
	processor/pipe/pipe2.c \
	processor/redirect/redirect1.c \
	processor/redirect/redirect2.c

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
	$(MAKE) fclean -C libft

fclean: clean
	/bin/rm -f $(NAME)
	$(MAKE) fclean -C libft

re: fclean all

run:
	$(CC) $(CFLAGS) -o mmr *.c $(TFLAGS)
	./mmr

arina: $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LIBFT) $(TFLAGS) -o $(NAME)

deb:
	$(CC) -g -o deb *.c libft/*.c $(TFLAGS)
	./deb

cl:
	$(CC) -g -o cl *.c libft/*.c $(TFLAGS)

debb:
	$(CC) $(CFLAGS) -g -o debb *.c libft/*.c $(TFLAGS)
	./debb

s:
	cp Makefile .gitignore l/
	cp -r libft l/
	cp -r parser l/
	cp -r processor l/
	cp -r headers l/
	