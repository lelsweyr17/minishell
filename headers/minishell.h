/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 20:50:33 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/03 21:00:45 by lelsweyr         ###   ########.fr       */
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

/* minishell.c */
void				executor(t_all *all);
int					break_n_cycle(t_all *all, char buf[1000], int len);
void				n_cycle(t_all *all);
void				d_cycle(t_all *all);
/* minishell_input_edit.c */
void				backspase(t_all *all, t_p *p);
void				deletebutton(t_all *all, t_p *p);
char				*lineinput(t_all *all, char buf[1000], t_p *p, char *cont);
/* minishell_executor.c */
void				hist_moving(t_all *all, char buf[1000], t_dlist **hist);
char				*linemovingright(t_all *all, char buf[1000], int res);
char				*linemovingleft(t_all *all, char buf[1000], int res);
char				*linemovebywords(t_all *all, char buf[1000], int res);
void				lineedit(t_all *all, char buf[1000], t_p *p, t_dlist *hist);
/* minishell_parser1.c */
t_com				*pars_get_command(t_all *all, int start, int end);
void				pars_hash(t_all *all);
void				pars_spec_sym(t_all *all, char *c);
int					pars_split_commands(t_all *all);
char				*str_free(char **line, char *tmp);
int					pars_shift_line(char **line, int i);
/* minishell_parser2.c */
void				pars_redirects_type(t_re *re, char *line, int *i);
void				pars_redirects(t_all *all, t_com *com, char **line, int *i);
char				*pars_get_next_arg(t_all *all, t_com *com, char **line, \
					int *i);
void				pars_split_args(t_all *all, t_com *com);
void				pars_get_args(t_all *all);
/* minishell_parser3.c */
int					pars_find_pair_quote(t_all *all, char **line, char c, int i);
int					pars_find_quotes(t_all *all, char **line, char c, int i);
/* minishell_parser4.c */
void				pars_echo_n(t_com *com);
void				pars_echo(t_com *com);
int					pars_get_com(t_com *com);
void				pars_cmp_com(t_com *com, char **commands);
int					pars_line(t_all *all, char **line, int *i);
/* minishell_parser_env.c */
int					pars_get_env_value(char **line, char **env, int n, int i);
int					pars_dollar_spec(t_all *all, char **line, int n);
int					pars_dollar_get_var(t_all *all, char **line, int i, int n);
int					pars_dollar(t_all *all, char **line, int i, int n);
/* minishell_pars_syntax.c */
int					pars_check_escape(char *input, int i);
int					pars_check_prev_com(t_all *all);
void				pars_check_command(t_all *all);
int					pars_check_redirects(t_all *all, char **line, char c, \
					int i);
void				pars_syntax_error(t_all *all);
/* minishell_history.c */
int					hist_read_file(t_dlist **hist, char *fn);
void				hist_prep(t_dlist *hist, char *fn);
void				hist_file(t_all *all);
/* minishell_termcap.c */
void				termcap_off(t_all *all);
void				termcap_on(t_all *all);
void				termcap(t_all *all);
/* minishell_utils1.c */
int					isempty(char *str, int hash);
int					isprevempty(char *str, int begin, int last);
char				*str_free(char **line, char *tmp);
void				pars_free_re(t_list *lst);
void				pars_free(t_all *all);
/* minishell_utils2.c */
void				sighandler(int signr);
int					get_read(t_all *all, char *buf, int res);
void				pars_shift_array(char **args, int a);
int					pars_shift_line(char **line, int n);
char				*strtrim_free(char *str);

#endif