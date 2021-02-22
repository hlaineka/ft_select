/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 11:38:45 by helvi             #+#    #+#             */
/*   Updated: 2021/02/22 12:18:00 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exit.h"

int	(*g_run_at_exit)(void) = NULL;

int					ft_atexit(int (*func_for_exit)(void))
{
	g_run_at_exit = func_for_exit;
	return(1);
}

int					ft_exit(int return_value)
{
	if (g_run_at_exit)
		g_run_at_exit();
	exit(return_value);
	return(1);
}