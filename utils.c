
#include "fdf.h"

long int	ft_atoi(const char *str)
{
	long int	num;
	int			sign;
	int			i;

	num = 0;
	sign = 1;
	i = 0;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num * sign);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i])
		i++;
	return (i);
}

unsigned int	count_words(const char *str, char sep)
{
	unsigned int	count;

	count = 0;
    if (!str)
        return(count);
	while (*str)
	{
		if (*str == sep)
			str++;
		else
		{
			while (*str != sep && *str)
				str++;
			count++;
		}
	}
	return (count);
}

char	**split_with_num(char const *str, char c, int num)
{
	char			**arr;
	unsigned int	words;
	unsigned int	i;

	if (!str)
		return (NULL);
	arr = (char **)malloc((num + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = -1;
	while (*str != '\0')
	{
		if (*str == c)
			str++;
		else
		{
			words = 0;
			while (*str != c && *str && ++words)
				str++;
			arr[++i] = (char *)malloc((words + 1) * sizeof(char));
			ft_strlcpy(arr[i], str - words, words + 1);
		}
	}
	return (arr);
}
