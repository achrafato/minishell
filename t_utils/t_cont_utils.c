/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cont_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:25:31 by iassil            #+#    #+#             */
/*   Updated: 2024/03/16 22:48:06 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_t_cont_len(t_cont *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

static t_cont	*ft_last_node(t_cont *top)
{
	while (top->next != NULL)
		top = top->next;
	return (top);
}

int	ft_push_container(t_tmp_cont *tmp, t_cont **head)
{
	t_cont	*newnode;
	t_cont	*last;

	newnode = ft_new_node_for_cont(tmp);
	if (!newnode)
		return (0);
	if (!head || !(*head))
		*head = newnode;
	else
	{
		last = ft_last_node(*head);
		last->next = newnode;
	}
	return (1);
}

void	ft_free_containers(t_cont **head)
{
	t_cont	*current;
	int		i;

	while (*head)
	{
		current = *head;
		*head = (*head)->next;
		i = 0;
		free(current->cmd);
		while (current->arg[i] != NULL)
			(1) && (free(current->arg[i]), i++);
		free(current->arg);
		i = 0;
		while (current->infile[i] != NULL)
			(1) && (free(current->infile[i]), i++);
		free(current->infile);
		i = 0;
		while (current->outfile[i] != NULL)
			(1) && (free(current->outfile[i]), i++);
		free(current->outfile);
		free(current->outfile_type);
		free(current);
		current = NULL;
	}
}
