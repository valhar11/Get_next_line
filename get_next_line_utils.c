/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlibert <vlibert@students.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:38:38 by vlibert           #+#    #+#             */
/*   Updated: 2023/11/20 20:37:59 by vlibert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_lstclear(t_list *lst)
{
	t_list	*following;
	t_list	*actual;

	if (!lst)
		return ;
	actual = lst;
	if (actual)
	{
		while (actual)
		{
			following = actual->next;
			free(actual->content);
			actual->content = NULL;
			free(actual);
			actual = NULL;
			actual = following;
		}
	}
}

t_list	*free_old_node(t_list *node, t_list *clean_node)
{
	ft_lstclear(node);
	if (clean_node->content[0])
		return (clean_node);
	ft_lstclear(clean_node);
	return(NULL);
}

int get_len_line(t_list *list)
{
	int len;
	int i;
	
	len = 0;
	while(list)
	{
		i = 0;
		while(list->content && list->content[i])
		{
			if (list->content[i] == '\n')
			{
				i++;
				return (len + i);
			}
			i++;
		}
		len = i + len;
		list = list->next;
	}
	return (len);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	if (!lst->next)
		return (lst);
	return (ft_lstlast(lst->next));
}

int no_eol(t_list *node)
{
	int	i;
	node = ft_lstlast(node);
	if(node && node->content)
	{
		i = 0;
		while(node->content[i])
		{
			if (node->content[i] == '\n')
				return (0);
			i++;
		}
	}
	return (1);
}

/* t_list	*ft_lstnew(void *content)
{
	t_list	*new_lst;

	new_lst = (t_list *)malloc(sizeof(t_list));
	if (!new_lst)
		return (NULL);
	new_lst->content = content;
	new_lst->next = NULL;
	return (new_lst);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	if (!lst->next)
		return (lst);
	return (ft_lstlast(lst->next));
}

int get_len_line(t_list *list)
{
	int len;
	int i;
	
	len = 0;
	while(list)
	{
		i = 0;
		while(list->content[i])
		{
			if (list->content[i] == '\n')
			{
				i++;
				return (len + i);
			}
			i++;
		}
		len = i + len;
		list = list->next;
	}
	return (len);
} */