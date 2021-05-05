/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 20:50:40 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/05/04 16:08:45 by lelsweyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libft/libft.h"
# include "minishell.h"

typedef struct s_pipe
{
	int				i;
	int				std_in;
	int				std_out;
	int				**fd;
	pid_t			*pid;
	int				pipe_num;
}	t_pipe;

typedef struct s_bin
{
	char			*path;
	int				fd[2];
	int				type[3];
	int				std_in;
	int				std_out;
}	t_bin;

typedef struct s_proc
{	
	int				build_in;
	char			*arg;
	int				error;
	char			*pwd;
	int				slesh;
	char			**ex_port;
	char			**bin;
	char			*com;
	int				*tmp;
	int				tmpp;
	t_bin			bin_exec;
}	t_proc;

typedef struct s_re
{
	char			*fn;
	int				type;
}	t_re;

typedef struct s_com
{
	int				type;
	int				n;
	char			pipsem;
	int				place;
	char			*line;
	char			**args;
	int				pipamount;
	t_list			*re;
}	t_com;

typedef struct s_p
{
	int				i;
	int				st;
	int				nl;
	int				len;
	int				res;
	int				pos;
	int				ctrld;
}	t_p;

typedef struct s_all
{
	t_dlist			*hist;
	t_list			*lst;
	t_p				*p;
	t_proc			*proc;
	char			**env;
	char			*fn;
	char			*input;
	char			*end;
	int				delescape;
	int				pid;
	int				nl;
	int				el;
	int				res;
	struct termios	term;
}	t_all;

#endif
