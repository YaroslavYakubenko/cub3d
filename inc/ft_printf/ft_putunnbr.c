/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 22:36:15 by yyakuben          #+#    #+#             */
/*   Updated: 2023/12/22 22:36:15 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunnbr(unsigned int num)
{
	int	count;

	count = 0;
	if (num < 10)
		count += ft_putchar(num + '0');
	else
	{
		count += ft_putunnbr(num / 10);
		count += ft_putunnbr(num % 10);
	}
	return (count);
}
