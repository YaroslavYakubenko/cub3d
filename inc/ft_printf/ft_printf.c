/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:55:10 by yyakuben          #+#    #+#             */
/*   Updated: 2023/12/18 17:55:10 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_case(char c, va_list factor)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar(va_arg(factor, int));
	else if (c == 's')
		count += ft_putstr(va_arg(factor, char *));
	else if (c == 'p')
	{
		count += ft_putstr("0x");
		count += ft_putpnbr(va_arg(factor, unsigned long long));
	}
	else if (c == 'd' || c == 'i')
		count += ft_putnbr(va_arg(factor, int));
	else if (c == 'u')
		count += ft_putunnbr(va_arg(factor, int));
	else if (c == 'x' || c == 'X')
		count += ft_puthexa(va_arg(factor, int), c);
	else if (c == '%')
		count += ft_putchar('%');
	else
		count += ft_putchar(c);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, format);
	if (!format)
		return (0);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[i] == '\0')
				return (i);
			count += ft_case(format[i + 1], args);
			i++;
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}

// int main(void)
// {
//     char    letter;
//     int     r_value;
//     int     r_value2;

//     letter = 'a';

//     // Using C standart printf function
//     printf("\n\tUsing printf\n");
//     // r_value = printf("Print c and s: %c %s\n", letter, "str");
//     printf("r_value is %d and %i\n", r_value, r_value);
//     printf("Print s: %s\n", "str");
//     printf("Print hexa is %x and %X\n", 10, 10);
//     printf("Print unsigned int is: %u\n", 11);
//     printf("Print pointer is: %p\n", 100000);
//     printf("Print percent is: %%\n");

//     // Using ft_printf function
//     ft_printf("\n\tUsing ft_printf\n");
//     // r_value2 = (ft_printf("Print c and s: %c %s\n", letter, "str"));
//     ft_printf("r_value2 is %d and %i\n", r_value2, r_value2);
//     ft_printf("Print s: %s\n", "str");
//     ft_printf("Print hexa is %x and %X\n", 10, 10);
//     ft_printf("Print unsigned int is: %u\n", 11);
//     ft_printf("Print pointer is: %p\n", 100000);
//     ft_printf("Print percent is: %%\n");

//     return (0);
// }
