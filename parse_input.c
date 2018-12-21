/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_input.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/19 15:39:21 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/21 21:46:28 by thbrouss    ###    #+. /#+    ###.fr     */
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
	if (i != 3)
		return (0);
	room->name = is_valid_room(split[0]) ? split[0] : NULL;
	room->x = is_number(split[1]) ? ft_atoi(split[1]) : -1;
	room->y = is_number(split[2]) ? ft_atoi(split[2]) : -1;
	if (room->x != -1 && room->y != -1 && room->name != NULL)
		return (1);
	return (0);
}

int		set_links(t_links *links, char *line)
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
	return (1);
}

void	set_data(t_data *data, char *line, int type)
{
	int i;
	char **split;

	i = 0;
	split = ft_strsplit(line, ' ');
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
		if (c_line == 0)
		{	
			if (is_number(line))
				data->n_ants = ft_atoi(line);
		}
		else
		{	
			if (data->is_start)
			{
				set_data(data, line, 1);
				data->is_start = 0; 
			}
			else if (data->is_end)
			{
				set_data(data, line, 2);
				data->is_end = 0;
			}
			else
			{
				if (set_room(room, line))
				{
					room->next = ft_init_room();
					room = room->next;
				}
				if (set_links(links, line))
				{
					links->next = ft_init_links();
					links = links->next;
				}
			}
			if (!ft_strncmp("##start", line, 7))
				data->is_start = 1;
			else if (!ft_strncmp("##end", line, 5))
				data->is_end = 1;
		}
		c_line++;
	}
	// DEBUG ROOM AND LINKS 
	// print_room(r_begin);
	// print_links(l_begin);
	// build_tree(tree, data, room, links);
}

int	main(void)
{
	t_room *room;
	t_data	*data;
	t_links	*links;
	t_tree	*tree;

	tree = ft_init_tree();
	data = ft_init_data();
	links = ft_init_links();
	room = ft_init_room();
	parse_entry(data, links, room);
	set_nodes(tree, links, data->start);	
}
