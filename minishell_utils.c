int	isnotempty(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n')
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}