/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_split_whitespaces.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/09 18:58:40 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/09 18:58:48 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

int		is_separator(char c, char is_char)
{
	if (is_char)
		return ((c >= 'a' && c <= 'z')
				|| (c >= 'A' && c <= 'Z')
				|| (c >= '0' && c <= '9'));
	return (c == ' ' || c == '\t' || c == '\n');
}

int		get_word_size(char *str, int pos)
{
	int i;

	i = 0;
	while (is_separator(str[pos], 0) && str[pos] != '\0')
		pos++;
	while (is_separator(str[pos], 1) && str[pos] != '\0')
	{
		i++;
		pos++;
	}
	return (i);
}

int		get_words_index(char *str, int nb)
{
	int i;
	int words;

	i = 0;
	words = 0;
	if (nb == 0)
	{
		while (is_separator(str[i], 0))
			i++;
		return (i);
	}
	while (str[i])
	{
		if (is_separator(str[i - 1], 0) && is_separator(str[i], 1))
			words++;
		if (words == 0 && words == nb && !is_separator(str[i], 0))
			return (i);
		if (words == nb + 1)
			return (i);
		i++;
	}
	return (0);
}

int		count_words(char *str)
{
	int			i;
	int			words;

	i = 0;
	words = 0;
	if (is_separator(str[0], 1))
		words++;
	while (str[i])
	{
		if (is_separator(str[i - 1], 0) && is_separator(str[i], 1))
			words++;
		i++;
	}
	return (words);
}

char	**ft_split_whitespaces(char *str)
{
	int		count_w;
	int		i;
	int		j;
	char	**tab;
	int		word_index;

	count_w = count_words(str);
	tab = (char **)malloc(sizeof(char *) * count_w + 1);
	i = 0;
	while (i < count_w)
	{
		word_index = get_words_index(str, i);
		tab[i] = (char *)malloc(sizeof(char) * get_word_size(str, word_index));
		j = 0;
		while (j < get_word_size(str, word_index))
		{
			tab[i][j] = str[word_index + j];
			j++;
		}
		tab[i][j] = 0;
		i++;
	}
	tab[i] = 0;
	return (tab);
}
