/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 12:14:51 by pamartin          #+#    #+#             */
/*   Updated: 2021/12/31 12:14:52 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tempo;

	if (!lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		tempo = ft_lstlast(*lst);
		tempo -> next = new;
	}
}
