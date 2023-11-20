/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlibert <vlibert@students.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:34:55 by vlibert           #+#    #+#             */
/*   Updated: 2023/11/20 21:25:19 by vlibert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
void	create_list(t_list **node, int fd);
void	cp_buf_lst_last(t_list **node, char *buf);
char	*get_last_line(t_list *node);
t_list	*free_list(t_list *node);
int		no_eol(t_list *node);
t_list	*ft_lstlast(t_list *lst);
int		get_len_line(t_list *list);
t_list	*free_old_node(t_list *node, t_list *clean_node);
void	ft_lstclear(t_list *lst);

# endif