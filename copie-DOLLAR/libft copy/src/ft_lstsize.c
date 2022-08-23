/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tverdood <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:02:20 by tverdood          #+#    #+#             */
/*   Updated: 2022/01/11 15:03:18 by tverdood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*list;
	int		count;

	count = 0;
	list = lst;
	if (list)
	{
		while (list)
		{
			count++;
			list = list->next;
		}
	}
	return (count);
}
