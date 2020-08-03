/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvirgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 14:47:24 by wpowder           #+#    #+#             */
/*   Updated: 2020/08/03 15:56:10 by cvirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_hex(unsigned long digit, int i, t_parser *box)		//рассчет и вывод 16го числа
{
	char *x;											

	if (i)												//признак больших 
		x = "0123456789ABCDEF";							//строка индексов для Х		
	else												
		x = "0123456789abcdef";							//Стркоа индексов для х
	if (digit > 15)										
		ft_hex(digit / 16, i, box);		 			//пока число больше 15 вызываем его само себя и делим на 16
	ft_putchar(x[digit % 16], box);					//выводим на экран 16е число
}

void	ft_put_x(unsigned int hex, int i, t_parser *box) //вывод 16тиричного числа
{
	int len;
	int p_zero;
	int space;

	len = ft_get_x_len(hex);						//получаем длину 16 
	if (hex == 0 && box->precision == 0)			//если точность нулевая и число равно 0 то ничего не выводим
		len = 0;
	p_zero = box->precision - len;					//число нулей
	if (p_zero > 0)
		space = box->width - box->precision;		//число пробелов
	else
		space = box->width - len;					//добиваем пробелы вычитая из ширины длину
	if (box->minus == 0)
		ft_put_spaces_or_zero(space, box);			//выводим пробелы
	ft_put_zeros(p_zero, box);						//выводим нули
	if (len != 0)			
		ft_hex(hex, i, box);						//если есть длина выводим число
	if (box->minus == 1)
		ft_put_spaces_or_zero(space, box);			//выводим пробелы после числа если задан знак минус
}

void	ft_put_u(unsigned int dec, t_parser *box)  //вывод самого числа (АНАЛОГ ИТОА)
{
	int len;
	int base;
	int digit;

	base = 1;										
	len = ft_get_diu_len(dec);	//получить длину числа (количества разрядов)
	while (--len > 0)								
	{
		base *= 10;				//наращиваем базу на которую будем делить									
	}
	while (base > 0)
	{
		digit = dec / base;		//каждая следуящая цифра образуется делением текущего числа на базу
		dec %= base;			//новым числом становится остаток от деления
		base /= 10;				//база уменьшается на каждом шаге
		ft_putchar(digit + '0', box); //вывести цифру в виде символа
	}
}

void	ft_print_u(unsigned int dec, t_parser *box)		//печатает unsigned инт
{
	int len;
	int p_zero;
	int space;

	len = ft_get_diu_len(dec);							//получаем длину (числа разрядов) для печати
	if (dec == 0 && box->precision == 0)				//если число и точность равно нулю то ничего не печатаем (по стандарту)
		len = 0;
	p_zero = box->precision - len;						//сколько нулей надо вывести? (если число выравнивается с нулями по точности и пробелами до ширины)
	if (p_zero > 0)										
		space = box->width - box->precision;			//сколько пробелов если точность больше длины
	else
		space = box->width - len;						//сколько пробелов если точность не больше длины
	if (box->minus == 0)								//если минуса нет 
		ft_put_spaces_or_zero(space, box);				//сначала пробелы
	ft_put_zeros(p_zero, box);							//нули
	if (len != 0)										//если нет длины то ничего не печатаем
		ft_put_u(dec, box);								//выводится само число ансайгнт инт
	if (box->minus == 1)								//если задан минус
		ft_put_spaces_or_zero(space, box);				//то потом пробелы
}
