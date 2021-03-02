/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:20:01 by helvi             #+#    #+#             */
/*   Updated: 2021/03/02 21:24:32 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			read_esc(t_terminal *info, int c)
{
	struct termios	*temp;
	int				c2;
	int				c3;
	int				returnable;

	c2 = 0;
	c3 = 0;
	temp = (struct termios*)malloc(sizeof(struct termios));
	ft_memcpy(temp, info->termios, sizeof(struct termios));
	temp->c_cc[VTIME] = 0;
	temp->c_cc[VMIN] = 0;
	tcsetattr(info->fd_out, TCSANOW, temp);
	read(0, &c2, 1);
	read(0, &c3, 1);
	if (!c2 || !c3)
		return c;
	returnable = c * 10000 + c2 * 100 + c3;
	tcsetattr(info->fd_out, TCSANOW, info->termios);
	ft_free(temp);
	return (returnable);
}

int			process_keypress(t_terminal *info)
{
	int	returnable;
	int	c;

	returnable = 0;
	c = 0;
	read(0, &c, 1);
	if (c == 27)
		returnable = read_esc(info, c);
	else
		returnable = c;
	return (returnable);
}

int			handle_left(t_option *first)
{
	t_option *temp;

	temp = first;
	while (temp)
	{
		if (temp->cursor)
		{
			temp->cursor = FALSE;
			temp->prev->cursor = TRUE;
			return (1);
		}
		temp = temp->next;
		if (temp == first)
			return (0);
	}
	return (0);
}

int			handle_right(t_option *first)
{
	t_option *temp;

	temp = first;
	while (temp)
	{
		if (temp->cursor)
		{
			temp->cursor = FALSE;
			temp->next->cursor = TRUE;
			return (1);
		}
		temp = temp->next;
		if (temp == first)
			return (0);
	}
	return (0);
}

int			handle_space(t_option *first)
{
	t_option *temp;

	temp = first;
	while (temp)
	{
		if (temp->cursor)
		{
			temp->selected = !temp->selected;
			temp->cursor = FALSE;
			temp->next->cursor = TRUE;
			return (1);
		}
		temp = temp->next;
		if (temp == first)
			return (0);
	}
	return (0);
}

int			handle_return(t_terminal *info, t_option *first)
{
	t_option	*temp;

	ft_clear_screen(info);
	disable_rawmode(info);
	temp = first;
	while (temp)
	{
		if (temp->selected)
		{
			ft_putstr_fd(temp->name, STDOUT_FILENO);
			ft_putstr_fd(" ", STDOUT_FILENO);
		}
		temp = temp->next;
		if (temp == first)
		{
			ft_putstr_fd("\r\n", STDOUT_FILENO);
			ft_exit(0);
		}
	}
	return (0);
}

void		free_option(t_option *to_free)
{
	ft_free(to_free->name);
	ft_free(to_free);
}

int			handle_delete(t_terminal *info, t_option **first)
{
	t_option *temp;

	temp = *first;
	while (temp)
	{
		if (temp->cursor)
		{
			if (temp->next == temp)
			{
				disable_rawmode(info);
				ft_exit(0);
			}
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			temp->next->cursor = TRUE;
			if (temp == *first)
				*first = temp->next;
			free_option(temp);
			return (1);
		}
		temp = temp->next;
		if (temp == *first)
			return (0);
	}
	return (0);
}

int			handle_char(t_terminal *info, t_option **first)
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
	if (c == 127)
		return (handle_delete(info, first));
	return (0);
}