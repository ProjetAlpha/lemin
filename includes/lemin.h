/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lemin.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/19 15:37:55 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/08 19:35:26 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEMIN_H

#define LEMIN_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define BUFF_SIZE 4096

typedef struct	s_room
{
	char	*name;
	int		x;
	int		y;
	struct	s_room	*next;
}				t_room;

typedef struct	s_dlinks
{
	char	*a;
	char	*b;
	int		size;
	int		is_set;
	struct	s_dlinks **next;
}				t_dlinks;			

typedef struct	s_links
{
	char *a;
	char *b;
	int	 is_set;
	int	 is_in;
	struct	s_links *next;
}				t_links;

typedef struct s_data
{
	int		is_end;
	int		is_start;
	char	*start;
	int		x_start;
	int		y_start;
	int		x_end;
	int		y_end;	
	char	*end;
	int		n_ants;
}				t_data;

typedef struct	s_nodes
{
	int		x;
	int		y;
	int		id;
	int		is_set;
	int		pos;
	int		c_childs;
	char	*link_a;
	char	*link_b;
	char	*r_name;
	struct s_nodes **childs;
}				t_nodes;

typedef struct	s_tree
{
	int		x;
	int		y;
	int		id;
	char	*r_name;
	t_nodes *root;
}				t_tree;

t_tree	*ft_init_tree(void);
t_room	*ft_init_room(void);
t_links	*ft_init_links(void);
t_nodes	*ft_init_nodes(void);
t_data	*ft_init_data(void);
int		get_next_line(const int fd, char **line);
t_nodes	**set_nodes(t_nodes *root, t_dlinks **links, char *r_name, int dept, t_nodes *begin);
t_dlinks **ft_sort_link(t_links *links, t_data *data);

#endif
