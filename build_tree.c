/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   build_tree.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/21 18:39:26 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/09 20:38:21 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>

t_dlinks	**find_links2(t_dlinks **links, t_nodes *nodes, char *r_name)
{
	t_dlinks **begin;

	begin = links;
	while (begin)
	{
		if (!ft_strcmp(r_name, begin[0]->a) && (*begin)->is_set == 0)
		{
			nodes->link_a = begin[0]->a;
			nodes->link_b = begin[0]->b;
			(*begin)->is_set = 1;
			nodes->r_name = nodes->link_a;
			nodes->c_childs = (*begin)->size;
			return (begin);
		}
		else if (!ft_strcmp(r_name, begin[0]->b) && (*begin)->is_set == 0)
		{
			nodes->link_a = begin[0]->a;
			nodes->link_b = begin[0]->b;
			(*begin)->is_set = 1;
			nodes->r_name = nodes->link_a;
			nodes->c_childs = (*begin)->size;
			return (begin);
		}
		begin = (*begin)->next;
	}
	return (NULL);
}


t_nodes	**set_nodes(t_nodes *root, t_dlinks **dlinks, char *r_name, int depth, t_nodes *begin)
{
	int			i;
	int			is_next;
	char		*tmp;
	t_nodes		*n_begin;
	t_dlinks	**begin_links;
	t_dlinks	**block_dlinks;

	n_begin = begin;
	i = 0;
	is_next = 0;
	begin_links = dlinks;
	if ((block_dlinks = find_links2(begin_links, root, r_name)) == NULL)
		return (NULL);
	if (root->c_childs == 0)
		return (NULL);
	root->weight = depth;
	depth++;
	printf("\nparent ----- %s --- weight %d ----\n\n", root->r_name, root->weight);
	root->childs = (t_nodes **)malloc(sizeof(t_nodes *) * root->c_childs);
	i = 0;
	//printf("seg\n");
	// TODO : ajouter X et Y pour les bonus.
	while (i < root->c_childs && block_dlinks[i]->a != NULL && block_dlinks[i]->b != NULL)
	{
		root->childs[i] = (t_nodes *)malloc(sizeof(t_nodes));
		root->childs[i]->link_a = block_dlinks[i]->a;
		root->childs[i]->link_b = block_dlinks[i]->b;
		root->childs[i]->r_name = block_dlinks[i]->b;
		root->childs[i]->weight = depth;
		//printf(" room : %s\n", root->childs[i]->r_name);
		printf("room childs ---- %s --- weight %d ---\n", root->childs[i]->r_name, root->childs[i]->weight);		
		printf(" LINK A : %s  | LINK B : %s | DEPTH : %d \n", root->childs[i]->link_a, root->childs[i]->link_b, depth);
		i++;
	}
	i = 0;
	while (i < root->c_childs && block_dlinks[i]->a != NULL && block_dlinks[i]->b != NULL)
	{
		//printf("seg -- index %d\n", i);
		tmp = root->childs[i]->link_b;
	   	//sleep(1);
		set_nodes(root->childs[i], dlinks, tmp, depth, begin);	
		i++;
	}
	return (NULL);
}
