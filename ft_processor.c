/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_processor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvirgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:14:55 by wpowder           #+#    #+#             */
/*   Updated: 2020/08/03 20:41:30 by cvirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_check_box(va_list argptr, t_parser *box)      		//обрабатывает взаимоисключающие фрали (приоритет флагов)
{
	if (box->w_asterisk == 1)							//если стоит  * вместо шириныб необходимо подтянуть ширину из списка аргументов
	{
		box->width = va_arg(argptr, int);					//записываем в ширину va_arg. он забирает аргумент после запятой
		if (box->width < 0)								//если   va_arg подано отрицательным ширина? то ширина считает положительный, а знак "-" перезжает в ширину
		{
			box->width *= -1;							//превращение значение отрицательного в положительного
			box->minus = 1;								//в box->minus записываем флаг "-" (по стандарту)
		}
	}
	if (box->dot == 1 && box->precision == -1)			//если стоит точка но не задана точность
		box->precision = 0;								//значит задана нулевая точность
	if (box->p_asterisk == 1)							//запись в точность
	{
		box->precision = va_arg(argptr, int);				//подтягивает va_arg в значение точности 
		if (box->precision < 0)							//если задана отрицательная точноть	
			box->precision = -1;						//точность не задана вовсе (стандарт) если она отрицательная
	}
	if (box->precision != -1)							//если задана точность 
		box->zero = 0;									//флаг ноль игнорируется (нет выравнивания нулями)
}

static void	ft_types(char c, va_list argptr, t_parser *box)		//вывод на печать спецификатора
{
	char		*input;

	if (c == '%')										//если встретился второй   %		
		ft_put_c('%', box);								////везде посылаем бокс, чтобы прибавить каунт
	else if (c == 's')									//если встретилась строка 						
	{
		input = va_arg(argptr, char *);				//подтягивает строку из va_arg
		if (input == NULL)							//если строка  NULL 	
			ft_putstr("(null)", box);					//вывести "(null)" (стандарт с учетом точности)  - строка подвергается всем преобразованиям
		else
			ft_putstr(input, box);					//вывод самой строки
	}
	else if (c == 'c')										//печатает одиочный символ
		ft_put_c(va_arg(argptr, int), box);					
	else if (c == 'u')										//печает  unsigned int
		ft_print_u(va_arg(argptr, unsigned int), box);		
	else if (c == 'x') 										//печатает маленькие х 16ричные, передаем 0
		ft_put_x(va_arg(argptr, unsigned int), 0, box);
	else if (c == 'X')										//печатает большие Х 16ричные, передаем 1
		ft_put_x(va_arg(argptr, unsigned int), 1, box);			
	else if (c == 'p')										//печатает указатель
		ft_put_p(va_arg(argptr, unsigned long), box);					//САША ОБЪЯСНИТ ПОЗЖЕ А СЕЙЧАС ДВИГАЕМСЯ ДАЛЬШЕ
	else if (c == 'd' || c == 'i')
		ft_put_di(va_arg(argptr, int), box);					//печатает десятичное число
}



static int	ft_process_wp(int i, const char *line, t_parser *box)  // подтягиваем ширину и точность с помощью  атой
{
	if (box->dot == 0) //если не встретили точку
	{
		box->width = ft_atoi(line + i);				//передаем в ширину (atoi превращает строки в число) запись числа в width "354"  box->width=354
		i += ft_get_diu_len(box->width) - 1;					//сдвигаем i на кол-во цифр возвращенных из  atoi   (3-1)   -1  костыль 
	}
	else
	{
		box->precision = ft_atoi(line + i);			//записываем в точность 
		i += ft_get_diu_len(box->precision) - 1;				//сдвигаем i на кол-во цифр возвращенных из  atoi   (3-1)   -1  костыль, чтобы не убежать на следующий индекс
	}
	return (i);
}

static int	ft_flags(int i, const char *line, char *types, t_parser *box)		//обрабатывает флаги до спецификатора
{
	while (!ft_strchr(types, line[i]) && line[i])         //пока не дойдем до спецификатора либо конца строки
	{
		if (line[i] == '-')						//все что найдено до конца строки распределяется по списку коробки
			box->minus = 1;
		else if (line[i] == '.')					
			box->dot = 1;
		else if (line[i] == '*')
		{
			if (box->dot == 1)					 //* стоит после .точки (значит она задает точность)
				box->p_asterisk = 1;
			else
				box->w_asterisk = 1;			//* стоит  перед .точкой (значит она задает ширину)
		}
		else if (line[i] == '0')			//выравнивание
		{
			if (box->dot == 0)					//если до точки	или ее нет			
				box->zero = 1;					//то это флаг ноль, который заполняет нулями
		}
		else                                   //встречаем цифры
			i = ft_process_wp(i, line, box);			//подтягиваем ширину и точность с помощью  атой
		i++;
	}
	return (i);												//возвращает позицию начала спецификатора
}

void		ft_processor(va_list argptr, const char *line, t_parser *box)
{
	int		i;
	char	*types;

	types = "%scuxXpdi"; 									//список спецификаторов константное выражение
	i = 0;
	while (line[i])								//поиск в строке до конца строки 	
	{
		if (line[i] == '%')						//если найден процент? заходим в цикл			
		{
			i++;										//перепрыгиваем через процент
			ft_init_parser(box);							//инициализируем коробку
			i = ft_flags(i, line, types, box);             //обрабатывает флаги до спецификатора
			ft_check_box(argptr, box);					//обрабатывает взаимоисключающие флаги (приоритет флагов)
			ft_types(line[i], argptr, box);				//вывод на печать спецификатора
			if (!line[i])								//если ВДРУГ вывалились из строки, спецификаторов больше чем надо
				i--;								 	// то откатываем на один символ назад, и все окей.
		}
		else
			ft_putchar(line[i], box);			//пока не найдет  % выводим на печать 
		i++;		
	}
}