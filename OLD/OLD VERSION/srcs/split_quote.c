/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilin <yilin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:51:05 by yilin             #+#    #+#             */
/*   Updated: 2024/09/24 17:08:27 by yilin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


static int	ft_strchop(char **arr, char *start, char *end, int index)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc((end - start + 1) * sizeof(char));
	if (!str)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
		return (0);
	}
	ft_strlcpy(str, start, end - start + 1);
	arr[index] = str;
	return (1);
}

static char	*ft_find_next_quote(char **arr, char *s, int *index)
{
	char	*next_quote;

	next_quote = ft_strchr(s + 1, '\'');
	if (next_quote - s > 1)
	{
		if (!ft_strchop(arr, s + 1, next_quote, *index))
			return (NULL);
		*index += 1;
	}
	return (next_quote);
}

static void	ft_assign_arr(char **arr, char *s, char c)
{
	int		j;
	char	*anchor;

	j = 0;
	anchor = s;
	while (*s)
	{
		if (*s == c || *s == '\'')
		{
			if (s - anchor > 0)
				if (!ft_strchop(arr, anchor, s, j++))
					return ;
			if (*s == '\'')
			{
				s = ft_find_next_quote(arr, s, &j);
				if (!s)
					return ;
			}
			anchor = s + 1;
		}
		s++;
	}
	if (s - anchor > 0)
		if (!ft_strchop(arr, anchor, s, j++))
			return ;
}

static int	ft_count_subset(char *s, char c)
{
	int		cnt;
	char	*anchor;

	cnt = 0;
	anchor = s;
	while (*s)
	{
		if (*s == c || *s == '\'')
		{
			if (s - anchor > 0)
				cnt++;
			if (*s == '\'')
			{
				if (ft_strchr(s + 1, '\'') - s > 1)
					cnt++;
				s = ft_strchr(s + 1, '\'');
			}
			anchor = s + 1;
		}
		s++;
	}
	if (s - anchor > 0)
		cnt++;
	return (cnt);
}

char	**ft_split_quote(char const *s, char c)
{
	char	**arr;
	int		n_subset;

	n_subset = ft_count_subset((char *)s, c);
	arr = (char **)malloc((n_subset + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	ft_assign_arr(arr, (char *)s, c);
	if (!arr)
		return (NULL);
	arr[n_subset] = NULL;
	return (arr);
}