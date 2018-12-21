/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   build_tree.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/21 18:39:26 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/21 20:27:13 by thbrouss    ###    #+. /#+    ###.fr     */
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
}


void	add_nodes(t_tree *tree, t_nodes *current, int n)
{
	int i;
	t_nodes **nodes;
	
	i = 0;
	nodes = malloc(sizeof(t_nodes *) * n);
	while (i < n)
	{
				
		i++;
	}	
}	


void	set_nodes(t_tree *tree, t_links *links, char *r_name)
{
	t_links *begin;
	t_nodes **nodes;
	int i;
	
	i = 0;	
	begin = links;
	while (links)
	{
		if (!ft_strcmp(r_name, links->a) || !ft_strcmp(r_name, links->b))
			c_nodes++;
		links = links->next;
	}
	nodes = malloc(sizeof(t_nodes *) * c_nodes);
	// pour chaque node on veut creer des news nodes.
	while (i < c_nodes)
	{
		
		i++;
	}
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
