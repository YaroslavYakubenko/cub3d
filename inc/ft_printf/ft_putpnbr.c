/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 23:00:18 by yyakuben          #+#    #+#             */
/*   Updated: 2023/12/22 23:00:18 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putpnbr(unsigned long long num)
{
	int	count;

	count = 0;
	if (num <= 0)
	{
		count += ft_putchar('-');
		num = -num;
	}
	else if (num < 10)
		count += ft_putchar(num + 48);
	else if (num < 16)
		count += ft_putchar(num + 87);
	else
	{
		count += ft_putpnbr(num / 16);
		count += ft_putpnbr(num % 16);
	}
	return (count);
}
