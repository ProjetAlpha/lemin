/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   build_tree.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/21 18:39:26 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/23 17:58:04 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>

void	find_links(t_links *links, t_nodes *nodes, char *r_name)
{
	t_links		*begin;
	int			is_set;
	int			c_nodes;

	begin = links;
	is_set = 0;
	c_nodes = 0;
	while (begin)
	{
		if (r_name != NULL)
		{
			if (begin->a != 0 || begin->b != 0)
			{
				if (!ft_strcmp(r_name, begin->a) && is_set == 0)
				{
					nodes->link_a = begin->a;
					nodes->link_b = begin->b;
					is_set = 1;
				}
				if (!ft_strcmp(r_name, begin->a))
				{
					nodes->c_childs++;
					c_nodes++;
				}
			}
		}
		begin = begin->next;
	}
}

void	get_next(t_links *links, t_nodes *nodes, char *r_name, int depth)
{
	t_links		*begin;
	int			is_set;
	int			c_nodes;

	c_nodes = 0;
	begin = links;
	is_set = 0;
	while (begin)
	{
		if (r_name != NULL)
		{
			if (begin->a != 0 || begin->b != 0)
			{

				if (!ft_strcmp(r_name, begin->a) && is_set == 0 && depth == c_nodes)
				{
					nodes->link_a = begin->a;
					nodes->link_b = begin->b;
					is_set = 1;
				}
				if (!ft_strcmp(r_name, begin->a))
					c_nodes++;
			}
		}
		begin = begin->next;
	}
}

t_nodes		*search_node(t_nodes *root, char *r_name)
{
	int i;

	i = 0;
	t_nodes *tmp;
	if (root->link_b == NULL)
		return (NULL);
	if (!ft_strcmp(root->link_b, r_name))
		return (root);
	while (i < root->c_childs)
	{
		root = root->childs[i];
		if ((tmp = search_node(root, r_name)))
			return (tmp);
		i++;	
	}
	return (NULL);
}

t_nodes	*find_next(t_links *links, char *r_name, t_nodes *n_begin)
{
	t_links		*begin;
	int			is_set;
	int			c_nodes;

	begin = links;
	is_set = 0;
	c_nodes = 0;
	while (begin)
	{
		if (r_name != NULL)
		{
			if (begin->a != 0 || begin->b != 0)
			{
				if (ft_strcmp(r_name, begin->a) != 0)
				{
					//root->is_set = 1;
					return (search_node(n_begin, begin->a));
				}
			}
		}
		begin = begin->next;
	}
	return (NULL);
}

t_nodes	**set_nodes(t_nodes *root, t_links *links, char *r_name, int depth, t_nodes *begin)
{
	int			i;
	int			is_next;
	char		*tmp;
	t_nodes		*n_begin;

	n_begin = begin;
	i = 0;
	is_next = 0;	
	find_links(links, root, r_name);
	if (root->c_childs == 0)
		return (NULL);
	printf(" LINK A : %s  | LINK B : %s \n", root->link_a, root->link_b);
	//if (root->childs == NULL)
	root->childs = malloc(sizeof(t_nodes *) * root->c_childs);
	i = 0;	
	while (i < root->c_childs)
	{
		root->childs[i] = malloc(sizeof(t_nodes));
		root->childs[i]->r_name = root->link_b;
		get_next(links, root->childs[i], root->link_a, i);
		// OK -- printf("root link a %s | root link b %s\n", root->childs[i]->link_a, root->childs[i]->link_b);
		i++;
	}
	i = 0;
	while (i < root->c_childs)
	{
		tmp = root->childs[i]->link_b;
	   	sleep(1);	
		set_nodes(root->childs[i], links, tmp, depth, begin);
		i++;
	}
	return (NULL);
}
