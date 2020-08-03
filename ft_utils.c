/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvirgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 14:26:43 by wpowder           #+#    #+#             */
/*   Updated: 2020/08/03 16:04:20 by cvirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, t_parser *box)
{
	write(1, &c, 1);
	box->count += 1;									//увеличиваем  box->count на ++
}

void	ft_print_str(char *str, t_parser *box)			//вывод строки пока есть точность
{
	while (str && box->precision--)             		//уменьшаем точность, пока она есть цикл работает
	{
		ft_putchar(*str, box);							//выводим символ, на котором висит указатель
		str++;											//увеличиваем указатель str
	}
}

int	ft_get_x_len(unsigned long dec)
{
	int	i;

	i = 0;
	if (dec == 0)
		i++;
	while (dec > 0)
	{
		dec /= 16;
		i++;
	}
	return (i);
}

int	ft_get_diu_len(unsigned int dec)
{
	int	i;

	i = 0;
	if (dec == 0)
		i++;
	while (dec > 0)
	{
		dec /= 10;
		i++;
	}
	return (i);
}
