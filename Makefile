# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/24 17:57:21 by thbrouss     #+#   ##    ##    #+#        #
#    Updated: 2018/12/21 16:20:31 by thbrouss    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = lem-in
MAKE = make
CC = gcc
FLAGS = -Wall -Wextra -Werror
INCLUDE = ./includes

#------------------------------------FILE--------------------------------------#

ALL=parse_input\
get_next_line\
ft_init_struct

#----------------------------------SOURCE--------------------------------------#

SRC = $(addsuffix .c, $(ALL))

#----------------------------------OBJECT--------------------------------------#

OBJ = $(addsuffix .o, $(ALL))

#-----------------------------------RULE---------------------------------------#

all: $(NAME) 

$(NAME): $(OBJ)
	@echo "\033[1m|---------LIBFT COMPILE--------------|\033[0m"
	@$(MAKE) -C libft/
	@echo "\033[1m|---------FILLER COMPILE--------------|\033[0m"
	@$(CC) $(FLAGS) -L libft/ -lft $(OBJ) -o $(NAME)

%.o: %.c ./includes/lemin.h
	@$(CC) $(FLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	@echo "\033[1m|---------------------------------|\033[0m"
	@echo "\033[1m|-------Supprimer les OBJECT------|\033[0m"
	@echo "\033[1m|---------------------------------|\033[0m"
	@rm -f $(OBJ)
	@rm -f libft/*.o

fclean: clean
	@echo "\n"
	@echo "\033[1m|---------------------------------|\033[0m"
	@echo "\033[1m|-------Supprimer la libft.a------|\033[0m"
	@echo "\033[1m|---------------------------------|\033[0m"
	@rm -f $(NAME)
	@rm -f libft/libft.a

re: fclean all
