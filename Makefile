# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/27 18:44:26 by bmirlico          #+#    #+#              #
#    Updated: 2023/06/13 16:43:56 by bmirlico         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## MAIN VARIABLES

NAME = 			minishell

CC = 			cc

CFLAGS = 		-g3 -Wall -Wextra -Werror

RM =			rm -f

RM_RF =			rm -rf

## SOURCES AND LIBS

SRC_DIR = 		./src

SRCS = 			$(SRC_DIR)/main.c \
				$(SRC_DIR)/lexer_1.c \
				$(SRC_DIR)/lexer_2.c \
				$(SRC_DIR)/utils.c \
				$(SRC_DIR)/lexer_list.c \
				$(SRC_DIR)/syntax_error.c \
				$(SRC_DIR)/parser_1.c \
				$(SRC_DIR)/parser_2.c \
				$(SRC_DIR)/parser_list.c

LIBFTDIR = 		./libft

LIBFT =			$(LIBFTDIR)/libft.a

LIBFT_FLAGS = 	-L$(LIBFTDIR) -lft

LREADLINE_FLAGS = -lreadline

## OBJECTS

OBJ_DIR =		./obj

OBJS = 			$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

## HEADERS

HDIR = 			./inc

HD = 			$(HDIR)/minishell.h \
				$(LIBFTDIR)/inc/libft.h \
				$(LIBFTDIR)/inc/get_next_line_bonus.h \
				$(LIBFTDIR)/inc/ft_printf.h \

INC_HD =		-I $(HDIR) -I $(LIBFTDIR)/inc

## RULES

all:			$(NAME)

$(NAME):		$(LIBFT) $(OBJS)
				$(CC) $(CFLAGS) $(INC_HD) $(OBJS) $(LIBFT_FLAGS) $(LREADLINE_FLAGS) -o $@

$(OBJS):		$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HD)
				mkdir -p $(OBJ_DIR)
				$(CC) $(CFLAGS) $(INC_HD) -c $< -o $@

$(LIBFT):
				make -C $(LIBFTDIR)

clean:
				$(RM_RF) $(OBJ_DIR)
				make clean -C $(LIBFTDIR)

fclean:			clean
				$(RM) $(NAME)
				$(RM) $(LIBFT)

re:				fclean all

.PHONY: 		all clean fclean re