/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   build_tree.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/21 18:39:26 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/06 22:46:06 by thbrouss    ###    #+. /#+    ###.fr     */
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
	int			is_a;
	int			is_b;

	is_a = 0;
	is_b = 0;
	begin = links;
	is_set = 0;
	c_nodes = 0;
	while (begin)
	{
		if (r_name != NULL)
		{
			if ((begin->a != 0 || begin->b != 0) && begin->is_set == 0)
			{
				if (!ft_strcmp(r_name, begin->a) && is_set == 0)
				{
					nodes->link_a = begin->a;
					nodes->link_b = begin->b;
					//begin->is_set = 1;
					is_set = 1;
					is_a = 1;
				}
				if (!ft_strcmp(r_name, begin->b) && is_set == 0)
				{
					nodes->link_a = begin->b;
					nodes->link_b = begin->a;
					//begin->is_set = 1;
					is_set = 1;
					is_b = 1;
				}
				if (!ft_strcmp(r_name, begin->a) || !ft_strcmp(r_name, begin->b))
				{
					nodes->c_childs++;
					c_nodes++;
				}
				/*if (!ft_strcmp(r_name, begin->b) && is_b == 1)
				{
					nodes->c_childs++;
					c_nodes++;
				}*/
			}
		}
		begin = begin->next;
	}
}

int		has_node(t_nodes *root, char *link_a, char *link_b)
{
	int i;

	i = 0;
	if (root == NULL || root->link_b == 0 || root->link_a == 0 || link_a == NULL || link_b == NULL)
		return (0);
	//printf("seg1\n");
	if ((!ft_strcmp(root->link_b, link_b) && !ft_strcmp(root->link_a, link_a)) || 
			(!ft_strcmp(root->link_b, link_a) && !ft_strcmp(root->link_a, link_b)))
	{
		printf("cmp_a %s, cmp_b %s\n", root->link_a, root->link_b);
		//printf("seg\n");
		return (1);
	}
	while (i < root->c_childs)
	{
		root = root->childs[i];
		//printf("seg 2\n");
		if (root)
		{
			if (has_node(root, link_a, link_b) == 1)
				return (1);
		}
		//printf("seg3\n");
		i++;	
	}
	return (0);
}



void	get_next(t_links *links, t_nodes *nodes, char *r_name, int depth)
{
	t_links		*begin;
	int			is_set;
	int			c_nodes;
	int 		is_a;
	int			is_b;

	is_a = 0;
	is_b = 0;
	c_nodes = 0;
	begin = links;
	is_set = 0;
	while (begin)
	{
		if (r_name != NULL)
		{
			if ((begin->a != 0 || begin->b != 0) && begin->is_set == 0)
			{

				if (!ft_strcmp(r_name, begin->a) && is_set == 0 && depth == c_nodes && begin->is_set == 0)
				{
					nodes->link_a = begin->a; // si strcmp(r_name, begin->b) === C - A.
					nodes->link_b = begin->b; // ==> nodes->link_a = begin->b, nodes->link_b = begin->a.
					is_set = 1;
					begin->is_set = 1;
					is_a = 1;
				}
				else if (!ft_strcmp(r_name, begin->b) && is_set == 0 && depth - 1 == c_nodes && begin->is_set == 0)
				{
					nodes->link_a = begin->b;
					nodes->link_b = begin->a;
					begin->is_set = 1;
					is_set = 1;
					is_b = 1;
				}
				if (!ft_strcmp(r_name, begin->b) && is_set == 0 && begin->is_set == 0 && depth - 1 == c_nodes)
					printf("foudned link a %s link b %s\n", begin->a, begin->b);
				if (!ft_strcmp(r_name, begin->b) || !ft_strcmp(r_name, begin->a))
					c_nodes++;
				/*if (!ft_strcmp(r_name, begin->a) && is_a == 1)
					c_nodes++;
				if (!ft_strcmp(r_name, begin->b) && is_b == 1)
					c_nodes++;*/
			}
		}
		begin = begin->next;
	}
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
	//printf(" LINK A : %s  | LINK B : %s \n", root->link_a, root->link_b);	
	find_links(links, root, r_name);
	// A - B.
	// B - C.
	// C - D.
	// D - A.
	// C - A => A - C.
	if (root->c_childs == 0)
		return (NULL);
	//printf(" ROOOOOT ----- LINK A : %s  | LINK B : %s \n", root->link_a, root->link_b);

	// check que root->link_a et root->link_b n'existe pas deja.
	//if (has_node(n_begin, root->link_a, root->link_b) == 1)
		//return (NULL);
	// Si un noeud est deja creer, ne cre pas de doublon => link->is_set = 1.
	// --------------- >>>> On veut pas creer 2 fois le meme lien <<<<< ------------------
	// printf(" LINK A : %s  | LINK B : %s \n", root->link_a, root->link_b);
	// if (root->childs == NULL)
	depth++;
	root->childs = (t_nodes **)malloc(sizeof(t_nodes *) * root->c_childs);
	i = 0;	
	while (i < root->c_childs)
	{
		root->childs[i] = (t_nodes *)malloc(sizeof(t_nodes));
		root->childs[i]->r_name = root->link_b;
		get_next(links, root->childs[i], root->link_a, i);
		printf(" LINK A : %s  | LINK B : %s | DEPTH : %d \n", root->childs[i]->link_a, root->childs[i]->link_b, depth);
		i++;
	}
	i = 0;
	while (i < root->c_childs)
	{
		tmp = root->childs[i]->link_b;
	   	//sleep(1);
		set_nodes(root->childs[i], links, tmp, depth, begin);	
		i++;
	}
	return (NULL);
}
