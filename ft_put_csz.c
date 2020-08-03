/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_csz.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvirgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:43:24 by wpowder           #+#    #+#             */
/*   Updated: 2020/08/03 15:49:48 by cvirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_spaces_or_zero(int i, t_parser *box)						//выводим или пробелы или нули
{
	if (box->zero == 0 || (box->zero == 1 && box->minus == 1))			//
	{
		while (i > 0)													//
		{
			ft_putchar(' ', box);
			i--;
		}
	}
	else if (box->zero == 1)
	{
		while (i > 0)
		{
			ft_putchar('0', box);
			i--;
		}
	}
}

void	ft_put_zeros(int i, t_parser *box)
{
	while (i > 0)
	{
		ft_putchar('0', box);
		i--;
	}
}

void	ft_put_c(char c, t_parser *box)				//обработка одиночного символа
{
	int	space;

	space = box->width - 1;							//-1 символ +  9 spaces  = 10 
	if (box->minus == 0)							//если нет минуса							
	{
		ft_put_spaces_or_zero(space, box);			//печатает пробелы 	 box - для переброса  count
		ft_putchar(c, box);							
	}
	else											//если есть минус 
	{
		ft_putchar(c, box);							//печает символ
		ft_put_spaces_or_zero(space, box);			//печатает пробелы 	 box - для переброса  count
	}
}													//если 0 - неопределенное поведение
