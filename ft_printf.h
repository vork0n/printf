/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvirgil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 20:18:34 by wpowder           #+#    #+#             */
/*   Updated: 2020/08/03 16:04:32 by cvirgil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef	struct	s_parser
{
	int			width;
	int			minus;
	int			precision;
	int			dot;
	int			w_asterisk;
	int			p_asterisk;
	int			zero;
	int			count;
}				t_parser;

int				ft_printf(const	char *line, ...);
void			ft_processor(va_list argptr, const char *line, t_parser *box);
void			ft_init_parser(t_parser *box);

int				ft_get_x_len(unsigned long dec);
int				ft_get_diu_len(unsigned int dec);
void			ft_put_spaces_or_zero(int i, t_parser *box);
void			ft_precision(char *str, t_parser *box);

void			ft_put_x(unsigned int dec, int i, t_parser *box);
void			ft_hex(unsigned long digit, int i, t_parser *box);
void			ft_put_u(unsigned int dec, t_parser *box);
void			ft_put_p(unsigned long p, t_parser *box);
void			ft_put_di(int n, t_parser *box);
void			ft_put_c(char c, t_parser *box);
void			ft_print_u(unsigned int dec, t_parser *box);
void			ft_put_zeros(int i, t_parser *box);

int				ft_atoi(const char *nptr);
void			ft_putstr(char *str, t_parser *box);
char			*ft_strchr(const char *s, int c);
void			ft_print_str(char *str, t_parser *box);
void			ft_putchar(char c, t_parser *box);
size_t			ft_strlen(const char *s);

#endif
