/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_dip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvirgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 14:54:31 by wpowder           #+#    #+#             */
/*   Updated: 2020/08/03 19:19:59 by cvirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_di_util(int minus, int space, t_parser *box)		//порядок выравнивания 
{
	if (box->zero && minus)
		ft_putchar('-', box);
	if (box->minus == 0)
		ft_put_spaces_or_zero(space, box);
	if (!box->zero && minus)
		ft_putchar('-', box);
}

void	ft_put_di(int n, t_parser *box)
{
	int	len;
	int	minus;
	int	p_zero;
	int	space;

	minus = 0;
	if (n < 0)
	{
		n *= -1;
		minus = 1;										//это НЕ ФЛАГ а знак числа
	}
	len = ft_get_diu_len(n);								//получаем длину десятичного числа
	if (n == 0 && box->precision == 0)					//если 0 число и точность
		len = 0;										//то длина 0 и ничего не печатаем
	p_zero = box->precision - len;						//получаем число нулей
	if (p_zero > 0)										//если точность больше длины то
		space = box->width - minus - box->precision;	//получаем число пробелов, если есть minus(он занимает место), поэтому мы его вычитаем из ширины
	else
		space = box->width - minus - len;				//если точность не больше длины то вычитаем из ширины длину с учетом минуса
	ft_put_di_util(minus, space, box);					//порядок выравнивания пробелами либо нулями 
	ft_put_zeros(p_zero, box);							//записываем нули
	if (len != 0)										//
		ft_put_u(n, box);								//выводим беззнаковое число
	if (box->minus == 1)								//
		ft_put_spaces_or_zero(space, box);				//выводим пробелы если задан флаг минус
}

void	ft_put_p(unsigned long p, t_parser *box)	//поддерживаем 8байт
{
	int		space;
	int		len;
	int		p_zero;

	len = ft_get_x_len(p);							
	if (p == 0 && box->precision == 0)				//костыль на случай нулево	 точности
		len = 0;									
	p_zero = box->precision - len;					
	if (p_zero > 0)									
		space = box->width - box->precision - 2;	// так как надо писать 0х
	else
		space = box->width - len - 2;				
	if (box->minus == 0)							
		ft_put_spaces_or_zero(space, box);			
	ft_putchar('0', box);							
	ft_putchar('x', box);							
	ft_put_zeros(p_zero, box);						
	if (len != 0)									
		ft_hex(p, 0, box);							
	if (box->minus == 1)							
		ft_put_spaces_or_zero(space, box);			
}
