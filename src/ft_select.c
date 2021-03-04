/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 13:59:22 by helvi             #+#    #+#             */
/*   Updated: 2021/03/04 16:59:00 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

struct termios		*g_termios;
struct termios		*g_original_termios;

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
** CS8 bit mask with multiple bits, sets character size to 8 bit per byte.\
** raw.c_cc[VMIN] = 0;
** raw.c_cc[VTIME] = 1
** these two can be used to set a timeout for read() so that it will not wait
** for input indefinately.
*/

int		enable_rawmode()
{
	struct termios	raw;

	if (NULL == (g_original_termios = (struct termios*)malloc(sizeof(
		struct termios))))
		die("malloc");
	if (tcgetattr(STDIN_FILENO, g_original_termios) == -1 ||
		tcgetattr(STDIN_FILENO, &raw) == -1)
		die("tcgetattr");
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
	raw.c_iflag &= ~(BRKINT | INPCK | ISTRIP | IXON | ICRNL);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		die("tcsetattr");
	g_termios = &raw;
	return (1);
}

int		disable_rawmode()
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, g_original_termios) == -1)
		die("tcsetattr");
	return (1);
}

int	read_esc(int c)
{
	struct termios	*temp;
	int				c2[3];
	int				i;

	bzero(c2, 3);
	i = 0;
	temp = (struct termios*)malloc(sizeof(struct termios));
	temp = ft_memcpy(temp, g_termios, sizeof(struct termios));
	temp->c_cc[VTIME] = 0;
	temp->c_cc[VMIN] = 0;
	tcsetattr(STDERR_FILENO, TCSAFLUSH, temp);
	read(0, c2, 3);
	while (i < 3 && c2[i] != 0)
	{
		c = c * 10 * ft_define_length(c2[i]) + c2[i];
		i++;
	}
	tcsetattr(STDERR_FILENO, TCSAFLUSH, g_termios);
	ft_free(temp);
	return (c);
}

int	process_keypress()
{
	int	returnable;
	int			c;

	returnable = 0;
	c = 0;
	read(0, &c, 1);
	if (c == 27)
		returnable = read_esc(c);
	else
		returnable = c;
	return (returnable);
}

int			read_char()
{
	int		c;

	c = process_keypress();
	if (c == 27)
	{
		disable_rawmode();
		ft_exit(0);
	}
	ft_printf("%i ", c);
	return (0);
}

int		main(void)
{
	t_select	*info;
	int			c;
	int			i;
	if (NULL == (info = (t_select*)malloc(sizeof(t_select))))
		die("malloc");
	ft_bzero(info, sizeof(t_select));
	ft_atexit(&disable_rawmode);
	enable_rawmode();
	i = 0;
	while (i != 113)
	{
		read(STDIN_FILENO, &c, 1);
		i = (int)c;
		ft_printf("%i ", i);
	}
	ft_exit(0);
	return (0);	
}