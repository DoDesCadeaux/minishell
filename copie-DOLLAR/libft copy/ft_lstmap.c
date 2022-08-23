/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 13:12:02 by pamartin          #+#    #+#             */
/*   Updated: 2021/12/31 14:43:47 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*f_lst;
	t_list	*each_lst;

	if (!lst || !f)
		return (NULL);
	f_lst = ft_lstnew((*f)(lst -> content));
	each_lst = f_lst;
	lst = lst -> next;
	while (lst)
	{
		each_lst -> next = ft_lstnew((*f)(lst -> content));
		if (!each_lst -> next)
		{
			ft_lstclear(&f_lst, del);
			return (NULL);
		}
		each_lst = each_lst -> next;
		lst = lst -> next;
	}
	return (f_lst);
}
