#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int fd = open("text.txt", O_RDONLY);
	char *line;
	int i;

	i = 0;
	while ((i = get_next_line(fd, &line)))
	{
		if (i == -1)
			return (0);
		printf("%s\n", line);
		free(line);
	}
	printf("%s", line);
	free(line);
	return 0;
}