/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 13:59:22 by helvi             #+#    #+#             */
/*   Updated: 2021/02/22 12:18:54 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		enable_rawmode()
{
	struct termios	raw;

	g_original_termios = (struct termios*)malloc(sizeof(struct termios));
	tcgetattr(STDIN_FILENO, g_original_termios);
	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	return (1);
}

int		disable_rawmode()
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, g_original_termios);
	return (1);
}

int		main(void)
{
	t_select	*info;

	info = (t_select*)malloc(sizeof(t_select));
	ft_bzero(info, sizeof(t_select));
	ft_atexit(&disable_rawmode);
	enable_rawmode();
	ft_exit(0);
	return (0);	
}