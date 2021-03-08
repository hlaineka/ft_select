/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:44:13 by helvi             #+#    #+#             */
/*   Updated: 2021/03/05 09:14:35 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LISTS_H
# define FT_LISTS_H

# include "libft.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;

}					t_list;

/*
** libft list functions
*/

t_list				*ft_lstnew(const void *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new_list);
void				ft_lstiter(t_list *lst, void (*f)(t_list*elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstsrc(const void *content, t_list *beginning);
void				ft_lstnewtoend(const void *content, size_t content_size,
					t_list **beginning);
void				ft_lstaddafter(t_list *end, t_list *newelem);

/*
** own list functions
*/

int					ft_lst_length(t_list *first);
void				ft_lst_merge_sort(t_list **first, int (*f)(t_list *elem_a,
					t_list *elem_b));
t_list				*ft_lst_reverse(t_list **first);
t_list				*ft_lst_sorted_merge(t_list *a, t_list *b,
					int (*f)(t_list *elem_a, t_list *elem_b));
void				ft_lst_split(t_list *first, t_list **a, t_list **b);
void				ft_lstaddtoend(const void *content, size_t content_size,
					t_list **beginning);
void				ft_lstdellast(t_list **first);
t_list				*ft_lstend(t_list *beginning);

#endif
