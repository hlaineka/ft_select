/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:20:01 by helvi             #+#    #+#             */
/*   Updated: 2021/03/04 17:05:00 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

extern t_terminal *g_info;

int			read_esc(t_terminal *info, int c)
{
	struct termios	*temp;
	int				i;
	char			c2[3];

	ft_bzero(c2, 3);
	temp = (struct termios*)malloc(sizeof(struct termios));
	ft_memcpy(temp, info->termios, sizeof(struct termios));
	temp->c_cc[VTIME] = 1;
	temp->c_cc[VMIN] = 0;
	tcsetattr(info->fd_out, TCSANOW, temp);
	read(0, c2, 3);
	while (i < 3 && c2[i] != 0)
	{
		c = c * 10 * ft_define_length(c2[i]) + (c2[i] - '0');
		i++;
	}
	tcsetattr(info->fd_out, TCSANOW, info->termios);
	ft_free(temp);
	return (c);
}

int	process_keypress(t_terminal *info)
{
	long int	returnable;
	int			c;

	returnable = 0;
	c = 0;
	read(info->fd_in, &c, 1);
	if (c == 27)
		returnable = read_esc(info, c);
	else
		returnable = c;
	return (returnable);
}

int			handle_delete(t_terminal *info, t_option **first)
{
	t_option *temp;

	temp = *first;
	while (!temp->cursor)
	{
		temp = temp->next;
		if (temp == *first)
			return (0);
	}
	if (temp->next == temp)
	{
		disable_rawmode(info);
		ft_exit(0);
	}
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	temp->next->cursor = TRUE;
	if (temp == *first)
	{
		*first = temp->next;
		g_info->first = temp->next;
	}
	free_option(temp);
	return (1);
}

int			read_char(t_terminal *info, t_option **first)
{
	int		c;

	c = process_keypress(info);
	if (c == 27)
	{
		disable_rawmode(info);
		ft_exit(0);
	}
	if (c == ARROW_LEFT)
		return (handle_left(*first));
	if (c == ARROW_RIGHT)
		return (handle_right(*first));
	if (c == 13)
		return (handle_return(info, *first));
	if (c == 32)
		return (handle_space(*first));
	if (c == 127) //add delete also! It is 4 characters
		return (handle_delete(info, first));
	ft_printf("%i", c);
	return (0);
}
