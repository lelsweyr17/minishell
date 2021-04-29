/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelsweyr <lelsweyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 20:50:40 by lelsweyr          #+#    #+#             */
/*   Updated: 2021/04/29 20:29:52 by lelsweyr         ###   ########.fr       */
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

typedef struct s_par
{
	int				i;
	int				st;
	int				sem;
}	t_par;

typedef struct s_all
{
	t_list			*lst;
	t_dlist			*hist;
	t_par			par;
	char			*input;
	char			**env;
	char			*fn;
	struct termios	term;
}	t_all;

#endif 