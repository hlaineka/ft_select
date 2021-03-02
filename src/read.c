/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:20:01 by helvi             #+#    #+#             */
/*   Updated: 2021/03/02 09:23:24 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			process_keypress(t_terminal *info)
{
	
}

int			read_char(t_terminal *info)
{
	char	c;
	int		returnable;

	read(STDIN_FILENO, &c, 1);
	returnable = process_keypress(info);
	return (returnable);
}