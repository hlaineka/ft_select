/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 13:59:22 by helvi             #+#    #+#             */
/*   Updated: 2021/03/02 09:22:13 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_option	*create_list(char **argv)
{
	int			i;
	t_option	*temp_prev;
	t_option	*temp_this;
	t_option	*first;

	i = 1;
	temp_prev = NULL;
	temp_this = NULL;
	while (argv[i])
	{
		temp_this = (t_option*)malloc(sizeof(t_option));
		temp_this->name = ft_strdup(argv[i]);
		temp_this->selected = FALSE;
		temp_this->next = NULL;
		temp_this->prev = temp_prev;
		if (i == 1)
			first = temp_this;
		if (temp_prev)
			temp_prev->next = temp_this;
		temp_prev = temp_this;
		i++;
	}
	temp_prev->next = first;
	first->prev = temp_prev;
	return(first);
}

void		selector(t_terminal *info, char **argv)
{
	t_option	*first;
	int			c;

	if (!info)
		return;
	first = create_list(argv);
	first->cursor = TRUE;
	print_selections(info, first);
	while (true)
	{
		c = read_char(info);
		if (c == 27)
		{
			disable_rawmode(info);
			ft_exit(0);
		}
	}
}

int			main(int argc, char **argv, char **envp)
{
	t_terminal	*info;

	if (NULL == (info = (t_terminal*)malloc(sizeof(t_terminal))))
		die("malloc");
	ft_bzero(info, sizeof(t_terminal));
	enable_rawmode(info, envp);
	check_window_size(info);
	if (argc > 1)
		selector(info, argv);
	disable_rawmode(info);
	ft_exit(0);
	return (0);
}
