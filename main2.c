/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvirgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 21:56:08 by sadolph           #+#    #+#             */
/*   Updated: 2020/08/03 19:47:37 by cvirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int main()
{
	int *res;
	//int re[2];
	//char *kek;
	int r;
	int r_p = 143;
	
	res = &r_p;
	r = ft_printf("[%16p]", res);
	printf("\n%d\n", r);
	r = printf("[%16p]", res);
	printf("\n%d\n", r);
	r = ft_printf("%-16p", res);
	



	//free(res);


	return 0;
}
