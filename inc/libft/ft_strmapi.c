/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaroslav <yaroslav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 20:51:50 by yyakuben          #+#    #+#             */
/*   Updated: 2024/12/17 18:53:06 by yaroslav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	// unsigned int	len;
	char			*str;

	i = 0;
	// len = 0;
	if (!s || !f)
		return (0);
	str = (char *)malloc(ft_strlen(s) + 1);
	// len = ft_strlen(s);
	if (!str)
		return (0);
	while (s[i])
	{
		str[i] = f(i, (char)s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
