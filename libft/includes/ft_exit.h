/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 11:19:21 by helvi             #+#    #+#             */
/*   Updated: 2021/02/22 12:17:53 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_EXIT_H
# define FT_EXIT_H

# include "ft_printf.h"
# include "libft.h"

typedef	struct 		s_exit
{
}					t_exit;

int					ft_atexit(int (*func_for_exit)(void));
int					ft_exit(int return_value);

#endif