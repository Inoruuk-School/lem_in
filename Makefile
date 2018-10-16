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

.PHONY = lib all clean fclean re

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
CFLAGS = -Werror -Wall -Wextra -g -fsanitize=address
HEADERS = $(addprefix $(HEADERDIR), lem_in.h def.h)

FILESFILLER = 	main parse_room room_tool solve tools tube_tools tube_parse\
				tube_tools2

SRCLEM = $(addprefix $(SRCDIR), $(addsuffix .c, $(FILESFILLER)))
OBJLEM = $(addprefix $(OBJDIR), $(addsuffix .o, $(FILESFILLER)))

SRCS = $(SRCLEM)
OBJS = $(OBJLEM)

# **************************************************************************** #
#																			   #
#									COMMANDS								   #
#																			   #
# **************************************************************************** #

all : $(NAME)

$(NAME): $(LIBFTDIR)libft.a $(OBJALL) $(OBJS)
	@printf "Compiling $(NAME)..."
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFTDIR)libft.a
	@printf "\033[32m[OK]\033[0m\n"

$(LIBFTDIR)libft.a: libft
	@printf "Compiling libft..."
	@make -C $(LIBFTDIR)
	@printf "\033[32m[OK]\033[0m\n"

$(OBJALL):
	@mkdir $@

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

signature:
	@echo "Nothing to do dumbass"
