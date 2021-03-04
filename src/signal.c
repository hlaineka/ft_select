/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 10:00:31 by helvi             #+#    #+#             */
/*   Updated: 2021/03/03 22:28:06 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

extern t_terminal *g_info;

void	signwinch_handler(int signo)
{
	if (signo == SIGWINCH)
	{
		reset_screen(g_info);
		print_selections(g_info, g_info->first);
	}
}

void	sigint_handler(int signo)
{
	if (signo ==  SIGINT)
	{
		disable_rawmode(g_info);
		ft_exit(0);
	}
}

void	sigcont_handler(int signo)
{
	if (signo == SIGCONT)
	{
		check_tty(g_info);
		if (tcsetattr(g_info->fd_out, TCSANOW, g_info->termios) == -1)
		{
			disable_rawmode(g_info);
			die("tcsetattr");
		}
		tputs(g_info->ti_string, g_info->screenrows, &ft_putc);
		tputs(tgoto(g_info->cm_string, 0, 0), g_info->screenrows, &ft_putc);
		reset_screen(g_info);
		print_selections(g_info, g_info->first);
	}
}

void	sigtstp_handler(int signo)
{
	if (signo == SIGTSTP)
	{
		if (tcsetattr(g_info->fd_out, TCSAFLUSH, g_info->original_termios) == -1)
			die("tcsetattr");
		signal(SIGTSTP, SIG_DFL);
		ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
		tputs(g_info->te_string, g_info->screenrows, &ft_putc);
	}
}

void	start_signal(void)
{
	signal(SIGWINCH, signwinch_handler);
	signal(SIGINT, sigint_handler);
	signal(SIGTSTP, sigtstp_handler);
	signal(SIGCONT, sigcont_handler);
}