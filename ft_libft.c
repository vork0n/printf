/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvirgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 13:18:07 by wpowder           #+#    #+#             */
/*   Updated: 2020/08/03 16:05:47 by cvirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_atoi(const char *nptr)
{
	int new_s;
	int negative;

	new_s = 0;
	negative = 1;
	while (*nptr == ' ' || *nptr == '\n' || *nptr == '\t' ||
		*nptr == '\v' || *nptr == '\f' || *nptr == '\r')
		nptr++;
	if (*nptr == '-')
		negative = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= 48 && *nptr <= 57)
	{
		new_s = new_s * 10 + (*nptr - 48);
		nptr++;
	}
	new_s = new_s * negative;
	return (new_s);
}

void	ft_putstr(char *str, t_parser *box)						//функция для обраротки строки (по точности по стороне и вывода на печать)
{
	int len;
	int space;

	len = ft_strlen(str);										//получаем длину строки
	if (box->precision > len || box->precision == -1)			//если точность больше чем длина
	{
		box->precision = len;									//то точность приравнивается длине
	}
	space = box->width - box->precision;					 	//для подсчета пробелов которыми надо добить ширину мы вычитаем из ширины полученную раньше точность
	if (box->minus == 0)										//если минус не изменился
	{
		ft_put_spaces_or_zero(space, box);						//забиваем пробелы
		ft_print_str(str, box);									//выводим строку
	}
	else if (box->minus == 1)									//если минус задан
	{
		ft_print_str(str, box);									//выводим строку
		ft_put_spaces_or_zero(space, box);						//забиваем пробелы
	}
}

char	*ft_strchr(const char *s, int c)
{
	char	*new_s;

	new_s = (char *)s;
	while (*new_s != c)
	{
		if (*new_s == '\0')
		{
			return (NULL);
		}
		new_s++;
	}
	return (new_s);
}

size_t	ft_strlen(const char *s)
{
	unsigned char	*new_s;
	size_t			i;

	new_s = (unsigned char *)s;
	i = 0;
	while (new_s[i] != '\0')
		i++;
	return (i);
}

void	ft_putnbr(int n, int fd, t_parser *box)
{
	const int base = 10;

	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-', box);
		n = -n;
	}
	if (n < base)
		ft_putchar(n + '0', box);
	if (n >= base)
	{
		ft_putnbr(n / base, fd, box);
		ft_putchar(n % base + '0', box);
	}
}
