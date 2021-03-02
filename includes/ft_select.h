/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 13:57:04 by helvi             #+#    #+#             */
/*   Updated: 2021/03/02 09:22:31 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <termios.h>
# include <sys/ioctl.h>
# include <stdbool.h>
# include <curses.h>
# include <term.h>
# include "libft.h"

typedef	struct 		s_terminal
{
	struct termios	*original_termios;
	char			term_buffer[2048];
	char			*cm_string;
	char			*cl_string;
	char			*ti_string;
	char			*te_string;
	char			*sc_string;
	char			*us_string;
	char			*me_string;
	char			*mr_string;
	int				screenrows;
	int				screencols;
	int				cursorrow;
	int				cursorcol;
}					t_terminal;

typedef struct 		s_option
{
	char			*name;
	bool			selected;
	bool			cursor;
	int				cursorcol;
	int				cursorrow;
	struct s_option	*next;
	struct s_option	*prev;

}					t_option;

/*
** rawmode.c
*/

int					enable_rawmode(t_terminal *info, char **envp);
int					disable_rawmode(t_terminal *info);
void				check_window_size(t_terminal *info);
void				ft_clear_screen(t_terminal *info);

/*
** print.c
*/

void				print_selections(t_terminal *info, t_option *first);

/*
** cursor.c
*/

void				save_cursor_position(t_option *node, t_terminal *info);
void				move_cursor(t_option *first, t_terminal *info);
void				print_mv_cursor(char *printable, t_terminal *info);

/*
** print.c
*/

int					read_char(t_terminal *info);

/*
** helpers.c
*/

int					ft_putc(int c);

#endif