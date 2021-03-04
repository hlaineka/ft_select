/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 19:11:03 by helvi             #+#    #+#             */
/*   Updated: 2021/03/03 19:19:06 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

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
