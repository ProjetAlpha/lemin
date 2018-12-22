/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   build_tree.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/21 18:39:26 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/22 23:57:43 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>

// asscocie tout les links avec le noeud correspondant.
// une fois qu on a plus de link pour ce noeud, cherche les bifurcations.

void	find_links(t_links *links, t_nodes *nodes, char *r_name, int depth)
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
				if (!ft_strcmp(r_name, begin->a) && is_set == 0 && depth == c_nodes)
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
	//printf("seg\n");
	printf("A : %s | B : %s\n", root->link_a, root->link_b);
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
	t_nodes		*n_begin;

	n_begin = begin;
	i = 0;
	is_next = 0;	
	find_links(links, root, r_name, depth);
	/*if (root->link_b == 0)
	  {
	  depth = 0;
	  root->c_childs = 0;
	  printf("room before : %s\n", r_name);
	// find 1 nodes avec des childs.
	// doit retourner
	root = find_next(links, r_name, n_begin);
	printf("room after : %s\n", r_name);

	// root childs = x.
	is_next = 1;
	//c_next++;
	// enlever ce qui sont
	}*/
	printf("NOOODES %d --- DEPTH %d --- ROOM %s\n", root->c_childs, depth, r_name);
	printf(" LINK A : %s  | LINK B : %s \n", root->link_a, root->link_b);
	if (root->childs == NULL)
		root->childs = malloc(sizeof(t_nodes *) * root->c_childs);
	i = 0;	
	while (i < root->c_childs)
	{
		printf("seg\n");
		if (root->childs[i] == NULL)
			root->childs[i] = malloc(sizeof(t_nodes));
		root->childs[i]->r_name = root->link_b;
		// is_next ? root->link_b :root->link_a;
		// find_next ... avec i, jusqu' a contruire la branche.
		//root = root->childs[i];
		//sleep(1);
		//set_nodes(root, links, root->r_name, depth, begin);
		printf("seg\n");
		
		get_next(links, root, root->link_a, i);
		i++;
	}
	i = 0;
	while (i < root->c_childs)
	{
		root = root->childs[i];
		sleep(1);
		printf("sef\n");
		set_nodes(root, links, root->link_b, depth++, begin);
		i++;
	}
	return (NULL);
}
