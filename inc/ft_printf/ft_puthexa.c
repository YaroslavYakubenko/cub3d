/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 19:40:03 by yyakuben          #+#    #+#             */
/*   Updated: 2023/12/23 19:40:03 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthexa(unsigned int num, char format)
{
	int	count;

	count = 0;
	if (num >= 16)
	{
		count += ft_puthexa(num / 16, format);
		count += ft_puthexa(num % 16, format);
	}
	else
	{
		if (num < 10)
			count += ft_putchar(num + 48);
		else if (format == 'X')
			count += ft_putchar(num + 55);
		else if (format == 'x')
			count += ft_putchar(num + 87);
	}
	return (count);
}
