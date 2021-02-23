/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 13:57:04 by helvi             #+#    #+#             */
/*   Updated: 2021/02/23 15:12:58 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "ft_printf.h"
# include "libft.h"
# include "ft_exit.h"
# include "ft_error.h"
# include <termios.h>
# include <sys/ioctl.h>

/*
** Global variables needed by the ft_exit.
*/

struct termios	*g_original_termios;

typedef	struct 		s_select
{
	
}					t_select;

#endif