#include "../headers/minishell.h"

int	hist_read_file(t_dlist **hist, char *fn)
{
	int		fd;
	char	*line;

	fd = open(fn, O_RDONLY);
	if (fd < 3)
		return (0);
	while (get_next_line(fd, &line) > 0)
		ft_dlstadd_back(hist, ft_dlstnew(line));
	if (line)
		free(line);
	if (!hist)
		return (0);
	while ((*hist)->next)
	{
		(*hist)->dup = ft_strdup((*hist)->cont);
		*hist = (*hist)->next;
	}
	(*hist)->dup = ft_strdup((*hist)->cont);
	return (1);
}

void	hist_prep(t_dlist *hist, char *fn)
{
	char	*changedhist;
	int		fd;

	if (hist->next)
	{
		changedhist = hist->cont;
		hist->cont = ft_strdup(hist->dup);
		while (hist->next)
			hist = hist->next;
		if (hist->cont)
			free(hist->cont);
		hist->cont = changedhist;
	}
	hist->dup = ft_strdup(hist->cont);
	fd = open(fn, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd)
	{
		write(fd, hist->cont, ft_strlen(hist->cont));
		write(fd, "\n", 1);
	}
	close(fd);
}

void	hist_file(t_all *all)
{
	all->hist = 0;
	all->fn = getenv("HOME");
	if (all->fn)
		all->fn = ft_strjoin(all->fn, "/.SSSshelkers_hist");
	if (!all->fn || !hist_read_file(&all->hist, all->fn))
		ft_dlstadd_back(&all->hist, ft_dlstnew(ft_strdup("")));
}
