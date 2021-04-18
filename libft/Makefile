# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
<<<<<<< HEAD
#    By: lelsweyr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/28 10:33:10 by lelsweyr          #+#    #+#              #
#    Updated: 2020/11/06 19:16:45 by lelsweyr         ###   ########.fr        #
=======
#    By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/28 13:42:48 by cmarsha           #+#    #+#              #
#    Updated: 2021/04/05 18:31:47 by cmarsha          ###   ########.fr        #
>>>>>>> test
#                                                                              #
# **************************************************************************** #

NAME = libft.a
<<<<<<< HEAD
COMP = gcc -Wall -Wextra -Werror
INCL = libft.h
PART_1-2 = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

OBJ_1-2 = $(PART_1-2:.c=.o)

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJ_BONUS = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_1-2)
	ar rc $(NAME) $(OBJ_1-2) $(INCL)

clean:
	rm -rf $(OBJ_1-2) $(OBJ_BONUS)

fclean: clean
	rm -rf $(NAME) 

re: fclean all

bonus: $(OBJ_1-2) $(OBJ_BONUS)
	ar rc $(NAME) $(OBJ_BONUS) $(INCL)

.PHONY: all clean fclean re bonus
=======

CC = gcc
CFLAGS = -Wall -Wextra -Werror
HEADERF = libft.h
CFILES = ft_putchar.c ft_putnbr.c ft_putstr.c ft_strcmp.c ft_atoi.c ft_swap.c \
		 ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c \
		 ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlcpy.c ft_strlcat.c \
		 ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_isalpha.c \
		 ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c \
		 ft_tolower.c ft_calloc.c ft_strdup.c ft_split.c ft_substr.c \
		 ft_strjoin.c ft_strtrim.c ft_putnbr_fd.c ft_putchar_fd.c \
		 ft_putstr_fd.c ft_itoa.c ft_strmapi.c ft_putendl_fd.c \
		 get_next_line.c ft_strcpy.c ft_lstnew.c ft_lstadd_front.c \
		 ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
		 ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_iputchar.c ft_arrjoin.c \
		 ft_arrlen.c ft_dlst.c

OBJ = $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		ar -rcs $(NAME) $(OBJ) $(HEADERF)
		ranlib $(NAME)

clean:
		/bin/rm -f $(OBJ) $(BOBJ)

fclean: clean
		/bin/rm -f $(NAME)

re: fclean all

run:
	$(CC) $(CFLAGS) -o main main.c
	./main

.PHONY: all clean fclean re bonus run
>>>>>>> test
