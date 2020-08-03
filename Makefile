# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cvirgil <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/31 13:25:19 by wpowder           #+#    #+#              #
#    Updated: 2020/08/03 16:33:20 by cvirgil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

HDRS = ft_printf.h

SRCS = ft_libft.c ft_printf.c ft_processor.c ft_utils.c\
		ft_put_dip.c ft_put_csz.c ft_put_ux.c

OBJS = $(SRCS:.c=.o)

CC = gcc -Wall -Wextra -Werror -c

all: $(NAME)

$(NAME): $(OBJS) $(HDRS)
	ar rc $(NAME) $?
	@ranlib $(NAME)
	@echo "Success!"

%.o: %.c $(HDRS)
	$(CC) $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "Object files were deleted ┐(￣ヘ￣)┌"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) was also totally deleted:("

re: fclean all

.PHONY: all clean fclean re