#  ************************************************************************** #
#                                                           LE - /            #
#                                                               /             #
#    Makefile                                         .::    .:/ .      .::   #
#                                                  +:+:+   +:    +:  +:+:+    #
#    By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     #
#                                                  #+#   #+    #+    #+#      #
#    Created: 2018/10/05 07:55:16 by asiaux       #+#   ##    ##    #+#       #
#    Updated: 2018/10/11 23:51:35 by asiaux      ###    #+. /#+    ###.fr      #
#                                                          /                  #
#                                                         /                   #
#  ************************************************************************** #

.PHONY = $(POINTA) lib all clean fclean re

# **************************************************************************** #
#																			   #
#									DIRECTORIES		    					   #
#																			   #
# **************************************************************************** #

SRCDIR = ./src/
OBJDIR = ./obj/
HEADERDIR = ./includes/
LIBFTDIR = ./libft/
OBJALL = $(OBJDIR)

# **************************************************************************** #
#																			   #
#		           			    	FILES		    						   #
#																			   #
# **************************************************************************** #

NAME = lem_in
CC = gcc
CFLAGS = -Werror -Wall -Wextra
POINTA = $(addprefix $(LIBFTDIR), libft.a)
HEADERS = $(addprefix $(HEADERDIR), lem_in.h)

FILESLEM = 	clean_tube\
			main\
			parse_room\
			room_tool\
			solver\
			tools\
			trie\
			tube\
			tube_tool

SRCLEM = $(addprefix $(SRCDIR), $(addsuffix .c, $(FILESLEM)))
OBJLEM = $(addprefix $(OBJDIR), $(addsuffix .o, $(FILESLEM)))

SRCS = $(SRCLEM)
OBJS = $(OBJLEM)

# **************************************************************************** #
#																			   #
#									COMMANDS								   #
#																			   #
# **************************************************************************** #

all : lib $(NAME)

$(NAME): $(OBJDIR) $(OBJS) $(POINTA)
	@printf "Compiling $(NAME)..."
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(POINTA)
	@printf "\033[32m[OK]\033[0m\n"

$(OBJDIR):
	@mkdir $@

lib:
	@make -C $(LIBFTDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADERS)
	@printf "%b" "Compiling $< in $@..."
	@$(CC) $(CFLAGS) -o $@ -c $< -I $(HEADERDIR)
	@printf "\033[32m[OK]\033[0m\n"

clean:
	@rm -rf $(OBJDIR)
	@make clean -C libft/

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft/

re: fclean all
