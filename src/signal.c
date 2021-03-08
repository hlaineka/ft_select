/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 10:00:31 by helvi             #+#    #+#             */
/*   Updated: 2021/03/04 20:38:09 by helvi            ###   ########.fr       */
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

void	sig_handler(int signo)
{
	if (signo)
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
		if (tcsetattr(g_info->fd_out, TCSAFLUSH, g_info->termios) == -1)
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
		if (tcsetattr(g_info->fd_out, TCSAFLUSH, g_info->original_termios)
			== -1)
			die("tcsetattr");
		signal(SIGTSTP, SIG_DFL);
		ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
		tputs(g_info->te_string, g_info->screenrows, &ft_putc);
	}
}

void	start_signal(void)
{
	if ((signal(SIGWINCH, signwinch_handler) == SIG_ERR) ||
		(signal(SIGTSTP, sigtstp_handler) == SIG_ERR) ||
		(signal(SIGCONT, sigcont_handler) == SIG_ERR) ||
		(signal(SIGINT, sig_handler) == SIG_ERR) ||
		(signal(SIGQUIT, sig_handler) == SIG_ERR) ||
		(signal(SIGHUP, sig_handler) == SIG_ERR) ||
		(signal(SIGPIPE, sig_handler) == SIG_ERR) ||
		(signal(SIGALRM, sig_handler) == SIG_ERR) ||
		(signal(SIGXCPU, sig_handler) == SIG_ERR) ||
		(signal(SIGXFSZ, sig_handler) == SIG_ERR) ||
		(signal(SIGVTALRM, sig_handler) == SIG_ERR) ||
		(signal(SIGPROF, sig_handler) == SIG_ERR))
	{
		disable_rawmode(g_info);
		ft_exit(0);
	}
}
