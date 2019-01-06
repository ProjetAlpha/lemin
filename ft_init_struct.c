/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_init_struct.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/21 14:22:07 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/06 21:40:17 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lemin.h"

t_data	*ft_init_data(void)
{
	t_data *data;
	data = malloc(sizeof(t_data));
	data->start = NULL;
	data->end = NULL;
	data->n_ants = 0;
	data->is_end = 0;
	data->is_start = 0;
	return (data);
}

t_tree	*ft_init_tree(void)
{
	t_tree *tree;
	tree = malloc(sizeof(t_tree));
	tree->x = 0;
	tree->y = 0;
	tree->id = 0;
	tree->r_name = NULL;
	tree->root = NULL;
	return (tree);
}

t_nodes		*ft_init_nodes(void)
{
	t_nodes	*nodes;
	nodes = malloc(sizeof(t_nodes));
	nodes->x = 0;
	nodes->y = 0;
	nodes->id = 0;
	nodes->is_set = 0;
	nodes->r_name = NULL;
	nodes->c_childs = 0;
	nodes->link_a = NULL;
	nodes->link_b = NULL;
	nodes->childs = NULL;
	return (nodes);
}

t_room		*ft_init_room(void)
{
	t_room *room;
	room = malloc(sizeof(t_room));
	room->name = NULL;
	room->x = 0;
	room->y = 0;
	room->next = NULL;
	return (room);
}

t_links		*ft_init_links(void)
{
	t_links	*links;
	links = malloc(sizeof(t_links));
	links->a = 0;
	links->is_set = 0;
	links->b = 0;
	links->next = NULL;
	return (links);
}
