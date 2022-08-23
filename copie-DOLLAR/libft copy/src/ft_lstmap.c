/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tverdood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:04:51 by tverdood          #+#    #+#             */
/*   Updated: 2022/01/14 12:42:41 by tverdood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr;
	t_list	*temp;

	ptr = NULL;
	if (f)
	{
		while (lst)
		{
			temp = ft_lstnew((*f)(lst->content));
			if (!temp)
			{
				ft_lstclear(&ptr, del);
				return (NULL);
			}
			ft_lstadd_back(&ptr, temp);
			lst = lst->next;
		}
	}
	return (ptr);
}
