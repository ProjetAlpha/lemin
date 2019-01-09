/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_input.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/19 15:39:21 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/09 21:10:42 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>

int		is_valid_room(char *line)
{
	if (line[0] == 'L' || line[0] == '#')
		return (0);
	if (ft_strchr(line, '-') != NULL)
		return (0);
	return (1);
}	

int		is_number(char *line)
{
	int i;
	int c_digit;
	int len;

	i = 0;
	c_digit = 0;
	len = ft_strlen(line);
	while (line[i])
	{
		if (ft_isdigit(line[i]))
			c_digit++;
		i++;
	}
	return (c_digit == len);
}

int		set_room(t_room *room, char *line)
{
	int i;
	char **split;

	i = 0;
	split = ft_strsplit(line, ' ');
	while (split[i])
		i++;
	printf("1 - %s | 2 - %s\n", split[0], split[1]);
	if (i != 3)
		return (0);
	room->name = is_valid_room(split[0]) ? split[0] : NULL;
	room->x = is_number(split[1]) ? ft_atoi(split[1]) : -1;
	room->y = is_number(split[2]) ? ft_atoi(split[2]) : -1;
	if (room->x != -1 && room->y != -1 && room->name != NULL)
		return (1);
	printf("room x : %d | room y : %d | name : %s\n", room->x, room->y, room->name);
	return (0);
}

int		set_links(t_links *links, char *line, t_data *data)
{
	int i;
	char **split;

	i = 0;
	split = ft_strsplit(line, '-');
	while (split[i])
		i++;
	if (i != 2)
	   return (0);
	links->a = split[0];
	links->b = split[1];
	printf("%s\n", links->a);
	if (!ft_strcmp(links->a, links->b))
		return (0);	
	if (!ft_strcmp(links->a, data->end) || !ft_strcmp(links->b, data->end))
		data->have_end = 1;
	return (1);
}

void	set_data(t_data *data, char *line, int type)
{
	int i;
	char **split;

	i = 0;
	split = ft_split_whitespaces(line);
	while (split[i])
		i++;
	if (i != 3)
	   return ;
	if (type == 1)
	{
		data->start = split[0];
		data->x_start = is_number(split[1]) ? ft_atoi(split[1]) : -1;
		data->y_start = is_number(split[2]) ? ft_atoi(split[2]) : -1;
	}
	else if (type == 2)
	{
		data->end = split[0];
		data->x_end = is_number(split[1]) ? ft_atoi(split[1]) : -1;
		data->y_end = is_number(split[2]) ? ft_atoi(split[2]) : -1;
	}	
}

void	print_room(t_room *room)
{
	while (room)
	{
		printf("ROOM NAME  -- %s\n", room->name);
		printf("ROOM X -- %d\n", room->x);
		printf("ROOM Y -- %d\n", room->y);
		room = room->next;
	}
}

void	print_links(t_links *links)
{
	while (links)
	{
		printf("LINK A -- %s\n", links->a);
		printf("LINK B -- %s\n", links->b);
		links = links->next;
	}
}

void	parse_entry(t_data *data, t_links *links, t_room *room)
{
	int		c_line;
	t_room	*r_begin;
	t_links	*l_begin;
	char	*line;

	c_line = 0;
	r_begin = room;
	l_begin = links;
	while (get_next_line(0, &line))
	{
		if (line[0] == ' ')
			return ;
		if (!ft_strncmp("##start", line, 7) && data->is_start == 2)
				return ;
			else if (!ft_strncmp("##end", line, 5) && data->is_end == 2)
				return ;
		if (data->n_ants == 0)
		{	
			if (is_number(line))
				data->n_ants = ft_atoi(line);
		}
		else
		{	
			if (data->is_start == 1)
			{
				set_data(data, line, 1);
				data->is_start = 2;
			}
			else if (data->is_end == 1)
			{
				set_data(data, line, 2);
				data->is_end = 2;
			}
			else if (ft_strncmp("##start", line, 7) != 0 && ft_strncmp("##end", line, 5) != 0
					&& ft_strchr(line, '#') == NULL)
			{
				if (set_room(room, line) == 1)
				{
					room->next = ft_init_room();
					room = room->next;
				}
				else if (set_links(links, line, data) == 1)
				{
					data->have_link = 1;
					links->next = ft_init_links();
					links = links->next;
				}else
					return ;
			}
			if (!ft_strncmp("##start", line, 7) && data->is_start != 2)
				data->is_start = 1;
			else if (!ft_strncmp("##end", line, 5) && data->is_end != 2)
				data->is_end = 1;
		}
		c_line++;
	}
	// DEBUG ROOM AND LINKS 
	// print_room(r_begin);
	//print_links(l_begin);
	// build_tree(tree, data, room, links);
}

int	main(void)
{
	t_room *room;
	t_data	*data;
	t_links	*links;
	t_links *begin_l;
	t_tree	*tree;
	t_nodes *root;
	t_dlinks **dlinks;
	t_nodes *begin;
	int c_next;
	int depth;

	depth = 0;
	c_next = 0;
	tree = ft_init_tree();
	data = ft_init_data();
	links = ft_init_links();
	begin_l = links;
	room = ft_init_room();
	root = ft_init_nodes();
	begin = root;
	parse_entry(data, links, room);
	if (data->is_start == 2 && data->is_end == 2 && data->n_ants > 0
			&& data->have_link == 1 && data->have_end == 1)
	{
		root->r_name = data->start;
		dlinks = ft_sort_link(begin_l, data);
		set_nodes(root, dlinks, data->start, depth, begin);
		tree->root = begin;
	}else
		write(1, "ERROR", 5);
}
