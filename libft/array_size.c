#include "libft.h"

int	array_size(char **ar)
{
	int	i;

	i = 0;
	while (ar[i])
		i++;
	return (i);
}
