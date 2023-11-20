/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlibert <vlibert@students.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:27:29 by vlibert           #+#    #+#             */
/*   Updated: 2023/11/20 21:58:08 by vlibert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*	1. Créer une liste avec tous les chars jusqu'a \n
	2. Mettre toute les char* de la liste dans un char* faisant la bonne taille
	3. Lire
	4. faire un nouveau noeud et effacer l'ancien */

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
/*
	Free content
	copy string into buf
	Set last list as a new node
*/

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

/*
	Calculate len of line
	malloc len + 1
	copy in the line in a string
	read it
*/

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

/*
	Create the node :
	add string of the size of Buffer size to each list inside node
	stop when \n is found
	Stop if eol
*/

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
				ft_lstclear(*node);
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
