/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:03:49 by cmarsha           #+#    #+#             */
/*   Updated: 2021/02/07 21:01:57 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifdef BUFFER_SIZE
#  if BUFFER_SIZE > 1
#   undef BUFFER_SIZE
#   define BUFFER_SIZE 1
#  endif
#  if BUFFER_SIZE < 1
#   undef BUFFER_SIZE
#   define BUFFER_SIZE 0
#  endif
# endif
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <stdint.h>
# include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_dlist
{
	char			*cont;
	char			*dup;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

char				**arrdup(char **envp);
int					array_size(char **ar);
char				**ft_arrjoin(char **s1, char **s2);
size_t				ft_arrlen(char **s);
int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_iputchar(int c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memset(void *b, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr(int nb);
void				ft_putnbr_fd(int nb, int fd);
void				ft_putstr(char *str);
void				ft_putstr_fd(char *s, int fd);
char				**ft_split(char const *s, char c);
/* String functions */
int					ft_strcmp(char *s1, char *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strcpy(char *dst, char *src);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strndup(const char *s1, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				ft_swap(int *a, int *b);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				ft_putendl_fd(char *s, int fd);
/* Linked lists */
void				ft_dlstadd_back(t_dlist **dlst, t_dlist *new);
void				ft_dlstadd_front(t_dlist **dlst, t_dlist *new);
void				ft_dlstadd_next(t_dlist **dlst, t_dlist *new);
int					ft_dlstsize(t_dlist *dlst);
t_dlist				*ft_dlstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
int					ft_lstsize(t_list *lst);
/* OTHER */
int					get_next_line(int fd, char **line);
char				*ft_getenv(char **envp, char *key);

#endif
