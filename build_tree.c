/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   build_tree.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/21 18:39:26 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/21 21:55:08 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>

// asscocie tout les links avec le noeud correspondant.
// une fois qu on a plus de link pour ce noeud, cherche les bifurcations.

void	set_first_node(t_tree *tree, t_data *data)
{
	tree->x = data->x_start;
	tree->y = data->y_start;
	tree->r_name = data->start;
}


t_nodes	*set_nodes(t_tree *tree, t_links *links, char *r_name)
{
	t_links *begin;
	int i;
	int c_nodes;

	i = 0;
	c_nodes = 0;	
	begin = links;
	while (links)
	{

		if (r_name != NULL)
		{
			if (links->a != 0 || links->b != 0)
			{
				if (!ft_strcmp(r_name, links->a) || !ft_strcmp(r_name, links->b))
					c_nodes++;
			}
		}
		links = links->next;
	}
	//printf(" NOOODES %d\n", c_nodes);
	if (tree->nodes == NULL)
		tree->nodes = malloc(sizeof(t_nodes *) * c_nodes);
	// pour chaque node on veut creer des news nodes.
	while (i < c_nodes && begin)
	{
		tree->nodes[i] = malloc(sizeof(t_nodes));
		tree->nodes[i]->r_name = begin->a;
		tree->nodes[i] = set_nodes(tree, links, begin->b);
		begin = begin->next;
		i++;
	}
	return (tree->nodes[i]);	
}

/*void	build_tree(t_tree *tree, t_data *data, t_room *room, t_links *links)
{
	t_tree *begin;
	t_links *b_links;
	t_room *b_room;
	t_links *tmp;

	b_room = room;
	b_links = links;
	set_first_node(tree, data);
	begin = tree;
	while (links)
	{
		tmp = links;
		while (tmp)
		{
			if (tmp->a == tree->r_name)
			{
				// trouver tout les noeuds en relation.
				// creer des nodes a partir de cette branche.
				// si encore des nodes, revenir au debut de la branche pour en creer des nouveaux.
				set_nodes(begin, b_links, tree->r_name);
			}
			tmp = tmp->next;
		}
		links = links->next;
	}
}*/
