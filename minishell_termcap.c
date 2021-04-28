#include "minishell.h"

void	termcap_off(t_all *all)
{
	all->term.c_lflag &= ~(ECHO);
	all->term.c_lflag &= ~(ISIG);
	all->term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &all->term);
}

void	termcap_on(t_all *all)
{
	all->term.c_lflag |= ECHO;
	all->term.c_lflag |= ISIG;
	all->term.c_lflag |= ICANON;
	tcsetattr(0, TCSANOW, &all->term);
}

void	termcap(t_all *all)
{
	char			*termname;

	tcgetattr(0, &all->term);
	// all->term.c_lflag &= ~(ECHO);
	// all->term.c_lflag &= ~(ISIG);
	// all->term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &all->term);
	termname = getenv("TERM");
	if (!termname)
		termname = "xterm-256color";
	tgetent(0, termname);	
}
