/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   build_tree.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/21 18:39:26 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/21 19:28:15 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lemin.h"

// asscocie tout les links avec le noeud correspondant.
// une fois qu on a plus de link pour ce noeud, cherche les bifurcations.

void	set_first_node(t_tree *tree, t_data *data)
{
	tree->x = data->start_x;
	tree->y = data->start_y;
	tree->r_name = data->start;
	tree->next = ft_init_tree();
	tree = tree->next;
}

void	set_nodes(t_tree *tree, t_links *links, char *r_name)
{
	t_nodes *nodes;
	
		
}

void	build_tree(t_tree *tree, t_data *data, t_room *room, t_links *links)
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
}
