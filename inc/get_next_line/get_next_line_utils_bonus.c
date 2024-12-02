/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:44:49 by yyakuben          #+#    #+#             */
/*   Updated: 2024/11/24 20:15:25 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen_v2(char *s)
{
	size_t	counter;

	counter = 0;
	if (!s)
	{
		return (0);
	}
	while (s[counter] != '\0')
	{
		counter ++;
	}
	return (counter);
}

char	*ft_strjoin_v2(char *static_buff, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!static_buff)
	{
		free(static_buff);
		static_buff = (char *)malloc(1 * sizeof(char));
		static_buff[0] = '\0';
	}
	if (!static_buff || !buff)
		return (NULL);
	str = malloc(((ft_strlen_v2(static_buff) + ft_strlen_v2(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (static_buff)
		while (static_buff[++i] != '\0')
			str[i] = static_buff[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen_v2(static_buff) + ft_strlen_v2(buff)] = '\0';
	free(static_buff);
	return (str);
}

char	*ft_strchr_v2(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen_v2(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}
