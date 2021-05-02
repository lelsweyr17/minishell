/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 20:50:33 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/04/29 20:30:40 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "processor.h"
# include <term.h>
# include <termios.h>
# include <termcap.h>
# include <math.h>
# include "structs.h"

void				executor(t_all *all); //, char **line);
void				pars_shift_array(char **args, int a);
int					pars_shift_line(char **line, int n);
char				*strtrim_free(char *str);
int					pars_split_commands(t_all *all);
char				*str_free(char **line, char *tmp);
int					pars_shift_line(char **line, int i);
/* minishell_utils1.c */
int					isprevempty(char *str, int begin, int last);
int					isempty(char *str, int hash);
void				pars_free(t_all *all);
/* minishell_parser2.c */
void				pars_get_args(t_all *all);
void				pars_split_args(t_all *all, t_com *com);
char				*pars_get_next_arg(t_all *all, t_com *com, char **line, int *i);
int					pars_get_com(t_com *com);
void				pars_cmp_com(t_com *com, char **commands);
/* minishell_parser3.c */
void				pars_echo_n(t_com *com);
void				pars_echo(t_com *com);
int					pars_get_env_value(char **line, char **env, int n, int i);
int					pars_dollar(t_all *all, char **line, int i, int n);
int					pars_find_quotes(t_all *all, char **line, char c, int i);

int					pars_check_redirects(t_all *all, char **line, char c, \
					int i);

int					array_size(char **ar);
/* minishell_parser4.c */
void				pars_line(t_all *all, char **line, int *i);
/* minishell_history.c */
void				hist_filling_in(t_dlist **hist, char *buf, int res, \
					int beg);
int					hist_read_file(t_dlist **hist, char *fn);
void				hist_prep(t_dlist *hist, char *fn);
void				hist_file(t_all *all);
/* minishell_termcap.c */
void				termcap_off(t_all *all);
void				termcap_on(t_all *all);
void				termcap(t_all *all);

#endif