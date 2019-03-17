# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jackson <jbeall@student.42.us.org>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/03 12:06:08 by skunz             #+#    #+#              #
#    Updated: 2019/03/16 17:42:24 by jackson          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##################################### GENERAL ##################################

NAME = lem-in

FLAGS = -Wall -Wextra -Werror -Ofast #-fsanitize=address

SRC_DIR = ./src/

################################# SOURCES #####################################

SRC = ant_runner.c ant_stack.c bfs.c flow_solver.c main.c parser_helper.c \
		parser.c translate.c flow_solver_helper.c flow_solver_helper2.c \
		flow_solver_init.c node_convert.c debugger_options.c

###################################### OBJECTS #################################

OBJ_DIR = .obj/

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

################################ LIBRARIES #####################################

LIB_DIR = ./lib

LIB_FT = -L $(LIB_DIR)/libft -lft

###################################### HEADERS #################################

INC_DIR = ./includes/

LIB_HEAD = $(LIB_DIR)/libft/includes/

INC = -I $(LIB_HEAD) -I $(INC_DIR)

###############################  COLORS AND TEXT  ##############################

#COLORS
COM_COLOR   = \033[0;36m
NO_COLOR    = \033[m

#TEXT
COM_STRING  = "$(NAME) Compilation Successful"
CLEAN_OBJ	= "Cleaned $(NAME) Objects"
CLEAN_NAME	= "Cleaned $(NAME) Binary"

######################################## RULES #################################

all: libf obj $(NAME)

$(NAME): $(OBJ)
	@clang $(FLAGS) $^ $(LIB_FT) -o $@ 
	@echo "$(COM_COLOR)$(COM_STRING)$(NO_COLOR)"

#OBJECTS

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@clang $(FLAGS) $(INC) -g -c $< -o $@

obj:
	@mkdir -p $(OBJ_DIR)

clean: libclean
	@/bin/rm -rf $(OBJ_DIR)
	@echo "$(COM_COLOR)$(CLEAN_OBJ)$(NO_COLOR)"

fclean: clean libfclean
	@/bin/rm -f $(NAME)
	@echo "$(COM_COLOR)$(CLEAN_NAME)$(NO_COLOR)"

#LIBFT

libf:
	@make -C ./lib/libft all --no-print-directory

libfclean:
	@make -C $(LIB_DIR)/libft fclean --no-print-directory

libclean:
	@make -C $(LIB_DIR)/libft clean --no-print-directory

re: fclean all
