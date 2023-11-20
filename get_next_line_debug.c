/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlibert <vlibert@students.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:13:29 by vlibert           #+#    #+#             */
/*   Updated: 2023/11/20 22:28:06 by vlibert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10

void	ft_lstclear(t_list **lst)
{
	t_list	*following;
	t_list	*actual;

	if (!*lst)
		return ;
	actual = *lst;
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
	ft_lstclear(&node);
	if (clean_node->content[0])
		return (clean_node);
	ft_lstclear(&clean_node);
	return(NULL);
}

t_list	*free_list(t_list *node)
{
	t_list	*last;
	t_list	*clean_node;
	char	*next_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	last = ft_lstlast(node);
	while (last->content[i] && last->content[i] != '\n')
		i++;
	clean_node = malloc(sizeof(t_list));
	next_line = malloc(sizeof(char) * (BUFFER_SIZE + 1 - i));
	if (!next_line || !clean_node)
		return (NULL);
	while (last->content[i] && last->content[++i])
		next_line[j++] = last->content[i];
	next_line[j] = '\0';
	clean_node->content = next_line;
	clean_node->next = NULL;
	return (free_old_node(node, clean_node));
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

char *get_last_line(t_list *node)
{
	char	*line;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = get_len_line(node);
	line = malloc(sizeof(char) * (len + 1));
	if (line == NULL)
		return (NULL);
	while(j < len && node->content[i])
	{
		line[j++] = node->content[i++];
		if(!node->content[i] && node->next)
		{
			node = node->next;
			i = 0;
		}
	}
	line[j] = '\0';
	return (line);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	if (!lst->next)
		return (lst);
	return (ft_lstlast(lst->next));
}

void cp_buf_lst_last(t_list **node, char *buf)
{
	t_list	*new;
	t_list	*last;

	last = ft_lstlast(*node);
	new = malloc(sizeof(t_list));
	new->content = buf;
	if (last == NULL)
		*node = new;
	else
		last->next = new; 
	new->next = NULL;
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

void create_list(t_list **node, int fd)
{
	char *buf;
	int count;
	
	while(!node || !*node || no_eol(*node))
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return ;
		count = read(fd, buf, BUFFER_SIZE);
		if (count <= 0)
		{
			if (node && count < 0)
			{
				ft_lstclear(node);
			}
			free(buf);
			return ;
		}
		buf[count] = '\0';
		cp_buf_lst_last(node, buf);
	}
}

char	*get_next_line(int fd)
{
	static struct s_list	*node;
	char					*next_line;

	//security + read()
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
	{
		if (node)
			free_list(node);
		return (NULL);
	}
	
	//Create the node
	create_list(&node, fd);
	if (!node)
		return (NULL);
	//take last line in node
	next_line = get_last_line(node);
	
	//clean list
	node = free_list(node);
	return (next_line);
}

int main()
{
	int fd = open("./monfichier.txt", O_RDONLY | O_CREAT);
 	char *string;
	int i = 1;
	while (i <= 3)
	{
		string = get_next_line(fd);
		printf("ligne %i: \"%s\"\n", i, string);
		i++;
	}
	return (0);
}

#endif