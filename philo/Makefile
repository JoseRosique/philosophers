# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joslopez <joslopez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 15:36:39 by joslopez          #+#    #+#              #
#    Updated: 2023/03/21 18:39:45 by joslopez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

HEADER	=	philo.h

CC		=	gcc

FLAGS	= 	-Wall -Wextra -Werror $(INC)

ifdef DEBUG
FLAGS	+=	-fsanitize=address -fno-omit-frame-pointer -g
endif

ifeq ($(OS),Linux)
	INC	=	-I $(INC_DIR) -lpthread
else
	INC	= 	-I $(INC_DIR)
endif

SRC		=	check.c exit.c fork-message.c init.c main.c philo.c \
			utils.c utils2.c setup-time.c

OBJ		=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))


SRC_DIR		=	src
INC_DIR		=	include
OBJ_DIR		=	obj

CYAN		= 	\033[0;36m
PURPLE		= 	\033[0;35m
BLUE		= 	\033[0;34m
GREEN		= 	\033[0;32m
RED			=	\033[0;31m
RESET		= 	\033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(INC) -o $@
	@echo "Executable $(CYAN)$@$(RESET) made"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(GREEN)Compiling: $<$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

debug:
	@echo "$(GREEN)Debug mode$(RESET)"
	@$(MAKE) DEBUG=1

clean:
	@echo "$(RED)Cleaning$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Removed: $(OBJ_DIR) folder$(RESET)"

fclean: clean
	@echo "$(RED)Removing: $(NAME)$(RESET)"
	@rm -rf $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
