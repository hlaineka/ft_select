/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rawmode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:27:50 by helvi             #+#    #+#             */
/*   Updated: 2021/03/03 22:36:14 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

extern t_terminal *g_info;

void	start_termcaps(t_terminal *info, char **envp)
{
	char		*term_type;
	int			success;

	if (NULL == (term_type = ft_getenv(envp, "TERM")))
	{
		disable_rawmode(info);
		die("Terminal type not specified in $TERM");
	}
	success = tgetent (info->term_buffer, term_type);
  	if (success < 0)
	{
		disable_rawmode(info);
		die("Could not access the termcap data base.");
	}
  	if (success == 0)
	{
		disable_rawmode(info);
		die("Terminal type $TERM not defined");
	}
	info->cm_string = tgetstr("cm", NULL);
	info->cl_string = tgetstr("cl", NULL);
	info->cd_string = tgetstr("cd", NULL);
	info->ti_string = tgetstr("ti", NULL);
	info->te_string = tgetstr("te", NULL);
	info->sc_string = tgetstr("sc", NULL);
	info->rc_string = tgetstr("rc", NULL);
	info->us_string = tgetstr("us", NULL);
	info->me_string = tgetstr("me", NULL);
	info->mr_string = tgetstr("mr", NULL);
}

void		check_tty(t_terminal *info)
{
	if (!isatty(1))
		info->fd_out = open(ttyname(ttyslot()), O_WRONLY);
	else
		info->fd_out = 1;
	if (!isatty(0))
	{
		info->fd_in = open(ttyname(ttyslot()), O_RDONLY);
	}
	else
		info->fd_in = 0;
}

/*
** ECHO disables automatic printing of a character
** ICANON starts canonical mode that allows to read one char at a time
** ISIG surpresses ctrl-C and ctrl-Z, those need to be handled separately now
** IXON surpresses ctrl-S and ctrl-Q, those need to be handled separately now
** IEXTEN surpresses ctrl-V, it needs to be handled separately now
** ICRNL surpresses ctrl-M, that reads as a 10 or newline, making ctrl-J read
** as 13
** OPOST turns off output prosessing. Now we need to replace every '\n'
** with "\r\n"
** BRKINT turned on, causing SIGINT signal to be sent to program
** INPCK enables parity checking, does not really apply to modern terminals?
** ISTRIP causes the 8th bit of each input byte to be stripped
** CS8 bit mask with multiple bits, sets character size to 8 bit per byte.
** raw.c_cc[VMIN] = 0;
** raw.c_cc[VTIME] = 1
** these two can be used to set a timeout for read() so that it will not wait
** for input indefinately.
*/

int		enable_rawmode(t_terminal *info, char **envp)
{
	check_tty(info);
	if (NULL == (info->original_termios = (struct termios*)malloc(sizeof(
		struct termios))))
		die("malloc");
	if (NULL == (info->termios = (struct termios*)malloc(sizeof(
		struct termios))))
		die("malloc");
	if (tcgetattr(STDIN_FILENO, info->original_termios) == -1 ||
		tcgetattr(STDIN_FILENO, info->termios) == -1)
		die("tcgetattr");
	info->termios->c_lflag &= ~(ECHO | ICANON | IEXTEN);
	info->termios->c_iflag &= ~(BRKINT | INPCK | ISTRIP | IXON | ICRNL);
	info->termios->c_oflag &= ~(OPOST);
	info->termios->c_cflag |= (CS8);
	if (tcsetattr(info->fd_out, TCSAFLUSH, info->termios) == -1)
	{
		disable_rawmode(info);
		die("tcsetattr");
	}
	start_termcaps(info, envp);
	tputs(info->ti_string, info->screenrows, &ft_putc);
	tputs(tgoto(info->cm_string, 0, 0), info->screenrows, &ft_putc);
	return (1);
}

int		disable_rawmode(t_terminal *info)
{
	tputs(info->te_string, info->screenrows, &ft_putc);
	if (tcsetattr(info->fd_out, TCSAFLUSH, info->original_termios) == -1)
		die("tcsetattr");
	return (1);
}

/*
** Checks and saves to info structure the size of the window.
*/

void		check_window_size(t_terminal *info)
{
	struct winsize	window_size;

	ioctl(info->fd_out, TIOCGWINSZ, &window_size);
	info->screenrows = window_size.ws_row;
	info->screencols = window_size.ws_col;
}


/*
** Function to clear the screen before options are printed. The cursor
** location was saved when the program started, and now we use it as the
** starting location.
*/

void	ft_clear_screen(t_terminal *info)
{
	tputs(info->cl_string, info->screenrows, &ft_putc);
}