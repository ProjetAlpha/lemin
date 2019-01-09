/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_order_link.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/07 15:00:46 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/09 18:30:44 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>

int		get_size(t_links *links, t_data *data, char *r_name, int is_start)
{
	int size;
	t_links *begin;

	begin = links;
	size = 0;
	while (begin && begin->a != NULL && begin->b != NULL)
	{
		if (is_start == 0 && begin->is_in == 0 && begin->is_duplicate == 0)
		{
			if (!ft_strcmp(data->start, begin->a)) 
				size++;
			else if (!ft_strcmp(data->start, begin->b))
				size++;
		}
		else if (begin->is_in == 0 && begin->is_duplicate == 0)
		{
			if (!ft_strcmp(r_name, begin->a)) 
				size++;
			else if (!ft_strcmp(r_name, begin->b))
				size++;
		}
		begin = begin->next;
	}
	return (size);
}

void	ft_alloc_links(t_dlinks **links, int size)
{
	int i;

	i = 0;
	while (i < size)
		links[i++] = malloc(sizeof(t_dlinks));
}

t_dlinks	**ft_sort_link(t_links *links, t_data *data)
{
	t_links *begin;
	t_links	*tmp;
	t_dlinks **dlinks;
	t_dlinks **dbegin;
	int 	is_start;
	int		c_links;
	int 	size;
	int		i;
	char	*r_name;

	begin = links;
	is_start = 0;
	size = get_size(begin, data, begin->a, is_start);
	dlinks = malloc(sizeof(t_dlinks*) * size);
	ft_alloc_links(dlinks, size);
	(*dlinks)->size = size;
	dbegin = dlinks;
	while (begin)
	{
		tmp = begin;
		//printf("size 1 %d\n", size);
		r_name = begin->a;
		i = 0;
		c_links = 0;
		while (tmp && tmp->a != NULL && tmp->b != NULL && r_name != NULL && size != 0)
		{
			if ((!ft_strcmp(tmp->a, begin->a) && !ft_strcmp(tmp->b, begin->b))
					|| (!ft_strcmp(tmp->b, begin->a) && !ft_strcmp(tmp->a, begin->b)))
				c_links++;
			if (c_links > 1)
			{
				tmp->is_duplicate = 1;
				printf("duplicate  : a  %s | b %s \n", tmp->a, tmp->b);
			}
			//printf(" tmp a %s\n", tmp->a);	
			if (is_start == 0 && i < size && size > 0 && tmp->is_in == 0 && tmp->is_duplicate == 0)
			{
				if (!ft_strcmp(data->start, tmp->a))
				{
					dlinks[i]->a = data->start;
					dlinks[i]->b = tmp->b;
					//printf(" ---- link a %s | ---- link b %s\n", dlinks[i]->a, dlinks[i]->b);
					tmp->is_in = 1;
					i++;
				}
				else if (!ft_strcmp(data->start, tmp->b))
				{
					dlinks[i]->a = data->start;
					dlinks[i]->b = tmp->a;
					//printf(" ---- link a %s | ---- link b %s\n", dlinks[i]->a, dlinks[i]->b);
					tmp->is_in = 1;
					i++;
				}
			}
			else if (i < size && size > 0 && tmp->is_in == 0 && tmp->is_duplicate == 0)
			{
				if (!ft_strcmp(r_name, tmp->a)) 
				{
					dlinks[i]->a = tmp->a;
					dlinks[i]->b = tmp->b;
					//printf(" ---- link a %s | ---- link b %s\n", dlinks[i]->a, dlinks[i]->b);
					tmp->is_in = 1;
					i++;
				}
				else if (!ft_strcmp(r_name, tmp->b))
				{
					dlinks[i]->a = tmp->b;
					dlinks[i]->b = tmp->a;
					//printf(" ---- link a %s | ---- link b %s\n", dlinks[i]->a, dlinks[i]->b);
					tmp->is_in = 1;
					i++;
				}
			}
			//printf(" ---- link a %s\n | ---- link b %s\n", dlinks[i]->a, dlinks[i]->b);
			tmp = tmp->next;
		}
		is_start = 1;
		if (begin->next && begin->next->a != NULL)
		{
			size = get_size(begin->next, data, begin->next->a, is_start);
			//printf("size -- %d\n", size);
			if (size != 0)
			{
				(*dlinks)->next = malloc(sizeof(t_dlinks*) * size);
				ft_alloc_links((*dlinks)->next, size);
				dlinks = (*dlinks)->next;
				(*dlinks)->size = size;
			}
		}
		begin = begin->next;
	}
	return (dbegin);
}
