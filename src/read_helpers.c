/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:20:58 by helvi             #+#    #+#             */
/*   Updated: 2021/03/04 19:45:21 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

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
			ft_putstr_fd("\n", STDOUT_FILENO);
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
