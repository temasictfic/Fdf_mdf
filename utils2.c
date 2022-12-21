#include "fdf.h"

char	*ft_toupper(char *str)
{
	int i;
	char *s;
	size_t len;
	
	len = ft_strlen(str);
	s = malloc(sizeof(char)* (len + 1));
	s[len] = '\0';
	i = 0;
	while(str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		    s[i] = str[i] - 32;
		else
		    s[i] = str[i];
		i++;
	}
	return (s);
}

int	nb_base(char str, char *base)
{
	int	nb;

	nb = 0;
	while (base[nb] != '\0')
	{
		if (str == base[nb])
			return (nb);
		nb++;
	}
	return (-1);
}

unsigned int	ft_atoi_hex(char *str)
{
	int	i;
	int	nb;
	char *up_str;

	nb = 0;
	i = 0;
	up_str = ft_toupper(str);
	while (up_str[i])
		nb = (nb * 16) + nb_base(up_str[i++], "0123456789ABCDEF");
	free(up_str);
	return (nb);
}